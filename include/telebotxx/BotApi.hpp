#ifndef TELEBOTXX_BOTAPI_HPP
#define TELEBOTXX_BOTAPI_HPP

#include "User.hpp"
#include "Message.hpp"
#include "Update.hpp"
#include "SendMessageRequest.hpp"
#include "SendPhotoRequest.hpp"

#include <string>
#include <memory>

namespace telebotxx {

template <typename RequestType, typename T>
void setRequestOption(RequestType& request, T t)
{
	request.setOption(t);
}

template <typename RequestType, typename T, typename... Ts>
void setRequestOption(RequestType& request, T&& t, Ts&&... ts)
{
	setRequestOption(request, std::forward<T>(t));
	setRequestOption(request, std::forward<Ts>(ts)...);
};

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
	/// \param chatId chat identifier
	/// \param text text
	/// \return Message object, recieved from the server
	Message sendMessage(ChatId&& chatId, Text&& text);

	/// \brief Send text message
	/// \param chatId chat identifier
	/// \param text text
	/// \param args parameters
	/// \return Message object, recieved from the server
	template <typename... Ts>
	Message sendMessage(ChatId&& chatId, Text&& text, Ts&&... args)
	{
		SendMessageRequest request(getTelegramMainUrl(), std::forward<ChatId>(chatId), std::forward<Text>(text));
		setRequestOption(request, std::forward<Ts>(args)...);
		return request.execute();
	}

	/// \brief Send image
	/// \param [in] chatId chat identifier
	/// \param [in] photo photo
	/// \return Message object, recieved from the server
	Message sendPhoto(ChatId&& chatId, Photo&& photo);

	/// \brief Send image
	/// \param [in] chatId chat identifier
	/// \param [in] photo photo
	/// \param [in] args parameters
	/// \return Message object, recieved from the server
	template <typename... Ts>
	Message sendPhoto(ChatId&& chatId, Photo&& photo, Ts&&... args)
	{
		SendPhotoRequest request(getTelegramMainUrl(), std::forward<ChatId>(chatId), std::forward<Photo>(photo));
		setRequestOption(request, std::forward<Ts>(args)...);
		return request.execute();
	}

	/// \brief Get updates using long polling
	/// \param offset identifier of the first update to be returned
	/// \param limit maximum number of updates to be retrieved
	/// \param timeout timeout in seconds for long polling
	/// \return Updates (vector of Update)
	/// \todo allowed_updates
	Updates getUpdates(int offset = 0, unsigned short limit = 0, unsigned timeout = 0);

private:
	std::string getTelegramMainUrl() const;

	class Impl;
	std::unique_ptr<Impl> impl_;
};

}

#endif // TELEBOTXX_BOTAPI_HPP
