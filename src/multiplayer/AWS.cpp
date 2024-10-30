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
#include <string>
#include <vector>
#include <map>

std::string AWS::token = "";
std::string AWS::player_id = "";

bool AWS::process_cli(const int argc, const char *argv[])
{
	std::vector<std::string> args{ argv, argv + argc };
	std::map<std::string, std::string> mp{ { "-u", "username" },
					       { "-p", "passwd" } };
	std::map<std::string, std::string> values;

	for (int i = 0; i < argc; i++) {
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
				  << std::endl;
			return "";
		}
	} catch (const std::exception &e) {
		std::cerr << "Failed to decode token: " << e.what()
			  << std::endl;
		return "";
	}
}

bool send_request(const std::string &lambda_url,
		  const std::map<std::string, std::string> &mp)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, lambda_url.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		Json::Value json_payload;
		for (auto &[key, value] : mp)
			json_payload[key] = value;

		Json::StreamWriterBuilder writer;
		std::string payload = Json::writeString(writer, json_payload);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers,
					    "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			// std::cerr
			// 	<< "Request failed: " << curl_easy_strerror(res)
			// 	<< '\n';
			return false;
		} else {
			// std::cout << "Request sent successfully" << '\n';
		}

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}
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
			  << targetId << std::endl;

	} else {
		std::cerr << "Target player is not active or does not exist."
			  << std::endl;
	}
	Aws::ShutdownAPI(options);
	return false;
}

using server = websocketpp::server<websocketpp::config::asio>;
void AWS::on_message(server *s, websocketpp::connection_hdl hdl,
		     server::message_ptr msg)
{
	std::cout << "Received: " << msg->get_payload() << std::endl;
	s->send(hdl, "Data received!", websocketpp::frame::opcode::text);
}

bool AWS::signout()
{
	static const std::string lambda_url =
		"https://tbo47lwtix3qhvg2zrzmufrsca0mbolu.lambda-url.ap-south-1.on.aws/";

	if (send_request(lambda_url, { { "playerid", AWS::player_id } })) {
#ifdef AWS_DEBUG
		std::cout << "Player " << AWS::player_id << " logged out\n";
#endif
		AWS::token = AWS::player_id = "";
		return true;
	} else {
		return false;
	}
}