#include "include/CurlHelper.hpp"
#include "include/TgBotHelper.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	if (argc < 3) 
	{
		std::cout << "Please specify token and chatId" << std::endl;
		return 0;
	}
	std::string token{ argv[1] };
	std::string chatId{ argv[2] };
	tgb::TgBotHelper tgBot(token);	
	tgBot.sendMessage(chatId, "Hello Im a Bot =)");
	std::cout << "Message send" << std::endl;

	//std::cout << CurlHelper::simplePost("", "") << std::endl;
	//std::cout << "After simplePost" << std::endl;
	return 0;
}
