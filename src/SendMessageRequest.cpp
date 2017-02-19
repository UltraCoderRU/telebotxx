#include <telebotxx/SendMessageRequest.hpp>
#include <telebotxx/Logging.hpp>
#include "JsonObjects.hpp"
#include "ReplyMarkup.hpp"

#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

#include <iostream>
#include <boost/optional.hpp>

namespace telebotxx {

class SendMessageRequest::Impl
{
public:
	Impl(const std::string& telegramMainUrl, const ChatId& chat, const Text& text)
		: telegramMainUrl_(telegramMainUrl), chatId_(chat), text_(text)
	{
	}

	void setParseMode(ParseMode mode)
	{
		parseMode_ = mode;
	}

	void setDisableWebPagePreview(const DisableWebPagePreview& disableWebPagePreview)
	{
		disableWebPagePreview_ = disableWebPagePreview;
	}

	void setDisableNotification(const DisableNotification& disableNotification)
	{
		disableNotification_ = disableNotification;
	}

	void setReplyToMessageId(const ReplyTo& replyToMessageId)
	{
		replyToMessageId_ = replyToMessageId;
	}

	void setReplyMarkup(const ReplyMarkup& replyMarkup)
	{
		replyMarkup_ = replyMarkup;
	}

	Message execute()
	{
		// Construct JSON body
		using namespace rapidjson;
		StringBuffer s;
		Writer<StringBuffer> writer(s);

		writer.StartObject();

		// Add chat_id
		writer.String("chat_id");
		if (chatId_.getType() == ChatId::Type::Id)
			writer.Int(chatId_.getId());
		else
			writer.String(chatId_.getUsername().c_str());

		writer.String("text");
		writer.String(text_.getValue().c_str());

		// Add parse_mode
		if (parseMode_)
		{
			writer.String("parse_mode");
			writer.String(
				(parseMode_ == ParseMode::Markdown) ? "Markdown" : (parseMode_ == ParseMode::Html) ? "HTML" : "Plain");
		}

		// Add disable_web_page_preview
		if (disableWebPagePreview_)
		{
			writer.String("disable_web_page_preview");
			writer.Bool(disableWebPagePreview_->getValue());
		}

		// Add disable_notification
		if (disableNotification_)
		{
			writer.String("disable_notification");
			writer.Bool(disableNotification_->getValue());
		}

		// Add reply_to_message_id
		if (replyToMessageId_)
		{
			writer.String("reply_to_message_id");
			writer.Int(replyToMessageId_->value());
		}

		// Add reply_markup
		if (replyMarkup_)
		{
			writer.String("reply_markup");
			writeReplyMarkup(writer, *replyMarkup_);
		}

		writer.EndObject();

		// Execute POST and get response
		std::string request = s.GetString();
		if (debugMode)
			std::cout << "Request: " << request << std::endl;
		auto r = cpr::Post(cpr::Url{telegramMainUrl_ + "/sendMessage"},
						   cpr::Header{{"Content-Type", "application/json"}},
						   cpr::Body{request}
		);
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
	Text text_;
	boost::optional<ParseMode> parseMode_;
	boost::optional<DisableWebPagePreview> disableWebPagePreview_;
	boost::optional<DisableNotification> disableNotification_;
	boost::optional<ReplyTo> replyToMessageId_;
	boost::optional<ReplyMarkup> replyMarkup_;
};

SendMessageRequest::SendMessageRequest(const std::string& telegramMainUrl, const ChatId& chat, const Text& text)
	: impl_(std::make_unique<Impl>(telegramMainUrl, chat, text))
{
}

SendMessageRequest::~SendMessageRequest()
{
}

void SendMessageRequest::setParseMode(ParseMode mode)
{
	impl_->setParseMode(mode);
}

void SendMessageRequest::setDisableWebPagePreview(const DisableWebPagePreview& disableWebPagePreview)
{
	impl_->setDisableWebPagePreview(disableWebPagePreview);
}

void SendMessageRequest::setDisableNotification(const DisableNotification& disableNotification)
{
	impl_->setDisableNotification(disableNotification);
}

void SendMessageRequest::setReplyToMessageId(const ReplyTo& replyToMessageId)
{
	impl_->setReplyToMessageId(replyToMessageId);
}

void SendMessageRequest::setReplyMarkup(const ReplyMarkup& replyMarkup)
{
	impl_->setReplyMarkup(replyMarkup);
}

void SendMessageRequest::setOption(ParseMode mode)
{
	setParseMode(mode);
}

void SendMessageRequest::setOption(const DisableWebPagePreview& disableWebPagePreview)
{
	setDisableWebPagePreview(disableWebPagePreview);
}

void SendMessageRequest::setOption(const DisableNotification& disableNotification)
{
	setDisableNotification(disableNotification);
}

void SendMessageRequest::setOption(const ReplyTo& replyToMessageId)
{
	setReplyToMessageId(replyToMessageId);
}

void SendMessageRequest::setOption(const ReplyMarkup& replyMarkup)
{
	setReplyMarkup(replyMarkup);
}

Message SendMessageRequest::execute()
{
	return impl_->execute();
}

}
