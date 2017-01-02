#ifndef TGB_MESSAGE_HPP
#define TGB_MESSAGE_HPP
#include <memory>
#include <string>
#include <vector>

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
		
		struct PhotoSize
		{
			std::string fileId;
			int width;
			int height;
			int fileSize;

			PhotoSize();
			PhotoSize(std::string fileId, int width,
					  int height, int fileSize);
			PhotoSize(std::string fileId, int width,
					  int height);

		};


		struct Photo
		{
			std::vector<PhotoSize> photoSizes;

			Photo();
			explicit Photo(std::vector<PhotoSize> photoSizes);
		};

		
		long messageId;
		long date;
		std::string text;
		std::shared_ptr<Chat> chat;
		// Named "from" in json response
		std::shared_ptr<User> user;
		std::shared_ptr<Photo> photo;
		Message();

		Message(long messageId, long date,
		        std::string text, std::shared_ptr<Chat> chat,
				std::shared_ptr<User> user, std::shared_ptr<Photo> photo);

	};
}

#endif // TGB_MESSAGE_HPP
