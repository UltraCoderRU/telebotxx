#include "TestGlobal.hpp"

#include <telebotxx/BotApi.hpp>

#include <memory>
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

std::unique_ptr<telebotxx::BotApi> bot;

const std::string CONFIG_FILE_NAME = "config.json";

std::string token;
std::string chat;
std::string photoFile;

struct TestConfig
{
	TestConfig()
	{
		std::cout << "Performing tests initialization..." << std::endl;

		using namespace rapidjson;
		FILE *pFile = fopen(CONFIG_FILE_NAME.c_str(), "rb");
		if (pFile == NULL)
			throw std::runtime_error("Can not open config file");

		char buffer[2048];
		FileReadStream is(pFile, buffer, sizeof(buffer));
		Document document;
		document.ParseStream<0, UTF8<>, FileReadStream>(is);

		if (!document.IsObject() && document.HasParseError())
			throw std::invalid_argument("Can not parse config file");

		// Read token
		if (document.HasMember("token"))
			if (document["token"].IsString())
				token = document["token"].GetString();
			else
				throw std::invalid_argument("Config error: 'token' must be unsigned int value.");
		else
			throw std::invalid_argument("Config error: 'token' not set.");

		// Read chat
		if (document.HasMember("chat"))
			if (document["chat"].IsString())
				chat = document["chat"].GetString();
			else
				throw std::invalid_argument("Config error: 'chat' must be unsigned int value.");
		else
			throw std::invalid_argument("Config error: 'chat' not set.");

		// Read photo filename
		if (document.HasMember("photo"))
			if (document["photo"].IsString())
				photoFile = document["photo"].GetString();
			else
				throw std::invalid_argument("Config error: 'photo' must be unsigned int value.");
		else
			throw std::invalid_argument("Config error: 'photo' not set.");
	}

	~TestConfig()
	{
		std::cout << "Performing tests cleanup..." << std::endl;
	}
};

BOOST_GLOBAL_FIXTURE(TestConfig);

BOOST_AUTO_TEST_SUITE(TestBotApi)

	BOOST_AUTO_TEST_CASE(DefaultConstructor)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE_NO_THROW(bot.reset(new telebotxx::BotApi(token)));
	}

	BOOST_AUTO_TEST_CASE(SendMessage)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendMessage(chat, "Hello from C++!"));
	}

BOOST_AUTO_TEST_SUITE_END()
