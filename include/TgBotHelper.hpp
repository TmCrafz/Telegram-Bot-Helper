#ifndef TGB_TGBOTHELPER_HPP
#define TGB_TGBOTHELPER_HPP
#include <vector>
#include "Message.hpp"
#include <string>
#include <utility>

namespace tgb 
{
	class TgBotHelper
	{
		private:
			std::string m_token;
			// The id of the last retrieved update
			long m_lastRetrieved;
		public:
			explicit TgBotHelper(std::string token);

			bool sendMessage(std::string chatId, std::string message);
			// Returns the Messages and a bool which is true when the api call was successful
			std::pair<std::vector<Message>, bool> getNewTextUpdates();

	};
}
#endif // TGB_TGBOTHELPER_HPP
