#ifndef TELEBOTXX_BOTAPI_H
#define TELEBOTXX_BOTAPI_H

#include <string>

namespace telebotxx
{
	class BotApi
	{
	public:
		/// \param [in] token bot's secret token
		BotApi(const std::string& token);

		/// \brief Send text message
		/// \param [in] chat chat identifier
		/// \param [in] text message text
		void sendMessage(const std::string& chat, const std::string& text);

		/// \brief Send image
		/// \param [in] chat chat identifier
		/// \param [in] file opened image stream
		/// \param [in] caption optional photo caption
		void sendPhoto(const std::string& chat, const std::istream& file, const std::string& caption = "");


	private:
		std::string token_;
		std::string telegramMainUrl_;
	};
}

#endif // TELEBOTXX_BOTAPI_H
