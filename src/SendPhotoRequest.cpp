#include <telebotxx/SendPhotoRequest.hpp>

#include <telebotxx/Logging.hpp>
#include "JsonObjects.hpp"

#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

#include <iostream>

using namespace telebotxx;

class SendPhotoRequest::Impl
{
public:
	Impl(const std::string& telegramMainUrl, const ChatId& chat, const Photo& photo)
		: telegramMainUrl_(telegramMainUrl), chatId_(chat), photo_(photo)
	{
	}

	void setCaption(const Caption& caption)
	{
		caption_ = caption;
	}

	void setDisableNotification(const DisableNotification& disableNotification)
	{
		disableNotification_ = disableNotification;
	}

	void setReplyToMessageId(const ReplyTo& replyToMessageId)
	{
		replyToMessageId_ = replyToMessageId;
	}

	Message execute()
	{
		cpr::Multipart multipart{};

		// Add chat_id
		if (chatId_.getType() == ChatId::Type::Id)
			multipart.parts.push_back({"chat_id", chatId_.getId()});
		else
			multipart.parts.push_back({"chat_id", chatId_.getUsername()});

		// Add photo
		if (photo_.getType() == Photo::Type::Id)
			multipart.parts.push_back({"photo", photo_.getId()});
		else if (photo_.getType() == Photo::Type::Buffer)
		{
			const char* data = photo_.getBuffer().data();
			std::size_t size = photo_.getBuffer().size();
			const std::string filename = photo_.getBuffer().filename();
			multipart.parts.push_back({"photo", cpr::Buffer(data, data + size, filename)});
		}
		else if (photo_.getType() == Photo::Type::File)
			multipart.parts.push_back({"photo", cpr::File(photo_.getFile().getFilename())});
		else if (photo_.getType() == Photo::Type::Url)
			multipart.parts.push_back({"photo", photo_.getUrl().getUrl()});

		// Add caption
		if (caption_)
			multipart.parts.push_back({"caption", *caption_});

		// Add disable_notification
		if (disableNotification_)
			multipart.parts.push_back({"disable_notification", disableNotification_->value()});

		// Add reply_to_message_id
		if (replyToMessageId_)
			multipart.parts.push_back({"reply_to_message_id", replyToMessageId_->value()});

		auto r = cpr::Post(cpr::Url{telegramMainUrl_ + "/sendPhoto"}, multipart);
		auto& response = r.text;

		if (debugMode)
			std::cout << "Response: " << response << std::endl;

		rapidjson::Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		checkResponse(doc);
		return *parseMessage(doc, "result", REQUIRED);
	}

private:
	std::string telegramMainUrl_;
	ChatId chatId_;
	Photo photo_;
	boost::optional<Caption> caption_;
	boost::optional<DisableNotification> disableNotification_;
	boost::optional<ReplyTo> replyToMessageId_;
};

SendPhotoRequest::SendPhotoRequest(const std::string& telegramMainUrl, const ChatId& chat, const Photo& photo)
	: impl_(std::make_unique<Impl>(telegramMainUrl, chat, photo))
{
}

SendPhotoRequest::~SendPhotoRequest()
{
}

void SendPhotoRequest::setCaption(const Caption& caption)
{
	impl_->setCaption(caption);
}

void SendPhotoRequest::setDisableNotification(const DisableNotification& disableNotification)
{
	impl_->setDisableNotification(disableNotification);
}

void SendPhotoRequest::setReplyToMessageId(const ReplyTo& replyToMessageId)
{
	impl_->setReplyToMessageId(replyToMessageId);
}

void SendPhotoRequest::setOption(const Caption& caption)
{
	setCaption(caption);
}

void SendPhotoRequest::setOption(const DisableNotification& disableNotification)
{
	setDisableNotification(disableNotification);
}

void SendPhotoRequest::setOption(const ReplyTo& replyToMessageId)
{
	setReplyToMessageId(replyToMessageId);
}

Message SendPhotoRequest::execute()
{
	return impl_->execute();
}
