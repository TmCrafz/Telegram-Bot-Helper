# Telegram-Bot-Helper
Telegram-Bot-Helper implement some functionality of the Telegram Bot Api for easy use in C++. I have created this for another project, so it only have limited functionallity (send messages, get messages and send photos)

## Used Libraries:
JSON for Modern C++
https://github.com/nlohmann/json

## Usage
First include header (Include path depends on the path of the lib)
````cpp
#include "TgBotHelper.hpp" 
````
Use Lib 
````cpp
// Create TgBotHelper Instance
tgb::TgBotHelper tgBot("Your Bot token");
// Send simple Text
tgBot.sendTextMessage(ChatId, "Message text");
// Send Photo
tgBot.sendPhotoMessage(ChatId, "Path to file");
// Save received Photo
tgBot.savePhoto("File id of photo", "Path where to save file");
// Get new Updates
// "std::pair<std::vector<Message>, bool> getNewUpdates()" returns a pair with the updates and a bool which inform if the call was successful
std::pair<std::vector<tgb::Message>, bool>  result{ tgBot.getNewUpdates() };

// Instead of calling getNewUpdates() you can specify a listener (e.g. at the beginning of the programm) and call handleUpdates()
// Set Listener with lambda expression:
tgBot.setOnNewMessageListener([&tgBot] (const std::vector<tgb::Message> &messages)
{
	// Do stuff with Messages here
}
// Call handle Updates and do the stuff specified in listener above, when there is a listener specified
tgBot.handleUpdates();
````

### Example
````cpp
// Create TgBotHelper Instance
tgb::TgBotHelper tgBot("Your Bot token");
// Listener is called when a new message received. Add lambda to do stuff.
tgBot.setOnNewMessageListener([&tgBot] (const std::vector<tgb::Message> &messages)
{
	for (const tgb::Message message: messages)
	{
		// Get text which was send (Is empty when no text was send)
		std::string text{ message.text };
		// Get chat id of chat in which message was send
		// If it is no group chat it is the same id as the id in message.user
		long chatId{ message.chat->id };
		// Data about user, who have send message
		if (message.user)
		{
			std::cout << " FirstName: " << message.user->firstName;
		}
		// Photo was send
		if (message.photo)
		{
			if (message.photo->photoSizes.size() > 0)
			{
				// In most cases the photo is available in different file sizes.
				// Regulary the last PhotoSize object in the vector is the one with the
				// original size.
				const std::string photoId{ message.photo->photoSizes.back().fileId };
				// Save photo with given photoId
				tgBot.savePhoto(photoId, "Put FilePath Here");
			}
		}
	}
			
});
while(true)
{
	// Check if updates are available and call listener when specified
	tgBot.handleUpdates();
}
````

