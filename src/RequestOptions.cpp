#include <telebotxx/RequestOptions.hpp>

using namespace telebotxx;

ChatId::ChatId(int id)
	: type_(Type::Id), id_(id)
{
}

ChatId::ChatId(const std::string& str)
	: type_(Type::Username), username_(str)
{
}

ChatId::ChatId(const ChatId& other)
	: type_(other.type_)
{
	if (type_ == Type::Id)
		id_ = other.id_;
	else
		new(&username_) std::string(other.username_);
}

ChatId::ChatId(ChatId&& other)
	: type_(std::move(other.type_))
{
	if (type_ == Type::Id)
	{
		id_ = other.id_;
		other.id_ = 0;
	}
	else
	{
		new(&username_) std::string(std::move(other.username_));
		other.username_.~basic_string();
	}
}

ChatId::~ChatId()
{
	if (type_ == Type::Username)
		username_.~basic_string();
}

ChatId::Type ChatId::getType() const
{
	return type_;
}

const int ChatId::getId() const
{
	return id_;
}

const std::string ChatId::getUsername() const
{
	return username_;
}

////////////////////////////////////////////////////////////////

DisableWebPagePreview::DisableWebPagePreview(bool disabled)
	: disable_(disabled)
{
}

bool DisableWebPagePreview::value() const
{
	return disable_;
}

////////////////////////////////////////////////////////////////

DisableNotification::DisableNotification(bool disabled)
	: disable_(disabled)
{
}

bool DisableNotification::value() const
{
	return disable_;
}

////////////////////////////////////////////////////////////////

ReplyTo::ReplyTo(int id)
	: id_(id)
{
}

int ReplyTo::value() const
{
	return id_;
}

////////////////////////////////////////////////////////////////

File::File(const std::string& filename)
	: filename_(filename)
{
}

const std::string& File::getFilename() const
{
	return filename_;
}

////////////////////////////////////////////////////////////////

const std::string& Url::getUrl() const
{
	return url_;
}

Url::Url(const std::string& url)
		: url_(url)
{
}

////////////////////////////////////////////////////////////////

Photo::Photo(int id)
	: type_(Type::Id), id_(id)
{
}

Photo::Photo(const File& file)
	: type_(Type::File), file_(file)
{
}

Photo::Photo(const Url& url)
	: type_(Type::Url), url_(url)
{
}

Photo::Photo(const Photo& other)
	: type_(other.type_)
{
	if (type_ == Type::Id)
		id_ = other.id_;
	else if (type_ == Type::File)
		new(&file_) File(other.file_);
	else
		new(&url_) Url(other.url_);
}

Photo::~Photo()
{
	if (type_ == Type::File)
		file_.~File();
	else if(type_ == Type::Url)
		url_.~Url();
}

Photo::Type Photo::getType() const
{
	return type_;
}