#include "include/TgBotHelper.hpp"
#include <iostream>

int main(int argc, char *argv[])
{

	if (argc < 3) 
	{
		std::cout << "Please specify token and chatId" << std::endl;
		return 0;
	}
		
	std::string token{ argv[1] };
	tgb::TgBotHelper tgBot(token);
	// The path where received files get saved 
	std::string filePath{ argv[3] };
	std::cout << "FilePath: " << filePath << std::endl;

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
