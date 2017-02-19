#ifndef TELEBOTXX_USER_H
#define TELEBOTXX_USER_H

#include "Optional.hpp"
#include <string>
#include <memory>

namespace telebotxx {

class User
{
public:
	User();

	/// \brief Get id
	int getId() const;

	/// \brief Set id
	void setId(int id);

	/// \brief Get first name
	const std::string& getFirstName() const;

	/// \brief Set first name
	void setFirstName(std::string firstName);

	/// \brief Get last name
	const optional<std::string>& getLastName() const;

	/// \brief Set last name
	void setLastName(optional<std::string> lastName);

	/// \brief Get username
	const optional<std::string>& getUsername() const;

	/// \brief Set username
	void setUsername(optional<std::string> username);

	/// \brief Get string representation of user
	const std::string toString() const;

private:
	int id_;
	std::string firstName_;
	optional<std::string> lastName_;
	optional<std::string> username_;
};

std::ostream& operator<<(std::ostream& os, const User& user);

}

#endif // TELEBOTXX_USER_H
