#ifndef TELEBOTXX_BOTAPI_H
#define TELEBOTXX_BOTAPI_H

#include "User.hpp"
#include "Message.hpp"

#include <string>
#include <memory>

namespace telebotxx
{
	class BotApi
	{
	public:
		enum class ParseMode
		{
			Plain,
			Markdown,
			Html
		};

		/// \param [in] token bot's secret token
		BotApi(const std::string& token);

		~BotApi();

		/// \brief Get basic information about the bot
		/// \return User object with information about the bot
		User getMe();

		/// \brief Send text message
		/// \param [in] chat chat identifier
		/// \param [in] text message text
		/// \param [in] parseMode parse mode
		/// \return Message object, recieved from the server
		Message sendMessage(const std::string& chat, const std::string& text, ParseMode parseMode = ParseMode::Plain);

		/// \brief Send image
		/// \param [in] chat chat identifier
		/// \param [in] filename image location
		/// \param [in] caption optional photo caption
		/// \return Message object, recieved from the server
		Message sendPhoto(const std::string& chat, const std::string& filename, const std::string& caption = "");

		/// \brief Send image by URL
		/// \param [in] chat chat identifier
		/// \param [in] url image URL
		/// \param [in] caption optional photo caption
		/// \return Message object, recieved from the server
		Message sendPhotoUrl(const std::string& chat, const std::string& url, const std::string& caption = "");

	private:
		class Impl;
		std::unique_ptr<Impl> impl_;
	};
}

#endif // TELEBOTXX_BOTAPI_H
