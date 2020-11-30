#ifndef TELEBOTXX_CHAT_HPP
#define TELEBOTXX_CHAT_HPP

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

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

	const std::optional<std::string>& getTitle() const;
	void setTitle(std::optional<std::string> title);

	const std::optional<std::string>& getUsername() const;
	void setUsername(std::optional<std::string> username);

	const std::optional<std::string>& getFirstName() const;
	void setFirstName(std::optional<std::string> firstName);

	const std::optional<std::string>& getLastName() const;
	void setLastName(std::optional<std::string> lastName);

	bool isAllAdmins() const;
	void setAllAdmins(bool allAdmins);

private:
	std::int64_t id_;
	Type type_;
	std::optional<std::string> title_;
	std::optional<std::string> username_;
	std::optional<std::string> firstName_;
	std::optional<std::string> lastName_;
	bool allAdmins_;
};

Chat::Type chatTypeFromString(const std::string& str);

} // namespace telebotxx

#endif // TELEBOTXX_CHAT_HPP
