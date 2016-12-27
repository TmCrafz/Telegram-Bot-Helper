#include "../include/TgBotHelper.hpp"
#include "../include/CurlHelper.hpp"
#include "../include/libs/json.hpp"
#include <iostream>

tgb::TgBotHelper::TgBotHelper(std::string token)
: m_token{ token } 
{

}

bool tgb::TgBotHelper::sendMessage(std::string chatId, std::string message)
{
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/sendMessage", 
			"chat_id=" + chatId + "&text=" + message) };
	bool success{ response.second };
	if (success)
	{
		// Post was successful
		nlohmann::json jsn = nlohmann::json::parse(response.first);
		// Check if bot api reports successfully processing , too 
		success = jsn.value("ok", false);
	}
	return success; 
}
