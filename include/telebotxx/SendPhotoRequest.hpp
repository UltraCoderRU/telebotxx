#ifndef TELEBOTXX_SEND_PHOTO_REQUEST_HPP
#define TELEBOTXX_SEND_PHOTO_REQUEST_HPP

#include <telebotxx/RequestOptions.hpp>
#include <telebotxx/Message.hpp>

#include <boost/optional.hpp>

#include <string>
#include <memory>

namespace telebotxx
{
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
}

#endif // TELEBOTXX_SEND_PHOTO_REQUEST_HPP
