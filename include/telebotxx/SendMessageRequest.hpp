#ifndef TELEBOTXX_SEND_MESSAGE_REQUEST_HPP
#define TELEBOTXX_SEND_MESSAGE_REQUEST_HPP

#include <telebotxx/RequestOptions.hpp>
#include <telebotxx/Message.hpp>

#include <string>
#include <memory>

namespace telebotxx {

class SendMessageRequest
{
public:
	SendMessageRequest(const std::string& telegramMainUrl, const ChatId& chat, const Text& text);
	~SendMessageRequest();

	void setParseMode(ParseMode mode);
	void setDisableWebPagePreview(const DisableWebPagePreview& disableWebPagePreview);
	void setDisableNotification(const DisableNotification& disableNotification);
	void setReplyToMessageId(const ReplyTo& replyToMessageId);
	void setReplyMarkup(const ReplyMarkup& replyMarkup);

	void setOption(ParseMode mode);
	void setOption(const DisableWebPagePreview& disableWebPagePreview);
	void setOption(const DisableNotification& disableNotification);
	void setOption(const ReplyTo& replyToMessageId);
	void setOption(const ReplyMarkup& replyMarkup);

	Message execute();

private:
	class Impl;
	std::unique_ptr<Impl> impl_;
};

}

#endif // TELEBOTXX_SEND_MESSAGE_REQUEST_HPP
