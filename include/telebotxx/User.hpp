#ifndef TELEBOTXX_USER_H
#define TELEBOTXX_USER_H

#include <string>

namespace telebotxx
{
	class User
	{
	public:
		User();

		/// \brief Full constructor
		/// \param id id
		/// \param firstName first name
		/// \param lastName last name
		/// \param username username
		User(int id, const std::string& firstName, const std::string& lastName, const std::string& username);

		User(const User&);
		User(User&&);

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

		void swap(User&) noexcept;

		const User& operator=(User other);
		User& operator=(User&& other);

	private:
		int id_;
		std::string firstName_;
		std::string lastName_;
		std::string username_;
	};
}

#endif // TELEBOTXX_USER_H
