#include "../include/TgBotHelper.hpp"
#include "../include/CurlHelper.hpp"
#include <iostream>

tgb::TgBotHelper::TgBotHelper(const std::string token)
: m_token{ token }
, m_lastRetrieved{ -1L }
{

}

void tgb::TgBotHelper::setOnNewMessageListener(std::function<void(const std::vector<Message> &messages)> onNewMessageListener)
{
	m_onNewMessageListener = onNewMessageListener;
}

bool tgb::TgBotHelper::sendMessage(const long chatId, const std::string &message) const
{
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/sendMessage", 
			"chat_id=" + std::to_string(chatId) + "&text=" + message) };
	bool success{ response.second && isResponseOk(response.first) };
	return success; 
}

bool tgb::TgBotHelper::sendPhoto(const long chatId, const std::string &fileName) const
{
	std::pair<std::string, bool> response{ CurlHelper::fileFormPost("https://api.telegram.org/bot" + m_token + 
			"/sendPhoto?chat_id=" +  std::to_string(chatId), "photo", fileName) };
	
	bool success{ response.second && isResponseOk(response.first) };
	return success; 
}

bool tgb::TgBotHelper::savePhoto(const std::string &fileId, const std::string fileName) const
{
	// Get info about file
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/getFile", 
			"file_id=" + fileId) };
	
	if(!response.second)
	{
		return false;
	}
	nlohmann::json jsn = nlohmann::json::parse(response.first);
	const std::string filePath{ jsn.value("result", nlohmann::json()).value("file_path", "") };
	// if there is no filePath in the result or the file path is empty there went something wrong
	if (filePath.empty())
	{
		return false;
	}
	// Download the file
	return CurlHelper::downloadAndSafeFile("https://api.telegram.org/file/bot" + m_token + "/" + filePath, fileName);	
}

std::pair<std::vector<tgb::Message>, bool> tgb::TgBotHelper::getNewTextUpdates()
{
	// With specifying the last retrieved message + 1, we guarantee that we only get updates we dont have already get 
	std::pair<std::string, bool> response{ CurlHelper::simplePost("https://api.telegram.org/bot" + m_token + "/getUpdates", 
			"offset=" + std::to_string(m_lastRetrieved + 1)) };
	
	std::vector<Message> messages;
	bool success{ response.second && isResponseOk(response.first) };
	if (success)
	{
		nlohmann::json jsn = nlohmann::json::parse(response.first);
		// Get all resulting updates
		nlohmann::json::array_t resultArr = jsn.value("result", nlohmann::json::array_t());
		for (auto entry : resultArr)
		{
			
			long updateId{ entry.value("update_id", -1L) };		
			// message		
			nlohmann::json jsonMessage = entry.value("message", nlohmann::json());
			long messageId{ jsonMessage.value("message_id", -1L) };
			long date{ jsonMessage.value("date", -1L) };
			std::string text{ jsonMessage.value("text", "") };
			// message->chat
			std::shared_ptr<Message::Chat> chat{ getChatFromJson(jsonMessage) };

			// message->from.
			std::shared_ptr<Message::User> user{ getUserFromJson(jsonMessage) };
			// message->photo
			std::shared_ptr<Message::Photo> photo { getPhotoFromJson(jsonMessage) };

			messages.push_back({ messageId, date, text, std::move(chat), std::move(user), std::move(photo) });

			// Make m_lastRetrieved update to actual update_id (When the update_id was in entry)
			if (updateId > -1) 
			{
				m_lastRetrieved = updateId;
			}
		}		
	}
	return std::make_pair(messages, success);
}

void tgb::TgBotHelper::handleUpdates()
{
	std::pair<std::vector<Message>, bool> resultUpdates{ getNewTextUpdates() };
	std::vector<Message> messages{ resultUpdates.first };
	// Call the listener when there are new messages
	if (messages.size() > 0 && m_onNewMessageListener)
	{
		m_onNewMessageListener(messages);
	}
}


std::shared_ptr<tgb::Message::Chat> tgb::TgBotHelper::getChatFromJson(const nlohmann::json &json) const
{

	std::shared_ptr<Message::Chat> chat{ nullptr };
	if (json.count("from") > 0)
	{
		nlohmann::json jsonChat = json.value("chat", nlohmann::json());
		long id{ jsonChat.value("id", -1L) };
		std::string type{ jsonChat.value("type", "") };
		std::string title{ jsonChat.value("title", "") };
		std::string username{ jsonChat.value("username", "") };
		std::string firstName{ jsonChat.value("first_name", "") };
		std::string lastName{ jsonChat.value("last_name", "") };
		bool allMembersAdmins{ jsonChat.value("all_members_are_administrators", false) };
		chat = std::make_shared<Message::Chat>(id, type,
			title, username, firstName, lastName, allMembersAdmins);
	}
	return std::move(chat);
		
}

std::shared_ptr<tgb::Message::User> tgb::TgBotHelper::getUserFromJson(const nlohmann::json &json) const
{
	std::shared_ptr<Message::User> user{ nullptr };
	if (json.count("from") > 0)
	{
		nlohmann::json jsonFrom = json.value("from", nlohmann::json());
		long id{ jsonFrom.value("id", -1L) };
		std::string username{ jsonFrom.value("username", "") };
		std::string firstName{ jsonFrom.value("first_name", "") };
		std::string lastName{ jsonFrom.value("last_name", "") };
		user = std::make_shared<Message::User>(id, username,
			firstName, lastName);
	}
	return std::move(user);
}


std::shared_ptr<tgb::Message::Photo> tgb::TgBotHelper::getPhotoFromJson(const nlohmann::json &json) const
{
	std::shared_ptr<Message::Photo> photo{ nullptr };
	if (json.count("photo") > 0)
	{
		std::vector<Message::PhotoSize> photoSizes;
		nlohmann::json::array_t jsonPhotoArr = json.value("photo", nlohmann::json::array_t());
		for (auto jsonPhoto: jsonPhotoArr)
		{
			std::string fileId{ jsonPhoto.value("file_id", "") };
			int width{ jsonPhoto.value("width", 0) };
			int height{ jsonPhoto.value("height", 0) };
			int fileSize{ jsonPhoto.value("file_size", 0) };
			photoSizes.push_back({ fileId, width, height, fileSize });
		}		
		photo = std::make_shared<Message::Photo>(photoSizes);
	}
	return std::move(photo);
}

bool tgb::TgBotHelper::isResponseOk(const std::string &response) const
{
	nlohmann::json jsn = nlohmann::json::parse(response);
	// Check if bot api reports successfully processing , too 
	return jsn.value("ok", false);
}
