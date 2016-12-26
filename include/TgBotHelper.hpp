#ifndef TGBOTHELPER_HPP
#define TGBOTHELPER_HPP
#include <string>

namespace tgb 
{
	class TgBotHelper
	{
		private:
			std::string m_token;

		public:
			explicit TgBotHelper(std::string token);
			void sendMessage(std::string chatId, std::string message);
	};
}
#endif // TGBOTHELPER_HPP
