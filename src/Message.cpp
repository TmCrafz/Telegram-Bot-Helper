#include "../include/Message.hpp"

tgb::Message::User::User()
: id{ 0L }
, username{ "" }
, firstName{ "" }
, lastName{ "" }
{

}
tgb::Message::User::User(long id, std::string username, std::string firstName,
						std::string lastName)
: id{ id }
, username{ username }
, firstName{ firstName }
, lastName{ lastName }
{

}


tgb::Message::Chat::Chat()
: id{ 0L }
, type{ "" }
, title{ "" }
, username{ "" }
, firstName{ "" }
, lastName{ "" }
, allMembersAdmins{ false }
{

}

tgb::Message::Chat::Chat(long id, std::string type, std::string title, 
			     std::string username, std::string firstName,
			     std::string lastName, bool allMembersAdmins)
: id{ id }
, type{ type }
, title{ title }
, username{ username }
, firstName{ firstName }
, lastName{ lastName }
, allMembersAdmins{ allMembersAdmins }
{

}


tgb::Message::PhotoSize::PhotoSize()
: fileId{ "" }
, width{ 0 }
, height{ 0 }
, fileSize{ 0 }
{

}

tgb::Message::PhotoSize::PhotoSize(std::string fileId, int width,
		  int height, int fileSize)
: fileId{ fileId }
, width{ width }
, height{ height }
, fileSize{ fileSize }
{

}

tgb::Message::PhotoSize::PhotoSize(std::string fileId, int width,
		  int height)
: fileId{ fileId }
, width{ width }
, height{ height }
, fileSize{ 0 }
{

}


tgb::Message::Photo::Photo()
{

}

tgb::Message::Photo::Photo(std::vector<tgb::Message::PhotoSize> photoSizes)
: photoSizes{ photoSizes }
{

}

tgb::Message::Message(long messageId, long date,
			std::string text, std::shared_ptr<Chat> chat,
			std::shared_ptr<User> user, std::shared_ptr<Photo> photo)
: messageId{ messageId }
, date{ date }
, text{ text }
, chat{ chat }
, user{ user }
, photo{ photo }
{

}
