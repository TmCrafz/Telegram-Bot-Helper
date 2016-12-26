#include "../include/TgBotHelper.hpp"
#include "../include/CurlHelper.hpp"

tgb::TgBotHelper::TgBotHelper(std::string token)
: m_token{ token } 
{

}

void tgb::TgBotHelper::sendMessage(std::string chatId, std::string message)
{
	CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/sendMessage", 
			"chat_id=" + chatId + "&text=" + message);
}
