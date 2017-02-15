#include <telebotxx/User.hpp>
#include <sstream>

namespace telebotxx {

User::User()
	: id_(-1)
{
}

User::User(const User&) = default;

User::User(User&&) = default;

User::~User() = default;

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

void User::setFirstName(const std::string& firstName)
{
	firstName_ = firstName;
}

const std::string& User::getLastName() const
{
	return lastName_;
}

void User::setLastName(const std::string& lastName)
{
	lastName_ = lastName;
}

const std::string& User::getUsername() const
{
	return username_;
}

void User::setUsername(const std::string& username)
{
	username_ = username;
}

const std::string User::toString() const
{
	std::stringstream ss;
	ss << firstName_ << " " << lastName_ << " (@" << username_ << ")";
	return ss.str();
}

void User::swap(User& other) noexcept
{
	std::swap(id_, other.id_);
	firstName_.swap(other.firstName_);
	lastName_.swap(other.lastName_);
	username_.swap(other.username_);
}

const User& User::operator=(User other)
{
	swap(other);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << user.toString();
	return os;
}

}
