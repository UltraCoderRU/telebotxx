#ifndef TELEBOTXX_CHAT_HPP
#define TELEBOTXX_CHAT_HPP

#include <string>
#include <memory>
#include <cstdint>

namespace telebotxx
{
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
		Chat(const Chat&);
		Chat(Chat&&);
		~Chat();

		std::int64_t getId() const;
		void setId(std::int64_t id);

		Type getType() const;
		void setType(Type type);

		const std::string& getTitle() const;
		void setTitle(const std::string& title);

		const std::string& getUsername() const;
		void setUsername(const std::string& username);

		const std::string& getFirstName() const;
		void setFirstName(const std::string& firstName);

		const std::string& getLastName() const;
		void setLastName(const std::string& lastName);

		bool isAllAdmins() const;
		void setAllAdmins(bool allAdmins);

		void swap(Chat& other) noexcept;

		const Chat& operator=(Chat other) noexcept;

	private:
		std::int64_t id_;
		Type type_;
		std::string title_;
		std::string username_;
		std::string firstName_;
		std::string lastName_;
		bool allAdmins_;
	};

	using ChatPtr = std::shared_ptr<Chat>;

	void swap(Chat& lhs, Chat& rhs);

	Chat::Type chatTypeFromString(const std::string& str);
}

#endif // TELEBOTXX_CHAT_HPP
