#ifndef TELEBOTXX_REQUEST_OPTIONS_HPP
#define TELEBOTXX_REQUEST_OPTIONS_HPP

#include <string>
#include <vector>

#include <boost/variant/variant.hpp>

#define TELEBOTXX_DECLARE_BOOL_PARAM_CLASS(Name, DEFAULT) class Name \
{ \
public: \
	explicit Name(bool value = DEFAULT); \
	bool getValue() const; \
private: \
	bool value_; \
};

#define TELEBOTXX_DECLARE_STRING_PARAM_CLASS(Name) class Name \
{ \
public: \
	explicit Name(const std::string& value); \
	const std::string& getValue() const; \
private: \
	std::string value_; \
};

namespace telebotxx {

class ChatId
{
public:
	ChatId(int);
	ChatId(const std::string&);
	ChatId(const ChatId&);
	ChatId(ChatId&&);
	~ChatId();

	enum class Type { Id, Username };
	Type getType() const;
	const int getId() const;
	const std::string getUsername() const;
private:
	Type type_;
	boost::variant<int, std::string> value_;
};

TELEBOTXX_DECLARE_STRING_PARAM_CLASS(Text);
TELEBOTXX_DECLARE_STRING_PARAM_CLASS(Caption);

enum class ParseMode
{
	Plain,
	Markdown,
	Html
};

TELEBOTXX_DECLARE_BOOL_PARAM_CLASS(DisableWebPagePreview, true)

TELEBOTXX_DECLARE_BOOL_PARAM_CLASS(DisableNotification, true)

class ReplyTo
{
public:
	explicit ReplyTo(int id);
	int value() const;
private:
	int id_;
};

class Buffer
{
public:
	Buffer(const char *buffer, std::size_t size, const std::string& filename);
	explicit Buffer(const std::vector<char>& data, const std::string& filename);
	const char *data() const;
	const std::size_t size() const;
	const std::string filename() const;
private:
	const char *data_;
	std::size_t size_;
	std::string filename_;
};

TELEBOTXX_DECLARE_STRING_PARAM_CLASS(File)

TELEBOTXX_DECLARE_STRING_PARAM_CLASS(Url)

class Photo
{
public:
	explicit Photo(int id);
	explicit Photo(const Buffer&);
	explicit Photo(const File&);
	explicit Photo(const Url&);
	Photo(const Photo&);
	Photo(Photo&&);
	~Photo();

	enum class Type	{ Id, Buffer, File, Url };
	Type getType() const;

	int getId() const;
	const Buffer& getBuffer() const;
	const File& getFile() const;
	const Url& getUrl() const;

private:
	Type type_;
	boost::variant<int, Buffer, File, Url> value_;
};

TELEBOTXX_DECLARE_STRING_PARAM_CLASS(CallbackData)

TELEBOTXX_DECLARE_STRING_PARAM_CLASS(SwitchInlineQuery)

TELEBOTXX_DECLARE_STRING_PARAM_CLASS(SwitchInlineQueryCurrentChat)

class InlineKeyboardButton
{
public:
	explicit InlineKeyboardButton(const std::string& text, const Url& url);
	explicit InlineKeyboardButton(const std::string& text, const CallbackData&);
	explicit InlineKeyboardButton(const std::string& text, const SwitchInlineQuery&);
	explicit InlineKeyboardButton(const std::string& text, const SwitchInlineQueryCurrentChat&);
	InlineKeyboardButton(const InlineKeyboardButton&);
	InlineKeyboardButton(InlineKeyboardButton&&);
	~InlineKeyboardButton();

	enum class ActionType { Url, CallbackData, SwitchInlineQuery, SwitchInlineQueryCurrentChat };
	ActionType getActionType() const;

	const std::string& getText() const;
	const Url& getUrl() const;
	const CallbackData& getCallbackData() const;
	const SwitchInlineQuery& getSwitchInlineQuery() const;
	const SwitchInlineQueryCurrentChat& getSwitchInlineQueryCurrentChat() const;

private:
	ActionType actionType_;
	std::string text_;
	boost::variant<Url, CallbackData, SwitchInlineQuery, SwitchInlineQueryCurrentChat> value_;
	// \todo CallbackGame
};

using InlineKeyboardButtonRow = std::vector<InlineKeyboardButton>;

class InlineKeyboardMarkup
{
public:
	void addRow(const InlineKeyboardButtonRow& row);

	const std::vector<InlineKeyboardButtonRow>& getRows() const;

private:
	std::vector<InlineKeyboardButtonRow> rows_;
};

class ReplyKeyboardMarkup
{

};

class ReplyMarkup
{
public:
	explicit ReplyMarkup(const InlineKeyboardMarkup&);
	explicit ReplyMarkup(const ReplyKeyboardMarkup&);
	ReplyMarkup(const ReplyMarkup&);
	ReplyMarkup(ReplyMarkup&&);
	~ReplyMarkup();

	enum class Type { InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply };
	Type getType() const;

	const InlineKeyboardMarkup& getInlineKeyboardMarkup() const;

	void swap(ReplyMarkup&);
	const ReplyMarkup& operator=(ReplyMarkup);

private:
	Type type_;
	boost::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup> value_;
};

}

#endif // TELEBOTXX_REQUEST_OPTIONS_HPP
