#include <telebotxx/User.hpp>
#include <sstream>

namespace telebotxx {

User::User()
	: id_(-1)
{
}

int User::getId() const
{
	return id_;
}

void User::setId(int id)
{
	id_ = id;
}

const std::string& User::getFirstName() const
{
	return firstName_;
}

void User::setFirstName(std::string firstName)
{
	firstName_ = std::move(firstName);
}

const optional<std::string>& User::getLastName() const
{
	return lastName_;
}

void User::setLastName(optional<std::string> lastName)
{
	lastName_ = std::move(lastName);
}

const optional<std::string>& User::getUsername() const
{
	return username_;
}

void User::setUsername(optional<std::string> username)
{
	username_ = std::move(username);
}

const std::string User::toString() const
{
	std::stringstream ss;
	ss << firstName_;
	if (lastName_)
		ss << " " << *lastName_;
	if (username_)
		ss << " (@" << *username_ << ")";
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << user.toString();
	return os;
}

}
