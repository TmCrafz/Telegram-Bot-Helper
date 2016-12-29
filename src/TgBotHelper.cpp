#include "../include/TgBotHelper.hpp"
#include "../include/CurlHelper.hpp"
#include "../include/libs/json.hpp"
#include <iostream>

tgb::TgBotHelper::TgBotHelper(std::string token)
: m_token{ token }
, m_lastRetrieved{ -1L }
{

}

void tgb::TgBotHelper::setOnNewMessageListener(std::function<void(const std::vector<Message> &messages)> onNewMessageListener)
{
	m_onNewMessageListener = onNewMessageListener;
}

bool tgb::TgBotHelper::sendMessage(long chatId, std::string message)
{
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/sendMessage", 
			"chat_id=" + std::to_string(chatId) + "&text=" + message) };
	bool success{ response.second };
	if (success)
	{
		// Post was successful
		nlohmann::json jsn = nlohmann::json::parse(response.first);
		// Check if bot api reports successfully processing , too 
		success = jsn.value("ok", false);
	}
	return success; 
}

std::pair<std::vector<tgb::Message>, bool> tgb::TgBotHelper::getNewTextUpdates()
{
	// With specifying the last retrieved message + 1, we guarantee that we only get updates we dont have already get 
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/getUpdates", 
			"offset=" + std::to_string(m_lastRetrieved + 1)) };
	
	std::vector<Message> messages;
	bool success{ response.second };
	if (success)
	{
		// Post was successful
		nlohmann::json jsn = nlohmann::json::parse(response.first);
		// Check if bot api reports successfully processing , too 
		success = jsn.value("ok", false);
		if (success)
		{
			// Get all resulting updates
			nlohmann::json::array_t resultArr = jsn.value("result", nlohmann::json::array_t());
			for (auto entry : resultArr)
			{
				
				long updateId{ entry.value("update_id", -1L) };		
				// message		
				nlohmann::json jsonMessage = entry.value("message", nlohmann::json());
				long date{ jsonMessage.value("date", -1L) };
				long messageId{ jsonMessage.value("message_id", -1L) };
				std::string text{ jsonMessage.value("text", "") };
				// message->chat
				nlohmann::json jsonChat = jsonMessage.value("chat", nlohmann::json());
				long chatId{ jsonChat.value("id", -1L) };
				std::string chatFirstName{ jsonChat.value("first_name", "") };
				// message->from
				nlohmann::json jsonFrom = jsonMessage.value("from", nlohmann::json());
				long authorId{ jsonFrom.value("id", -1L) };
				std::string authorFirstName{ jsonFrom.value("first_name", "") };
				
				messages.push_back({ chatId, chatFirstName, date, authorId, 
						authorFirstName, messageId, text, updateId});

				// Make m_lastRetrieved update to actual update_id (When the update_id was in entry)
				if (updateId > -1) 
				{
					m_lastRetrieved = updateId;
				}
			}		
		}

	}
	return std::make_pair(messages, success);
}

void tgb::TgBotHelper::poll()
{
	std::pair<std::vector<Message>, bool> resultUpdates{ getNewTextUpdates() };
	std::vector<Message> messages{ resultUpdates.first };
	// Call the listener when there are new messages
	if (messages.size() > 0 && m_onNewMessageListener)
	{
		m_onNewMessageListener(messages);
	}
}
