#include "../include/Message.hpp"

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
