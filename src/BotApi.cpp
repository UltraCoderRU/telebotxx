#include <telebotxx/BotApi.hpp>

#include <sstream>

#include <rapidjson/writer.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace telebotxx;

BotApi::BotApi(const std::string& token)
	: token_(token)
{
	telegramMainUrl_ = "https://api.telegram.org/bot" + token_;

	/// \todo run getMe command to check token
}

void BotApi::sendMessage(const std::string &chat, const std::string &text)
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

	std::istringstream myStream(s.GetString());
	std::cout << myStream.str() << std::endl;
	auto size = myStream.str().size();

	// Construct HTTP request
	curlpp::Easy request;
	std::list<std::string> headers;

	// Content-Type
	headers.push_back("Content-Type: application/json");

	// Content-Length
	std::ostringstream ss;
	ss << "Content-Length: " << size;
	headers.push_back(ss.str());

	// Set options
	request.setOpt(new curlpp::Options::Url(telegramMainUrl_ + "/sendMessage"));
	request.setOpt(new curlpp::Options::Verbose(true));
	request.setOpt(new curlpp::Options::ReadStream(&myStream));
	request.setOpt(new curlpp::Options::InfileSize(size));
	request.setOpt(new curlpp::options::HttpHeader(headers));
	request.setOpt(new curlpp::Options::Post(true));

	// Perform request
	request.perform();
}

void BotApi::sendPhoto(const std::string& chat, const std::istream& file, const std::string& caption)
{
	// Construct HTTP request
	curlpp::Easy request;
	std::list<std::string> headers;

	{
		// Forms takes ownership of pointers!
		curlpp::Forms formParts;
		formParts.push_back(new curlpp::FormParts::Content("chat_id", chat));
		formParts.push_back(new curlpp::FormParts::Content("photo", "value2"));

		request.setOpt(new curlpp::options::HttpPost(formParts));
	}

	// Set options
	request.setOpt(new curlpp::Options::Url(telegramMainUrl_ + "/sendPhoto"));
	request.setOpt(new curlpp::Options::Verbose(true));
	request.setOpt(new curlpp::options::HttpHeader(headers));
	request.setOpt(new curlpp::Options::Post(true));

	// Perform request
	request.perform();
}


