#ifndef TGB_MESSAGE_HPP
#define TGB_MESSAGE_HPP
#include <memory>
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

		
		long messageId;
		long date;
		std::string text;
		std::shared_ptr<Chat> chat;
		// Called "from" in json response
		std::shared_ptr<User> user;
		
		Message();

		Message(long messageId, long date,
		        std::string text, std::shared_ptr<Chat> chat,
				std::shared_ptr<User> user);

	};
}

#endif // TGB_MESSAGE_HPP
