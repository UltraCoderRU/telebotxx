#include "RequestOptions.hpp"

#define TELEBOTXX_DEFINE_BOOL_PARAM_CLASS(Name) \
	Name::Name(bool value) : value_(value) {} \
	bool Name::getValue() const { return value_; }

#define TELEBOTXX_DEFINE_STRING_PARAM_CLASS(Name) \
	Name::Name(const std::string& value) : value_(value) {} \
	const std::string& Name::getValue() const { return value_; }

namespace telebotxx {

ChatId::ChatId(int id) : type_(Type::Id), value_(id)
{
}

ChatId::ChatId(const std::string& str) : type_(Type::Username), value_(str)
{
}

ChatId::Type ChatId::getType() const
{
	return type_;
}

const int ChatId::getId() const
{
	return std::get<int>(value_);
}

const std::string ChatId::getUsername() const
{
	return std::get<std::string>(value_);
}

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(Text)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(Caption)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_BOOL_PARAM_CLASS(DisableWebPagePreview)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_BOOL_PARAM_CLASS(DisableNotification)

////////////////////////////////////////////////////////////////

ReplyTo::ReplyTo(int id) : id_(id)
{
}

int ReplyTo::value() const
{
	return id_;
}

////////////////////////////////////////////////////////////////

Buffer::Buffer(const char* buffer, std::size_t size, const std::string& filename)
    : data_(buffer), size_(size), filename_(filename)
{
}

Buffer::Buffer(const std::vector<char>& data, const std::string& filename)
    : data_(data.data()), size_(data.size()), filename_(filename)
{
}

const char* Buffer::data() const
{
	return data_;
}

const std::size_t Buffer::size() const
{
	return size_;
}

const std::string Buffer::filename() const
{
	return filename_;
}

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(File)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(Url)

////////////////////////////////////////////////////////////////

Photo::Photo(int id) : type_(Type::Id), value_(id)
{
}

Photo::Photo(const Buffer& buffer) : type_(Type::Buffer), value_(buffer)
{
}

Photo::Photo(const File& file) : type_(Type::File), value_(file)
{
}

Photo::Photo(const Url& url) : type_(Type::Url), value_(url)
{
}

Photo::Type Photo::getType() const
{
	return type_;
}

int Photo::getId() const
{
	return std::get<int>(value_);
}

const Buffer& Photo::getBuffer() const
{
	return std::get<Buffer>(value_);
}

const File& Photo::getFile() const
{
	return std::get<File>(value_);
}

const Url& Photo::getUrl() const
{
	return std::get<Url>(value_);
}

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(CallbackData)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(SwitchInlineQuery)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(SwitchInlineQueryCurrentChat)

////////////////////////////////////////////////////////////////

InlineKeyboardButton::InlineKeyboardButton(const std::string& text, const Url& url)
    : actionType_(ActionType::Url), text_(text), value_(url)
{
}

InlineKeyboardButton::InlineKeyboardButton(const std::string& text, const CallbackData& callbackData)
    : actionType_(ActionType::CallbackData), text_(text), value_(callbackData)
{
}

InlineKeyboardButton::InlineKeyboardButton(const std::string& text,
                                           const SwitchInlineQuery& switchInlineQuery)
    : actionType_(ActionType::SwitchInlineQuery), text_(text), value_(switchInlineQuery)
{
}

InlineKeyboardButton::InlineKeyboardButton(const std::string& text,
                                           const SwitchInlineQueryCurrentChat& switchInlineQueryCurrentChat)
    : actionType_(ActionType::SwitchInlineQueryCurrentChat),
      text_(text),
      value_(switchInlineQueryCurrentChat)
{
}

InlineKeyboardButton::InlineKeyboardButton(const InlineKeyboardButton& other) = default;

InlineKeyboardButton::InlineKeyboardButton(InlineKeyboardButton&& other) = default;

InlineKeyboardButton::~InlineKeyboardButton() = default;

InlineKeyboardButton::ActionType InlineKeyboardButton::getActionType() const
{
	return actionType_;
}

const std::string& InlineKeyboardButton::getText() const
{
	return text_;
}

const Url& InlineKeyboardButton::getUrl() const
{
	return std::get<Url>(value_);
}

const CallbackData& InlineKeyboardButton::getCallbackData() const
{
	return std::get<CallbackData>(value_);
}

const SwitchInlineQuery& InlineKeyboardButton::getSwitchInlineQuery() const
{
	return std::get<SwitchInlineQuery>(value_);
}

const SwitchInlineQueryCurrentChat& InlineKeyboardButton::getSwitchInlineQueryCurrentChat() const
{
	return std::get<SwitchInlineQueryCurrentChat>(value_);
}

void InlineKeyboardButton::swap(InlineKeyboardButton& other)
{
	using std::swap;
	swap(text_, other.text_);
	swap(actionType_, other.actionType_);
	swap(value_, other.value_);
}

const InlineKeyboardButton& InlineKeyboardButton::operator=(InlineKeyboardButton other)
{
	swap(other);
	return *this;
}

////////////////////////////////////////////////////////////////

void InlineKeyboardMarkup::addRow(const InlineKeyboardButtonRow& row)
{
	rows_.push_back(row);
}

const std::vector<InlineKeyboardButtonRow>& InlineKeyboardMarkup::getRows() const
{
	return rows_;
}

////////////////////////////////////////////////////////////////

ReplyMarkup::ReplyMarkup(const InlineKeyboardMarkup& keyboard)
    : type_(Type::InlineKeyboardMarkup), value_(keyboard)
{
}

ReplyMarkup::ReplyMarkup(const ReplyKeyboardMarkup& keyboard)
    : type_(Type::ReplyKeyboardMarkup), value_(keyboard)
{
}

ReplyMarkup::ReplyMarkup(const ReplyMarkup&) = default;
ReplyMarkup::ReplyMarkup(ReplyMarkup&&) = default;
ReplyMarkup::~ReplyMarkup() = default;

ReplyMarkup::Type ReplyMarkup::getType() const
{
	return type_;
}

const InlineKeyboardMarkup& ReplyMarkup::getInlineKeyboardMarkup() const
{
	return std::get<InlineKeyboardMarkup>(value_);
}

void ReplyMarkup::swap(ReplyMarkup& other)
{
	using std::swap;
	swap(type_, other.type_);
	swap(value_, other.value_);
}

const ReplyMarkup& ReplyMarkup::operator=(ReplyMarkup other)
{
	swap(other);
	return *this;
}

} // namespace telebotxx
