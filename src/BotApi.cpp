#include <telebotxx/BotApi.hpp>
#include <telebotxx/Exception.hpp>
#include <telebotxx/Logging.hpp>

#include <iostream>
#include <sstream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>

#include <cpr/cpr.h>

namespace telebotxx
{
	const rapidjson::Value& parseResponse(const rapidjson::Document& doc)
	{
		using namespace rapidjson;
		if (!doc.IsObject())
			throw ParseError("Object expected");

		// Get status
		if (!doc.HasMember("ok") || !doc["ok"].IsBool())
			throw ParseError("Field 'ok' not found or has invalid type");
		bool ok = doc["ok"].GetBool();

		if (ok)
		{
			if (!doc.HasMember("result") || !doc["result"].IsObject())
				throw ParseError("Field 'result' not found or has invalid type");
			return doc["result"];
		} else
		{
			if (!doc.HasMember("error_code") || !doc["error_code"].IsInt())
				throw ParseError("Field 'error_code' not found or has invalid type");
			int code = doc["error_code"].GetInt();

			if (!doc.HasMember("description") || !doc["description"].IsString())
				throw ParseError("Field 'description' not found or has invalid type");
			std::string description(doc["description"].GetString());

			throw ApiError(code, description);
		}
	}

	User parseUser(const rapidjson::Value& obj)
	{
		if (!obj.HasMember("id") || !obj["id"].IsInt())
			throw ParseError("Field 'id' not found or has invalid type");
		int id = obj["id"].GetInt();

		if (!obj.HasMember("first_name") || !obj["first_name"].IsString())
			throw ParseError("Field 'first_name' not found or has invalid type");
		std::string firstName(obj["first_name"].GetString());

		std::string lastName;
		if (obj.HasMember("last_name"))
		{
			if (obj["last_name"].IsString())
				lastName = obj["last_name"].GetString();
			else
				throw ParseError("Field 'last_name' has invalid type");
		}

		std::string username;
		if (obj.HasMember("username"))
		{
			if (obj["username"].IsString())
				username = obj["username"].GetString();
			else
				throw ParseError("Field 'username' has invalid type");
		}

		return User(id, firstName, lastName, username);
	}
}

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

		using namespace rapidjson;
		Document doc;
		doc.Parse(response.c_str());

		return parseUser(parseResponse(doc));
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

		using namespace rapidjson;
		Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		parseResponse(doc);
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

		using namespace rapidjson;
		Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		parseResponse(doc);
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

		using namespace rapidjson;
		Document doc;
		doc.Parse(response.c_str());

		/// \todo Parse message
		parseResponse(doc);
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
