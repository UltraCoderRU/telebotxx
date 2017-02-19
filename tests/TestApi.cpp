#include "TestGlobal.hpp"

#include <telebotxx/BotApi.hpp>
#include <telebotxx/Logging.hpp>

#include <memory>
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

std::unique_ptr<telebotxx::BotApi> bot;

const std::string CONFIG_FILE_NAME = "config.json";

using namespace telebotxx;

std::string token;
std::string chat;
std::string photoFile;
std::string photoUrl;

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
		rapidjson::Document document;
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

		// Read photo URL
		if (document.HasMember("photoURL"))
			if (document["photoURL"].IsString())
				photoUrl = document["photoURL"].GetString();
			else
				throw std::invalid_argument("Config error: 'photoURL' must be unsigned int value.");
		else
			throw std::invalid_argument("Config error: 'photoURL' not set.");

		telebotxx::setDebugMode(true);
	}

	~TestConfig()
	{
		std::cout << "Performing tests cleanup..." << std::endl;
	}
};

BOOST_GLOBAL_FIXTURE(TestConfig);

BOOST_AUTO_TEST_SUITE(TestSend)

	BOOST_AUTO_TEST_CASE(DefaultConstructor)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE_NO_THROW(bot.reset(new BotApi(token)));
	}

	BOOST_AUTO_TEST_CASE(SendMessage)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendMessage(ChatId{chat},
										        Text{"Sample text"}
		));
	}

	BOOST_AUTO_TEST_CASE(SendMessageWithMarkdown)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendMessage(ChatId{chat},
										        Text{"[Sample text in markdown](http://google.com/)"},
										        ParseMode::Markdown
		));
	}

	BOOST_AUTO_TEST_CASE(SendMessageWithHtml)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendMessage(ChatId{chat},
										        Text{"<a href=\"http://google.com/\">Sample text in HTML</a>"},
										        ParseMode::Html
		));
	}

	BOOST_AUTO_TEST_CASE(SendMessageWithoutPreview)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendMessage(ChatId{chat},
										        Text{"http://google.com/"},
										        DisableWebPagePreview()
		));
	}

	BOOST_AUTO_TEST_CASE(SendMessageWithoutNotification)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendMessage(ChatId{chat},
										        Text{"Message without notification"},
										        DisableNotification()
		));
	}

	BOOST_AUTO_TEST_CASE(SendPhotoFile)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendPhoto(chat,
											  Photo{File{photoFile}}
		));
	}

	BOOST_AUTO_TEST_CASE(SendPhotoFileWithCaption)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendPhoto(chat,
											  Photo{File{photoFile}},
											  Caption{"Photo with caption"}
		));
	}

	BOOST_AUTO_TEST_CASE(SendPhotoInMemory)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		std::ifstream file(photoFile, std::ios::binary | std::ios::ate);
		std::size_t size = static_cast<std::size_t>(file.tellg());
		file.seekg(0, std::ios::beg);
		std::vector<char> buffer(size);
		BOOST_REQUIRE(file.read(buffer.data(), size));
		BOOST_REQUIRE_NO_THROW(bot->sendPhoto(chat,
											  Photo{Buffer{buffer.data(), size, photoFile}},
											  Caption{"Photo sent in-memory"}
		));
	}

	BOOST_AUTO_TEST_CASE(SendPhotoUrl)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendPhoto(chat,
											  Photo{Url{photoUrl}},
											  Caption{"Photo sent by URL"}
		));
	}

	BOOST_AUTO_TEST_CASE(SendPhotoWithoutNotification)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		BOOST_REQUIRE_NO_THROW(bot->sendPhoto(chat,
											  Photo{File{photoFile}},
											  Caption{"Photo without notification"},
											  DisableNotification()
		));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestParse)

	BOOST_AUTO_TEST_CASE(GetUpdates)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE(bot);
		Updates updates;
		BOOST_REQUIRE_NO_THROW(updates = bot->getUpdates());
		for (auto update : updates)
		{
			switch (update.getType())
			{
				case Update::Type::Message:
				case Update::Type::EditedMessage:
				case Update::Type::ChannelPost:
				case Update::Type::EditedChannelPost:
				{
					auto message = update.getMessage();
					if (message->getFrom())
						std::cout << *message->getFrom() << ": ";
					if (message->getText())
						std::cout << *message->getText() << std::endl;
					break;
				}
			}
		}
	}

BOOST_AUTO_TEST_SUITE_END()
