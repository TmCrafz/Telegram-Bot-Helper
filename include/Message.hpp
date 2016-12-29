#ifndef TGB_MESSAGE_HPP
#define TGB_MESSAGE_HPP
#include <string>

namespace tgb
{
	struct Message
	{
		struct Chat
		{
			long id;
			std::string type;
			std::string title;
			std::string username;
			std::string firstName;
			std::string lastName;
			bool allMembersAdmins;
			
			Chat();
			Chat(long id, std::string type, std::string title, 
			     std::string username, std::string firstName,
			     std::string lastName, bool allMembersAdmins);
		};

		struct User
		{			
			long id;
			std::string username;
			std::string firstName;
			std::string lastName;
			
			User();
			User(long id, std::string username, std::string firstName,
			     std::string lastName);
		};

		// The id of the chat (When it is not a group chat
		// it is the same as the authorId)
		long chatId;
		std::string chatFirstName;
		// Unix time
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
