#include "BotApi.hpp"

#include "Exception.hpp"
#include "JsonObjects.hpp"
#include "Logging.hpp"

#include <cpr/cpr.h>
#include <rapidjson/writer.h>

#include <iostream>
#include <sstream>

namespace telebotxx {

class BotApi::Impl
{
public:
	Impl(const std::string& token) : token_(token)
	{
		telegramMainUrl_ = "https://api.telegram.org/bot" + token_;
		botUser_ = getMe();
	}

	inline User getMe()
	{
		auto r = cpr::Get(cpr::Url{telegramMainUrl_ + "/getMe"});
		auto& response = r.text;

		if (debugMode)
			std::cout << "Response: " << response << std::endl;

		rapidjson::Document doc;
		doc.Parse(response.c_str());

		checkResponse(doc);
		return require<User>(doc, "result");
	}

	inline Message
	sendPhoto(const std::string& chat, const std::string& filename, const std::string& caption)
	{
		auto r = cpr::Post(
		    cpr::Url{telegramMainUrl_ + "/sendPhoto"},
		    cpr::Multipart{{"chat_id", chat}, {"photo", cpr::File{filename}}, {"caption", caption}});
		auto& response = r.text;

		if (debugMode)
			std::cout << "Response: " << response << std::endl;

		rapidjson::Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		checkResponse(doc);
		return *parseMessage(doc, "result", REQUIRED);
	}

	inline Message
	sendPhotoUrl(const std::string& chat, const std::string& url, const std::string& caption)
	{
		// Construct JSON body
		using namespace rapidjson;
		StringBuffer s;
		Writer<StringBuffer> writer(s);

		writer.StartObject();
		writer.String("chat_id");
		writer.String(chat.c_str());
		writer.String("photo");
		writer.String(url.c_str());
		writer.String("caption");
		writer.String(caption.c_str());
		writer.EndObject();

		std::string request = s.GetString();

		auto r = cpr::Post(cpr::Url{telegramMainUrl_ + "/sendPhoto"},
		                   cpr::Header{{"Content-Type", "application/json"}}, cpr::Body{request});
		auto& response = r.text;

		if (debugMode)
			std::cout << "Response: " << response << std::endl;

		rapidjson::Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		checkResponse(doc);
		return *parseMessage(doc, "result", REQUIRED);
	}

	Updates getUpdates(int offset, unsigned short limit, unsigned timeout)
	{
		// Construct JSON body
		using namespace rapidjson;
		StringBuffer s;
		Writer<StringBuffer> writer(s);

		writer.StartObject();
		if (offset != 0)
		{
			writer.String("offset");
			writer.Int(offset);
		}
		if (limit != 0)
		{
			writer.String("limit");
			writer.Uint(limit);
		}
		if (timeout != 0)
		{
			writer.String("timeout");
			writer.Uint(timeout);
		}
		writer.EndObject();

		std::string request = s.GetString();

		auto r = cpr::Post(cpr::Url{telegramMainUrl_ + "/getUpdates"},
		                   cpr::Header{{"Content-Type", "application/json"}}, cpr::Body{request});
		auto& response = r.text;

		if (debugMode)
			std::cout << "Response: " << response << std::endl;

		rapidjson::Document doc;
		doc.Parse(response.c_str());

		checkResponse(doc);
		return parseUpdates(doc, "result");
	}

	std::string getTelegramMainUrl() const { return telegramMainUrl_; }

private:
	std::string token_;
	std::string telegramMainUrl_;
	User botUser_;
};

BotApi::BotApi(const std::string& token) : impl_(std::make_unique<Impl>(token))
{
}

BotApi::~BotApi() = default;

User BotApi::getMe()
{
	return impl_->getMe();
}

Message BotApi::sendMessage(ChatId&& chatId, Text&& text)
{
	SendMessageRequest request(getTelegramMainUrl(), std::forward<ChatId>(chatId),
	                           std::forward<Text>(text));
	return request.execute();
}

Message BotApi::sendPhoto(ChatId&& chatId, Photo&& photo)
{
	SendPhotoRequest request(getTelegramMainUrl(), std::forward<ChatId>(chatId),
	                         std::forward<Photo>(photo));
	return request.execute();
}

Updates BotApi::getUpdates(int offset, unsigned short limit, unsigned int timeout)
{
	return impl_->getUpdates(offset, limit, timeout);
}

std::string BotApi::getTelegramMainUrl() const
{
	return impl_->getTelegramMainUrl();
}

} // namespace telebotxx
