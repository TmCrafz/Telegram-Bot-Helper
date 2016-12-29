#ifndef TGB_TGBOTHELPER_HPP
#define TGB_TGBOTHELPER_HPP
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
			explicit TgBotHelper(std::string token);
			
			void setOnNewMessageListener(std::function<void(const std::vector<Message> &messages)> onNewMessageListener);

			bool sendMessage(long chatId, std::string message);
			// Returns the Messages and a bool which is true when the api call was successful
			std::pair<std::vector<Message>, bool> getNewTextUpdates();
			
			// Retrieve updates and call listeners
			void poll();

	};
}
#endif // TGB_TGBOTHELPER_HPP
