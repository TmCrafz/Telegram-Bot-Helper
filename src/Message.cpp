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

tgb::Message::Message(long chatId, std::string chatFirstName, long date,
				long authorId, std::string authorFirstName, 
				long messageId, std::string text, long updateId)
: chatId{ chatId }
, chatFirstName{ chatFirstName }
, date{ date }
, authorId{ authorId }
, authorFirstName{ authorFirstName }
, messageId{ messageId }
, text{ text }
, updateId{ updateId }
{

}
