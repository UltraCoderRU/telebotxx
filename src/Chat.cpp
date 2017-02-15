#include <telebotxx/Chat.hpp>
#include <stdexcept>

namespace telebotxx {

Chat::Chat()
	: id_(-1),
	  type_(Type::Private),
	  allAdmins_(false)
{
}

Chat::Chat(const Chat&) = default;

Chat::Chat(Chat&&) = default;

Chat::~Chat() = default;

std::int64_t Chat::getId() const
{
	return id_;
}

void Chat::setId(std::int64_t id)
{
	id_ = id;
}

Chat::Type Chat::getType() const
{
	return type_;
}

void Chat::setType(Chat::Type type)
{
	type_ = type;
}

const std::string& Chat::getTitle() const
{
	return title_;
}

void Chat::setTitle(const std::string& title)
{
	title_ = title;
}

const std::string& Chat::getUsername() const
{
	return username_;
}

void Chat::setUsername(const std::string& username)
{
	username_ = username;
}

const std::string& Chat::getFirstName() const
{
	return firstName_;
}

void Chat::setFirstName(const std::string& firstName)
{
	firstName_ = firstName;
}

const std::string& Chat::getLastName() const
{
	return lastName_;
}

void Chat::setLastName(const std::string& lastName)
{
	lastName_ = lastName;
}

bool Chat::isAllAdmins() const
{
	return allAdmins_;
}

void Chat::setAllAdmins(bool allAdmins)
{
	allAdmins_ = allAdmins;
}

void Chat::swap(Chat& other) noexcept
{
	using std::swap;
	swap(id_, other.id_);
	swap(type_, other.type_);
	swap(title_, other.title_);
	swap(username_, other.username_);
	swap(firstName_, other.firstName_);
	swap(lastName_, other.lastName_);
	swap(allAdmins_, other.allAdmins_);
}

const Chat& Chat::operator=(Chat other) noexcept
{
	swap(other);
	return *this;
}

void swap(Chat& lhs, Chat& rhs)
{
	lhs.swap(rhs);
}

Chat::Type chatTypeFromString(const std::string& str)
{
	if (str == "private")
		return Chat::Type::Private;
	else if (str == "group")
		return Chat::Type::Group;
	else if (str == "supergroup")
		return Chat::Type::Supergroup;
	else if (str == "channel")
		return Chat::Type::Channel;
	else
		throw std::invalid_argument("Unknown chat type");
}

}
