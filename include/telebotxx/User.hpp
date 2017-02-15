#ifndef TELEBOTXX_USER_H
#define TELEBOTXX_USER_H

#include <string>
#include <memory>

namespace telebotxx {

class User
{
public:
	User();
	User(const User&);
	User(User&&);
	~User();

	/// \brief Get id
	int getId() const;

	/// \brief Set id
	void setId(int id);

	/// \brief Get first name
	const std::string& getFirstName() const;

	/// \brief Set first name
	void setFirstName(const std::string& firstName);

	/// \brief Get last name
	const std::string& getLastName() const;

	/// \brief Set last name
	void setLastName(const std::string& lastName);

	/// \brief Get username
	const std::string& getUsername() const;

	/// \brief Set username
	void setUsername(const std::string& username);

	/// \brief Get string representation of user
	const std::string toString() const;

	void swap(User&) noexcept;

	const User& operator=(User other);

private:
	int id_;
	std::string firstName_;
	std::string lastName_;
	std::string username_;
};

using UserPtr = std::shared_ptr<User>;

std::ostream& operator<<(std::ostream& os, const User& user);

}

#endif // TELEBOTXX_USER_H
