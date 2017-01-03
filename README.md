# Telegram-Bot-Helper
Telegram-Bot-Helper implement some functionality of the Telegram Bot Api for easy use in C++. I have created this for another project, so it only have limited functionallity (send messages, get messages, send photos, save photos)

## Used Libraries:
JSON for Modern C++
https://github.com/nlohmann/json

## Usage
You have to use a compiler which supports c++14 and specify that you want to compile with c++14.
Also you have to add -lcurl to your compiler flags (because libcurl is needed).

First include header (include path depends on the path of the lib)
````cpp
#include "TgBotHelper.hpp" 
````
How to use methods 
````cpp
// Create TgBotHelper instance
tgb::TgBotHelper tgBot("Your Bot token");
// Send simple text
tgBot.sendTextMessage(chatId, "Message text");
// Send photo
tgBot.sendPhotoMessage(chatId, "Path to file");
// Save received photo
tgBot.savePhoto("FileId of photo", "Path where to save file");
// Get new updates
// "std::pair<std::vector<Message>, bool> getNewUpdates()" returns a pair 
// with the updates and a bool which inform if the call was successful
std::pair<std::vector<tgb::Message>, bool>  result{ tgBot.getNewUpdates() };

// Instead of calling getNewUpdates() you can specify a listener 
// (e.g. at the beginning of the programm) and call handleUpdates()
// Set listener with lambda expression:
tgBot.setOnNewMessageListener([&tgBot] (const std::vector<tgb::Message> &messages)
{
	// Do stuff with messages here
}
// Call handleUpdates method and do the stuff specified in listener above, 
// when there is a listener specified
tgBot.handleUpdates();
````

### Examples
Echo text:
````cpp
#include <iostream>
// Include library
#include "include/TgBotHelper.hpp"

int main(int argc, char *argv[])
{		
	std::string token{ "Your Bot token" };
	std::string filePath{ "Path where to save received files" };
	tgb::TgBotHelper tgBot(token);
	// Set listener with lambda expression, to specifiy what to do when new messages receive
	tgBot.setOnNewMessageListener([&tgBot, &filePath] (const std::vector<tgb::Message> &messages)
	{
		// Loop over all messages
		for (const tgb::Message message: messages)
		{
			// The id of the chat in which message was send
			long chatId{ message.chat->id };
			if (!message.text.empty())
			{
				// Message was send. Echo same text back to chat
				const std::string text{ message.text };			
				tgBot.sendTextMessage(chatId, text);
			}
		}				
	});
	while(true)
	{
		// Check for new updates. Listener is automatical called when there are
		// new updates
		tgBot.handleUpdates();
	}
	return 0;
}
````

Echo text which is send to the bot and save photo which was send to the bot in a specified path:
````cpp
#include <iostream>
// Include library
#include "include/TgBotHelper.hpp"

int main(int argc, char *argv[])
{		
	std::string token{ "Your Bot token" };
	std::string filePath{ "Path where to save received files" };
	tgb::TgBotHelper tgBot(token);
	// Set listener with lambda expression, to specifiy what to do when new messages receive
	tgBot.setOnNewMessageListener([&tgBot, &filePath] (const std::vector<tgb::Message> &messages)
	{
		// Loop over all messages
		for (const tgb::Message message: messages)
		{
			// The id of the chat in which message was send
			long chatId{ message.chat->id };
			if (!message.text.empty())
			{
				// Message was send. Echo same text back
				const std::string text{ message.text };			
				tgBot.sendTextMessage(chatId, text);
			}
			if (message.photo)
			{
				// Photo was send. Save photo.
				// In most cases the photo is available in different file sizes.
				std::vector<tgb::Message::PhotoSize> photoSizes{ message.photo->photoSizes };					
				if (photoSizes.size() > 0)
				{
					// Regulary the last PhotoSize object in the vector is the one with the
					// original size. To save the photo we need its fileId
					const std::string photoId{ photoSizes.back().fileId };
					// Save Photo to specified file path and add its id as name
					if (tgBot.savePhoto(photoId, filePath + photoId))
					{
						std::cout << "Photo successfully saved \n";
					}
					else
					{
						std::cout << "Error by saving photo \n";
					}
				}					
			}
		}				
	});
	while(true)
	{
		// Check for new updates. Listener is automatical called when there are
		// new updates
		tgBot.handleUpdates();
	}
	return 0;
}
````
