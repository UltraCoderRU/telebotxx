#ifndef TELEBOTXX_CHAT_HPP
#define TELEBOTXX_CHAT_HPP

#include "Optional.hpp"

#include <string>
#include <memory>
#include <cstdint>

namespace telebotxx {

class Chat
{
public:
	enum class Type
	{
		Private,
		Group,
		Supergroup,
		Channel
	};

	Chat();

	std::int64_t getId() const;
	void setId(std::int64_t id);

	Type getType() const;
	void setType(Type type);

	const optional<std::string>& getTitle() const;
	void setTitle(optional<std::string> title);

	const optional<std::string>& getUsername() const;
	void setUsername(optional<std::string> username);

	const optional<std::string>& getFirstName() const;
	void setFirstName(optional<std::string> firstName);

	const optional<std::string>& getLastName() const;
	void setLastName(optional<std::string> lastName);

	bool isAllAdmins() const;
	void setAllAdmins(bool allAdmins);

private:
	std::int64_t id_;
	Type type_;
	optional<std::string> title_;
	optional<std::string> username_;
	optional<std::string> firstName_;
	optional<std::string> lastName_;
	bool allAdmins_;
};

Chat::Type chatTypeFromString(const std::string& str);

}

#endif // TELEBOTXX_CHAT_HPP
