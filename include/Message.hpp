#ifndef TGB_MESSAGE_HPP
#define TGB_MESSAGE_HPP
#include <string>

namespace tgb
{
	struct Message
	{
		// The id of the chat (When it is not a group chat
		// it is the same as the authorId
		long chatId;
		std::string chatFirstName;
		// Time in Unix time
		long date;
		long authorId;
		std::string authorFirstName;
		long messageId;
		std::string text;
		long updateId;

		Message(long chatId, std::string chatFirstName, long date,
				long authorId, std::string authorFirstName, 
				long messageId, std::string text, long updateId);
	};
}

#endif // TGB_MESSAGE_HPP
