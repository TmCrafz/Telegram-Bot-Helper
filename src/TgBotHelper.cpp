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
	std::string response = { CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/sendMessage", 
			"chat_id=" + chatId + "&text=" + message) };
	nlohmann::json jsn = nlohmann::json::parse(response);
	// Check if post was successfull
	bool success = jsn.value("ok", false);
	return sucess; 
}
