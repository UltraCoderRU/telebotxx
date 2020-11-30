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

} // namespace telebotxx
