#ifndef TELEBOTXX_SEND_PHOTO_REQUEST_HPP
#define TELEBOTXX_SEND_PHOTO_REQUEST_HPP

#include "Message.hpp"
#include "RequestOptions.hpp"

#include <memory>
#include <string>

namespace telebotxx {

class SendPhotoRequest
{
public:
	SendPhotoRequest(const std::string& telegramMainUrl, const ChatId& chat, const Photo& photo);
	~SendPhotoRequest();

	void setCaption(const Caption& caption);
	void setDisableNotification(const DisableNotification& disableNotification);
	void setReplyToMessageId(const ReplyTo& replyToMessageId);

	void setOption(const Caption& caption);
	void setOption(const DisableNotification& disableNotification);
	void setOption(const ReplyTo& replyToMessageId);

	Message execute();

private:
	class Impl;
	std::unique_ptr<Impl> impl_;
};

} // namespace telebotxx

#endif // TELEBOTXX_SEND_PHOTO_REQUEST_HPP
