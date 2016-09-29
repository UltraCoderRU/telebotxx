#include <telebotxx/BotApi.hpp>
#include <telebotxx/Exception.hpp>

#include <sstream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/istreamwrapper.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <boost/log/trivial.hpp>

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
		curlpp::Easy request;
		std::stringstream ss;

		request.setOpt(new curlpp::Options::Url(telegramMainUrl_ + "/getMe"));
		request.setOpt(new curlpp::Options::Verbose(false));
		request.setOpt(new curlpp::options::WriteStream(&ss));
		request.perform();

		BOOST_LOG_TRIVIAL(debug) << ss.str();

		using namespace rapidjson;
		IStreamWrapper isw(ss);
		Document doc;
		doc.ParseStream(isw);

		return parseUser(parseResponse(doc));
	}

	inline void sendMessage(const std::string& chat, const std::string& text)
	{
		// Construct JSON body and istream
		using namespace rapidjson;
		StringBuffer s;
		Writer<StringBuffer> writer(s);

		writer.StartObject();
		writer.String("chat_id");
		writer.String(chat.c_str());
		writer.String("text");
		writer.String(text.c_str());
		writer.EndObject();

		std::istringstream requestStream(s.GetString());
		BOOST_LOG_TRIVIAL(debug) << requestStream.str();
		auto size = requestStream.str().size();

		std::stringstream responseStream;

		// Construct HTTP request
		curlpp::Easy request;
		std::list<std::string> headers;

		// Content-Type
		headers.push_back("Content-Type: application/json");

		// Content-Length
		{
			std::ostringstream ss;
			ss << "Content-Length: " << size;
			headers.push_back(ss.str());
		}

		// Set options
		request.setOpt(new curlpp::Options::Url(telegramMainUrl_ + "/sendMessage"));
		request.setOpt(new curlpp::Options::Verbose(false));
		request.setOpt(new curlpp::Options::ReadStream(&requestStream));
		request.setOpt(new curlpp::options::WriteStream(&responseStream));
		request.setOpt(new curlpp::Options::InfileSize(size));
		request.setOpt(new curlpp::options::HttpHeader(headers));
		request.setOpt(new curlpp::Options::Post(true));

		// Perform request
		request.perform();

		BOOST_LOG_TRIVIAL(debug) << responseStream.str();

		using namespace rapidjson;
		IStreamWrapper isw(responseStream);
		Document doc;
		doc.ParseStream(isw);

		/// \todo Parse message
		parseResponse(doc);
	}

	inline void sendPhoto(const std::string& chat, const std::string& filename, const std::string& caption)
	{
		// Construct HTTP request
		curlpp::Easy request;
		std::stringstream responseStream;

		{
			// Forms takes ownership of pointers!
			curlpp::Forms formParts;
			formParts.push_back(new curlpp::FormParts::Content("chat_id", chat));
			formParts.push_back(new curlpp::FormParts::File("photo", filename));
			formParts.push_back(new curlpp::FormParts::Content("caption", caption));
			request.setOpt(new curlpp::options::HttpPost(formParts));
		}

		// Set options
		request.setOpt(new curlpp::Options::Url(telegramMainUrl_ + "/sendPhoto"));
		request.setOpt(new curlpp::Options::Verbose(false));
		request.setOpt(new curlpp::options::WriteStream(&responseStream));

		// Perform request
		request.perform();

		BOOST_LOG_TRIVIAL(debug) << responseStream.str();

		using namespace rapidjson;
		IStreamWrapper isw(responseStream);
		Document doc;
		doc.ParseStream(isw);

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

void BotApi::sendMessage(const std::string& chat, const std::string& text)
{
	return impl_->sendMessage(chat, text);
}

void BotApi::sendPhoto(const std::string& chat, const std::string& filename, const std::string& caption)
{
	return impl_->sendPhoto(chat, filename, caption);
}
