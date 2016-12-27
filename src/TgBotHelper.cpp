#include "../include/TgBotHelper.hpp"
#include "../include/CurlHelper.hpp"
#include <iostream>

tgb::TgBotHelper::TgBotHelper(std::string token)
: m_token{ token } 
{

}

void tgb::TgBotHelper::sendMessage(std::string chatId, std::string message)
{
	std::string response { CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/sendMessage", 
			"chat_id=" + chatId + "&text=" + message) };
	std::cout << response << std::endl;
}
