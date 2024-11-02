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

#include <jwt-cpp/jwt.h>
#include <curl/curl.h>
#include <json/json.h>

#include <misc/Log.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <map>

std::string AWS::token = "";
std::string AWS::player_id = "";
bool AWS::idle = true;

Logger &Log(Logger::get_instance());

bool AWS::process_cli(const int32_t argc, const char *argv[])
{
	std::vector<std::string> args{ argv, argv + argc };
	std::map<std::string, std::string> mp{ { "-u", "username" },
					       { "-p", "passwd" } };
	std::map<std::string, std::string> values;

	for (int32_t i = 0; i < argc; i++) {
		if (mp.count(args[i])) {
			if (i + 1 > argc) {
				Log << "(AWS) Invalid arg at " << i << ": "
				    << args[i] << "\r\n";
				return false;
			}
			values[mp[args[i]]] = args[i + 1];
			i++;
		}
	}
	if (values.size() != mp.size())
		return false;
#ifdef AWS_DEBUG
	Log << "(AWS) Logging in to server\r\n";
#endif
	AWS::token = authenticate_player(values["username"], values["passwd"]);
	if (AWS::token.empty()) {
#ifdef AWS_DEBUG
		Log << "(AWS) Couldn't log in\r\n";
#endif
		return false;
	}
	AWS::player_id =
		jwt::decode(AWS::token).get_payload_claim("sub").as_string();
#ifdef AWS_DEBUG
	Log << "(AWS) Logged in with \r\n\r\nToken: " << AWS::token
	    << "\r\n\r\nPlayer ID: " << AWS::player_id << "\r\n";
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
#ifdef AWS_DEBUG
		Log << "(AWS) Authentication failed:\r\n"
		    << authOutcome.GetError().GetMessage() << "\r\n";
#endif
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
			throw std::runtime_error(
				"Token does not contain a session ID.\r\n");
		}
	} catch (const std::exception &e) {
#ifdef AWS_DEBUG
		Log << "(AWS) Failed to decode token: " << e.what() << "\r\n";
#endif
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

#ifdef AWS_DEBUG
	if (res != CURLE_OK) {
		Log << "(AWS) Request failed: " << curl_easy_strerror(res)
		    << "\r\n";
	} else {
		Log << "(AWS) Request sent successfully" << "\r\n";
	}
#endif

	if (res != CURLE_OK)
		return false;

	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return true;
}

static const std::string update_lambda =
	"https://5rmyu3pght4flefb4djguiurq40twlwo.lambda-url.ap-south-1.on.aws/";

Json::Value AWS::request_match(const std::string &opponent_id)
{
	std::string response;
	if (send_request(update_lambda,
			 { { "operation", "CHALLENGE" },
			   { "player1_id", AWS::player_id },
			   { "player2_id", opponent_id } },
			 response)) {
		Json::Value json_response;
		Json::CharReaderBuilder reader_builder;
		std::string errors;
		std::istringstream response_stream(response);

		if (Json::parseFromStream(reader_builder, response_stream,
					  &json_response, &errors)) {
#ifdef AWS_DEBUG
			Log << "(AWS) Parsed JSON Response(Match Request): "
			    << json_response.toStyledString() << "\r\n\r\n";
#endif
			return json_response;
		}
	}
#ifdef AWS_DEBUG
	Log << "(AWS) Match " << AWS::player_id << " logged out\r\n";
#endif

	return "";
}

std::string AWS::accept_match(const std::string &opponent_id)
{
	std::string response;
	if (send_request(update_lambda,
			 { { "operation", "CHALLENGE_RESP" },
			   { "player1_id", opponent_id },
			   { "player2_id", AWS::player_id },
			   { "status", "ACCEPT" } },
			 response)) {
		Json::Value json_response;
		Json::CharReaderBuilder reader_builder;
		std::string errors;
		std::istringstream response_stream(response);

		if (Json::parseFromStream(reader_builder, response_stream,
					  &json_response, &errors)) {
#ifdef AWS_DEBUG
			Log << "(AWS) Parsed JSON Response(Match Accept): "
			    << json_response.toStyledString() << "\r\n\r\n";
#endif
			return json_response["connect_url"].asString();
		}
	}
	return "";
}

void AWS::reject_match(const std::string &opponent_id)
{
	std::string response;
	if (send_request(update_lambda,
			 { { "operation", "CHALLENGE_RESP" },
			   { "player1_id", opponent_id },
			   { "player2_id", AWS::player_id },
			   { "status", "REJECT" } },
			 response)) {
#ifdef AWS_DEBUG
		Json::Value json_response;
		Json::CharReaderBuilder reader_builder;
		std::string errors;
		std::istringstream response_stream(response);

		if (Json::parseFromStream(reader_builder, response_stream,
					  &json_response, &errors)) {
			Log << "(AWS) Parsed JSON Response(Match Accept): "
			    << json_response.toStyledString() << "\r\n\r\n";
#endif
		}
	}
}

bool AWS::signout()
{
	std::string response;
	if (send_request(update_lambda,
			 { { "operation", "DELETE" },
			   { "playerid", AWS::player_id } },
			 response)) {
#ifdef AWS_DEBUG
		Log << "(AWS) Player " << AWS::player_id << " logged out\r\n";
#endif
		AWS::token = AWS::player_id = "";
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

	if (send_request(update_lambda, req, response)) {
#ifdef AWS_DEBUG
		Log << "(AWS) " << response << "\r\n\r\n";
#endif
		Json::CharReaderBuilder reader_builder;
		std::string errors;
		std::istringstream response_stream(response);

		if (Json::parseFromStream(reader_builder, response_stream,
					  &json_response, &errors)) {
#ifdef AWS_DEBUG
			Log << "(AWS) Parsed JSON Response: "
			    << json_response.toStyledString() << "\r\n\r\n";
#endif
			return json_response;
		} else {
			Log << "(AWS) Failed to parse JSON: " << errors
			    << "\r\n\r\n";
		}
	}
	return Json::Value();
}

std::string AWS::get_player_id()
{
	return AWS::player_id;
}