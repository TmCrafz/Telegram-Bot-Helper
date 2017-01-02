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
	if (argc < 3) 
	{
		std::cout << "Please specify token and chatId" << std::endl;
		return 0;
	}
		
	std::string token{ argv[1] };
	std::string chatId{ argv[2] };
	tgb::TgBotHelper tgBot(token);
	if (argc > 3)
	{
		std::string fileName{ argv[3] };
		//std::cout << "Filename: " << fileName << std::endl;
		
		bool success{ tgBot.sendPhoto(std::stol(chatId), fileName) };
		if (success)
		{
			std::cout << "Successfully send Photo" << std::endl;
		}
		else
		{
			std::cout << "Error by sending Photo" << std::endl;
		}

	}

	tgBot.setOnNewMessageListener([&tgBot] (const std::vector<tgb::Message> &messages)
	{
		for (const tgb::Message message: messages)
		{
			std::string text{ message.text };
			long chatId{ message.chat->id };
			std::cout << "Text: " << message.text << " ChatId: " << chatId; 
			if (message.user)
			{
				std::cout << " FirstName: " << message.user->firstName;
			}
			std::cout << std::endl;
			tgBot.sendMessage(chatId, text);
		}
				
	});

	while(true)
	{
		tgBot.handleUpdates();
		//std::cout << "New Updates: \n";
		//std::pair<std::vector<tgb::Message>, bool> result = 
			//tgBot.getNewTextUpdates();
		//if (!result.second)
		//{
			//std::cout << "Error by retrieving Messages" << std::endl;
			//continue;
		//}
		//for (tgb::Message message: result.first)
		//{
			//std::cout << "ChatId: " << message.chatId << std::endl <<
						//"ChatFirstName: " << message.chatFirstName << std::endl <<
						//"Date: " << message.date << std::endl <<
						//"AuthorId: " << message.authorId << std::endl <<
						//"AuthorFirstName: " << message.authorFirstName << std::endl <<
						//"MessageId: " << message.messageId << std::endl <<
						//"Text: " << message.text << std::endl <<
						//"UpdateId: " << message.updateId << std::endl << std::endl; 
		//}
	}
	return 0;
}
