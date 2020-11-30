#include <telebotxx/BotApi.hpp>
#include <telebotxx/Logging.hpp>

#include <catch2/catch_all.hpp>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <fstream>
#include <iostream>
#include <memory>

const char* CONFIG_FILE_NAME = "config.json";

struct Config
{
	std::string token;
	std::string chat;
	std::string photoFile;
	std::string photoUrl;
};
std::unique_ptr<Config> config;

std::unique_ptr<Config> readConfig()
{
	using namespace rapidjson;

	std::ifstream file(CONFIG_FILE_NAME);
	if (file.fail())
		throw std::runtime_error("Can not open config file");

	IStreamWrapper is(file);
	rapidjson::Document document;
	document.ParseStream(is);

	Config config;

	if (!document.IsObject() && document.HasParseError())
		throw std::invalid_argument("Can not parse config file");

	// Read token
	if (document.HasMember("token"))
		if (document["token"].IsString())
			config.token = document["token"].GetString();
		else
			throw std::invalid_argument("Config error: 'token' must be unsigned int value.");
	else
		throw std::invalid_argument("Config error: 'token' not set.");

	// Read chat
	if (document.HasMember("chat"))
		if (document["chat"].IsString())
			config.chat = document["chat"].GetString();
		else
			throw std::invalid_argument("Config error: 'chat' must be unsigned int value.");
	else
		throw std::invalid_argument("Config error: 'chat' not set.");

	// Read photo filename
	if (document.HasMember("photo"))
		if (document["photo"].IsString())
			config.photoFile = document["photo"].GetString();
		else
			throw std::invalid_argument("Config error: 'photo' must be unsigned int value.");
	else
		throw std::invalid_argument("Config error: 'photo' not set.");

	// Read photo URL
	if (document.HasMember("photoURL"))
		if (document["photoURL"].IsString())
			config.photoUrl = document["photoURL"].GetString();
		else
			throw std::invalid_argument("Config error: 'photoURL' must be unsigned int value.");
	else
		throw std::invalid_argument("Config error: 'photoURL' not set.");

	telebotxx::setDebugMode(true);

	return std::make_unique<Config>(std::move(config));
}

using namespace telebotxx;

std::unique_ptr<BotApi> bot;

TEST_CASE("Read tests configuration")
{
	REQUIRE_NOTHROW(config = readConfig());
	REQUIRE(config);
}

TEST_CASE("Default constructor", "[API]")
{
	REQUIRE(config);
	REQUIRE_NOTHROW(bot.reset(new BotApi(config->token)));
}

TEST_CASE("Send text message", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendMessage(ChatId{config->chat}, Text{"Sample text"}));
}

TEST_CASE("Send message with markdown", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendMessage(ChatId{config->chat},
	                                 Text{"[Sample text in markdown](http://google.com/)"},
	                                 ParseMode::Markdown));
}

TEST_CASE("Send message with HTML", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendMessage(ChatId{config->chat},
	                                 Text{"<a href=\"http://google.com/\">Sample text in HTML</a>"},
	                                 ParseMode::Html));
}

TEST_CASE("Send message without preview", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendMessage(ChatId{config->chat}, Text{"http://google.com/"},
	                                 DisableWebPagePreview()));
}

TEST_CASE("Send message without notification", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendMessage(ChatId{config->chat}, Text{"Message without notification"},
	                                 DisableNotification()));
}

TEST_CASE("Send photo from file", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendPhoto(config->chat, Photo{File{config->photoFile}}));
}

TEST_CASE("Send photo from file with caption", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendPhoto(config->chat, Photo{File{config->photoFile}},
	                               Caption{"Photo with caption"}));
}

TEST_CASE("Send photo from memory", "[API]")
{
	REQUIRE(bot);
	std::ifstream file(config->photoFile, std::ios::binary | std::ios::ate);
	std::size_t size = static_cast<std::size_t>(file.tellg());
	file.seekg(0, std::ios::beg);
	std::vector<char> buffer(size);
	REQUIRE(file.read(buffer.data(), size));
	REQUIRE_NOTHROW(bot->sendPhoto(config->chat, Photo{Buffer{buffer.data(), size, config->photoFile}},
	                               Caption{"Photo sent in-memory"}));
}

TEST_CASE("Send photo by URL", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(
	    bot->sendPhoto(config->chat, Photo{Url{config->photoUrl}}, Caption{"Photo sent by URL"}));
}

TEST_CASE("Send photo without notification", "[API]")
{
	REQUIRE(bot);
	REQUIRE_NOTHROW(bot->sendPhoto(config->chat, Photo{File{config->photoFile}},
	                               Caption{"Photo without notification"}, DisableNotification()));
}

TEST_CASE("Get updates", "[API]")
{
	REQUIRE(bot);

	Updates updates;
	REQUIRE_NOTHROW(updates = bot->getUpdates());
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
