#include "../include/TgBotHelper.hpp"
#include "../include/CurlHelper.hpp"
#include "../include/libs/json.hpp"
#include <iostream>

tgb::TgBotHelper::TgBotHelper(std::string token)
: m_token{ token }
, m_lastRetrieved{ -1L }
{

}

bool tgb::TgBotHelper::sendMessage(std::string chatId, std::string message)
{
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/sendMessage", 
			"chat_id=" + chatId + "&text=" + message) };
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

std::string tgb::TgBotHelper::getNewTextUpdates()
{
	// With specifying the last retrieved message + 1, we guarantee that we only get updates we dont have already get 
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/getUpdates", 
			"offset=" + std::to_string(m_lastRetrieved + 1)) };
	
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
				int updateId = entry.value("update_id", -1L);
				std::cout << "UpdateId: " << updateId << std::endl;
				std::cout << "Entry: \n" << entry << std::endl;
				// Make m_lastRetrieved update to actual update_id (When the update_id was in entry)
				if (updateId > -1) 
				{
					m_lastRetrieved = updateId;
				}
			}		
		}

	}
	return "";
}
