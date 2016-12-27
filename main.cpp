#include "include/CurlHelper.hpp"
#include "include/libs/json.hpp"
#include "include/TgBotHelper.hpp"
#include <iostream>
#include <string>
#include "include/libs/json.hpp"

int main(int argc, char *argv[])
{
	std::cout << sizeof(long) << std::endl;
	if (argc < 3) 
	{
		std::cout << "Please specify token and chatId" << std::endl;
		return 0;
	}
	std::string token{ argv[1] };
	std::string chatId{ argv[2] };
	tgb::TgBotHelper tgBot(token);	
	bool success{ tgBot.sendMessage(chatId, "Hello Im a Bot =)") };
	if (success)
	{
		std::cout << "Message send" << std::endl;
	}
	else
	{
		std::cout << "Message send failed" << std::endl;
	}
	while(true)
	{
		std::cout << "New Updates: \n";
		tgBot.getNewTextUpdates();
	}
	return 0;
}
