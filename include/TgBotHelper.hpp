#ifndef TGB_TGBOTHELPER_HPP
#define TGB_TGBOTHELPER_HPP
#include "libs/json.hpp"
#include <functional>
#include "Message.hpp"
#include <string>
#include <utility>
#include <vector>

namespace tgb 
{
	class TgBotHelper
	{
		private:
			std::string m_token;
			// The id of the last retrieved update
			long m_lastRetrieved;

			std::function<void(const std::vector<Message> &messages)> m_onNewMessageListener;
		public:
			explicit TgBotHelper(const std::string token);
			
			// Set Listener which is called when a new messaged receive
			void setOnNewMessageListener(std::function<void(const std::vector<Message> &messages)> onNewMessageListener);
			// Send a simple text message to the chat with given chatId
			bool sendTextMessage(const long chatId, const std::string &message) const;
			// Send a photo to the chat with given chatId
			bool sendPhotoMessage(const long chatId, const std::string &fileName) const;
			// Save the photo with the given fileId in the given fileName(path)
			bool savePhoto(const std::string &fileId, const std::string fileName) const;
			// Returns the messages and a bool which is true when the api call was successful
			std::pair<std::vector<Message>, bool> getNewUpdates();

			// Retrieve updates and call listeners
			void handleUpdates();

		private:
			std::shared_ptr<Message::Chat> getChatFromJson(const nlohmann::json &json) const;
			std::shared_ptr<Message::User> getUserFromJson(const nlohmann::json &json) const;
			std::shared_ptr<Message::Photo> getPhotoFromJson(const nlohmann::json &json) const;
			// Returns true if the given string contains that the action of the response was successfully
			bool isResponseOk(const std::string &response) const;

	};
}
#endif // TGB_TGBOTHELPER_HPP
