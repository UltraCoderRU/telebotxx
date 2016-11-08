#include <telebotxx/BotApi.hpp>
#include <telebotxx/Exception.hpp>
#include <telebotxx/Logging.hpp>
#include "JsonObjects.hpp"

#include <iostream>
#include <sstream>

#include <rapidjson/writer.h>

#include <cpr/cpr.h>

using namespace telebotxx;

class BotApi::Impl
{
public:
	Impl(const std::string& token)
		: token_(token)
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

		parseResponse(doc);
		return *parseUser(doc, "result", REQUIRED);
	}

	inline void sendMessage(const std::string& chat, const std::string& text, ParseMode parseMode)
	{
		// Construct JSON body
		using namespace rapidjson;
		StringBuffer s;
		Writer<StringBuffer> writer(s);

		writer.StartObject();
		writer.String("chat_id");
		writer.String(chat.c_str());
		writer.String("text");
		writer.String(text.c_str());
		if (parseMode != ParseMode::Plain)
		{
			writer.String("parse_mode");
			writer.String((parseMode == ParseMode::Markdown) ? "Markdown" : "HTML");
		}
		writer.EndObject();

		std::string request = s.GetString();

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
		parseResponse(doc);
		MessagePtr message = parseMessage(doc, "result", REQUIRED);
	}

	inline void sendPhoto(const std::string& chat, const std::string& filename, const std::string& caption)
	{
		auto r = cpr::Post(cpr::Url{telegramMainUrl_ + "/sendPhoto"},
						   cpr::Multipart{{"chat_id", chat},
										  {"photo", cpr::File{filename}},
										  {"caption", caption}
						   }
		);
		auto& response = r.text;

		if (debugMode)
			std::cout << "Response: " << response << std::endl;

		rapidjson::Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		parseResponse(doc);
		MessagePtr message = parseMessage(doc, "result", REQUIRED);
	}

	inline void sendPhotoUrl(const std::string& chat, const std::string& url, const std::string& caption)
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
						   cpr::Header{{"Content-Type", "application/json"}},
						   cpr::Body{request}
		);
		auto& response = r.text;

		if (debugMode)
			std::cout << "Response: " << response << std::endl;

		rapidjson::Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		parseResponse(doc);
		MessagePtr message = parseMessage(doc, "result", REQUIRED);
	}

private:

	std::string token_;
	std::string telegramMainUrl_;
	User botUser_;
};

BotApi::BotApi(const std::string& token)
	: impl_(std::make_unique<Impl>(token))
{
}

BotApi::~BotApi() = default;

User BotApi::getMe()
{
	return impl_->getMe();
}

void BotApi::sendMessage(const std::string& chat, const std::string& text, ParseMode parseMode)
{
	return impl_->sendMessage(chat, text, parseMode);
}

void BotApi::sendPhoto(const std::string& chat, const std::string& filename, const std::string& caption)
{
	return impl_->sendPhoto(chat, filename, caption);
}

void BotApi::sendPhotoUrl(const std::string& chat, const std::string& url, const std::string& caption)
{
	return impl_->sendPhotoUrl(chat, url, caption);
}
