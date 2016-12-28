#include "include/CurlHelper.hpp"
#include "include/libs/json.hpp"
#include "include/Message.hpp"
#include "include/TgBotHelper.hpp"
#include <iostream>
#include <string>
#include <vector>
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
	//bool success{ tgBot.sendMessage(chatId, "Hello Im a Bot =)") };
	//if (success)
	//{
		//std::cout << "Message send" << std::endl;
	//}
	//else
	//{
		//std::cout << "Message send failed" << std::endl;
	//}
	while(true)
	{
		std::cout << "New Updates: \n";
		std::pair<std::vector<tgb::Message>, bool> result = 
			tgBot.getNewTextUpdates();
		if (!result.second)
		{
			std::cout << "Error by retrieving Messages" << std::endl;
			continue;
		}
		for (tgb::Message message: result.first)
		{
			std::cout << "ChatId: " << message.chatId << std::endl <<
						"ChatFirstName: " << message.chatFirstName << std::endl <<
						"Date: " << message.date << std::endl <<
						"AuthorId: " << message.authorId << std::endl <<
						"AuthorFirstName: " << message.authorFirstName << std::endl <<
						"MessageId: " << message.messageId << std::endl <<
						"Text: " << message.text << std::endl <<
						"UpdateId: " << message.updateId << std::endl << std::endl; 
		}
	}
	return 0;
}
