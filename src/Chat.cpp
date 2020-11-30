#include "Chat.hpp"

#include <stdexcept>

namespace telebotxx {

Chat::Chat() : id_(-1), type_(Type::Private), allAdmins_(false)
{
}

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

const std::optional<std::string>& Chat::getTitle() const
{
	return title_;
}

void Chat::setTitle(std::optional<std::string> title)
{
	title_ = title;
}

const std::optional<std::string>& Chat::getUsername() const
{
	return username_;
}

void Chat::setUsername(std::optional<std::string> username)
{
	username_ = username;
}

const std::optional<std::string>& Chat::getFirstName() const
{
	return firstName_;
}

void Chat::setFirstName(std::optional<std::string> firstName)
{
	firstName_ = firstName;
}

const std::optional<std::string>& Chat::getLastName() const
{
	return lastName_;
}

void Chat::setLastName(std::optional<std::string> lastName)
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

} // namespace telebotxx
