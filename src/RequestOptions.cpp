#include <telebotxx/RequestOptions.hpp>

#define TELEBOTXX_DEFINE_BOOL_PARAM_CLASS(Name) Name::Name(bool value) : value_(value) { } \
bool Name::getValue() const { return value_; }

#define TELEBOTXX_DEFINE_STRING_PARAM_CLASS(Name) Name::Name(const std::string& value) : value_(value) { } \
const std::string& Name::getValue() const { return value_; }

namespace telebotxx {

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

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(Text)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_STRING_PARAM_CLASS(Caption)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_BOOL_PARAM_CLASS(DisableWebPagePreview)

////////////////////////////////////////////////////////////////

TELEBOTXX_DEFINE_BOOL_PARAM_CLASS(DisableNotification)

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

Photo::Photo(int id)
	: type_(Type::Id), id_(id)
{
}

Photo::Photo(const Buffer& buffer)
	: type_(Type::Buffer), buffer_(buffer)
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
	else if (type_ == Type::Buffer)
		new(&buffer_) Buffer(other.buffer_);
	else if (type_ == Type::File)
		new(&file_) File(other.file_);
	else
		new(&url_) Url(other.url_);
}

Photo::Photo(Photo&& other)
{
	if (type_ == Type::Id)
	{
		id_ = other.id_;
		other.id_ = 0;
	}
	else if (type_ == Type::Buffer)
	{
		new(&buffer_) Buffer(std::move(other.buffer_));
		other.buffer_.~Buffer();
	}
	else if (type_ == Type::File)
	{
		new(&file_) File(std::move(other.file_));
		other.file_.~File();
	}
	else
	{
		new(&url_) Url(std::move(other.url_));
		other.url_.~Url();
	}
}

Photo::~Photo()
{
	if (type_ == Type::File)
		file_.~File();
	else if (type_ == Type::Url)
		url_.~Url();
}

Photo::Type Photo::getType() const
{
	return type_;
}

int Photo::getId() const
{
	return id_;
}

const Buffer& Photo::getBuffer() const
{
	return buffer_;
}

const File& Photo::getFile() const
{
	return file_;
}

const Url& Photo::getUrl() const
{
	return url_;
}

}
