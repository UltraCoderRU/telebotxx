#ifndef TELEBOTXX_BOTAPI_H
#define TELEBOTXX_BOTAPI_H

#include "User.hpp"

#include <string>
#include <memory>

namespace telebotxx
{
	class BotApi
	{
	public:
		/// \param [in] token bot's secret token
		BotApi(const std::string& token);

		~BotApi();

		/// \brief Get basic information about the bot
		/// \return User object with information about the bot
		User getMe();

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
		class Impl;
		std::unique_ptr<Impl> impl_;
	};
}

#endif // TELEBOTXX_BOTAPI_H
