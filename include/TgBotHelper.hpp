#ifndef TGB_TGBOTHELPER_HPP
#define TGB_TGBOTHELPER_HPP
#include <string>

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
			std::string getNewTextUpdates();

	};
}
#endif // TGB_TGBOTHELPER_HPP
