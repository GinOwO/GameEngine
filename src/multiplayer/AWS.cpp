#include <multiplayer/AWS.h>

#include <aws/core/Aws.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/InitiateAuthRequest.h>
#include <aws/cognito-idp/model/GlobalSignOutRequest.h>

#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/PutItemRequest.h>
#include <aws/dynamodb/model/AttributeValue.h>
#include <aws/dynamodb/model/DeleteItemRequest.h>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <jwt-cpp/jwt.h>
#include <curl/curl.h>
#include <json/json.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

std::string AWS::token = "";
std::string AWS::player_id = "";
bool AWS::idle = true;

bool AWS::process_cli(const int32_t argc, const char *argv[])
{
	std::vector<std::string> args{ argv, argv + argc };
	std::map<std::string, std::string> mp{ { "-u", "username" },
					       { "-p", "passwd" } };
	std::map<std::string, std::string> values;

	for (int32_t i = 0; i < argc; i++) {
		if (mp.count(args[i])) {
			if (i + 1 > argc) {
				std::cerr << "Invalid arg at " << i << ": "
					  << args[i] << '\n';
				return false;
			}
			values[mp[args[i]]] = args[i + 1];
			i++;
		}
	}
	if (values.size() != mp.size())
		return false;
#ifdef AWS_DEBUG
	std::cout << "Logging in to server\n";
#endif
	AWS::token = authenticate_player(values["username"], values["passwd"]);
	if (AWS::token.empty()) {
		std::cout << "Couldn't log in\n";
		return false;
	}
	AWS::player_id =
		jwt::decode(AWS::token).get_payload_claim("sub").as_string();
#ifdef AWS_DEBUG
	std::cout << "Logged in with \n\nToken: " << AWS::token
		  << "\n\nPlayer ID: " << AWS::player_id << '\n';
#endif
	return true;
}

std::string AWS::authenticate_player(const std::string &username,
				     const std::string &password)
{
	Aws::SDKOptions options;
	Aws::InitAPI(options);

	Aws::Client::ClientConfiguration clientConfig;
	clientConfig.region = "ap-south-1";
	Aws::CognitoIdentityProvider::CognitoIdentityProviderClient
		cognitoClient(clientConfig);
	Aws::CognitoIdentityProvider::Model::InitiateAuthRequest authRequest;

	authRequest.SetClientId("7fpvlb8fshn8fmgf8db158nnf4");
	authRequest.SetAuthFlow(Aws::CognitoIdentityProvider::Model::
					AuthFlowType::USER_PASSWORD_AUTH);
	authRequest.AddAuthParameters("USERNAME", username);
	authRequest.AddAuthParameters("PASSWORD", password);

	auto authOutcome = cognitoClient.InitiateAuth(authRequest);
	Aws::ShutdownAPI(options);

	if (authOutcome.IsSuccess()) {
		return authOutcome.GetResult()
			.GetAuthenticationResult()
			.GetIdToken();
	} else {
		std::cerr << "Authentication failed:\n"
			  << authOutcome.GetError().GetMessage() << '\n';
		return "";
	}
}

std::string get_session_id_from_token(const std::string &token)
{
	try {
		auto decoded_token = jwt::decode(token);

		if (decoded_token.has_payload_claim("sessionid")) {
			return decoded_token.get_payload_claim("sessionid")
				.as_string();
		} else {
			std::cerr << "Token does not contain a session ID."
				  << '\n';
			return "";
		}
	} catch (const std::exception &e) {
		std::cerr << "Failed to decode token: " << e.what() << '\n';
		return "";
	}
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb,
		     std::string *userp)
{
	size_t totalSize = size * nmemb;
	userp->append((char *)contents, totalSize);
	return totalSize;
}

bool send_request(const std::string &lambda_url,
		  const std::map<std::string, std::string> &mp,
		  std::string &response_str)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (!curl)
		return false;
	curl_easy_setopt(curl, CURLOPT_URL, lambda_url.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 1L);

	// Prepare the JSON payload
	Json::Value json_payload;
	for (const auto &[key, value] : mp)
		json_payload[key] = value;

	Json::StreamWriterBuilder writer;
	std::string payload = Json::writeString(writer, json_payload);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);

	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		// std::cerr << "Request failed: " << curl_easy_strerror(res) << '\n';
		return false;
	} else {
		// std::cout << "Request sent successfully" << '\n';
	}

	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return true;
}

bool AWS::request_match(const std::string &requesterId,
			const std::string &targetId)
{
	Aws::SDKOptions options;
	Aws::InitAPI(options);
	Aws::DynamoDB::DynamoDBClient dynamoClient;

	Aws::DynamoDB::Model::GetItemRequest getRequest;
	getRequest.SetTableName("ActivePlayers");
	getRequest.AddKey("PlayerID",
			  Aws::DynamoDB::Model::AttributeValue(targetId));

	auto getOutcome = dynamoClient.GetItem(getRequest);
	if (getOutcome.IsSuccess() &&
	    getOutcome.GetResult().GetItem().size() > 0) {
		std::cout << "Match request sent from " << requesterId << " to "
			  << targetId << '\n';

	} else {
		std::cerr << "Target player is not active or does not exist."
			  << '\n';
	}
	Aws::ShutdownAPI(options);
	return false;
}

using server = websocketpp::server<websocketpp::config::asio>;
void AWS::on_message(server *s, websocketpp::connection_hdl hdl,
		     server::message_ptr msg)
{
	std::cout << "Received: " << msg->get_payload() << '\n';
	s->send(hdl, "Data received!", websocketpp::frame::opcode::text);
}

static const std::string modify_lambda =
	"https://5rmyu3pght4flefb4djguiurq40twlwo.lambda-url.ap-south-1.on.aws/";

bool AWS::signout()
{
	std::string response;
	if (send_request(modify_lambda,
			 { { "operation", "DELETE" },
			   { "playerid", AWS::player_id } },
			 response)) {
#ifdef AWS_DEBUG
		std::cout << "Player " << AWS::player_id << " logged out\n";
#endif
		AWS::token = AWS::player_id = "";
		return true;
	}
	return false;
}

bool AWS::toggle_idle()
{
	std::string response;
	if (send_request(modify_lambda,
			 { { "operation", "UPDATE_IDLE" },
			   { "playerid", AWS::player_id },
			   { "state", AWS::idle ? "False" : "True" } },
			 response)) {
		AWS::idle = !AWS::idle;
#ifdef AWS_DEBUG
		std::cout << "Player " << AWS::player_id << " idle? "
			  << AWS::idle << "\n";
#endif
		return true;
	}
	return false;
}

Json::Value AWS::read_active(int32_t idle)
{
	std::string response;
	Json::Value json_response;
	std::map<std::string, std::string> req{
		{ "operation", "GET" }, { "playerid", AWS::player_id }
	};

	if (idle == 0)
		req["idle_only"] = "False";
	else if (idle == 1)
		req["idle_only"] = "True";

	if (send_request(modify_lambda, req, response)) {
#ifdef AWS_DEBUG
		std::cout << response << "\n\n";
#endif
		Json::CharReaderBuilder reader_builder;
		std::string errors;
		std::istringstream response_stream(response);

		if (Json::parseFromStream(reader_builder, response_stream,
					  &json_response, &errors)) {
#ifdef AWS_DEBUG
			std::cout << "Parsed JSON Response: "
				  << json_response.toStyledString() << "\n\n";
#endif
			return json_response["Items"];
		} else {
			std::cerr << "Failed to parse JSON: " << errors
				  << "\n\n";
		}
	}
	return Json::Value();
}
