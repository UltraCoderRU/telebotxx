#ifndef TELEBOTXX_MESSAGE_HPP
#define TELEBOTXX_MESSAGE_HPP

#include "User.hpp"
#include "Chat.hpp"
#include "Attachment.hpp"

#include <vector>
#include <ctime>
#include <memory>

namespace telebotxx
{
	class MessageEntity
	{
	public:
		enum class Type
		{
			Mention,
			Hashtag,
			BotCommand,
			Url,
			Email,
			Bold,
			Italic,
			Code,
			Pre,
			TextLink,
			TextMention
		};

		MessageEntity();
		MessageEntity(const MessageEntity&);
		MessageEntity(MessageEntity&&);
		~MessageEntity();

		Type getType() const;
		void setType(Type type);

		int getOffset() const;
		void setOffset(int offset);

		size_t getLength() const;
		void setLength(size_t length);

		const std::string& getUrl() const;
		void setUrl(const std::string& url);

		const User& getUser() const;
		void setUser(const User& user);

		void swap(MessageEntity& other) noexcept;

		const MessageEntity& operator=(MessageEntity other);

	private:
		Type type_;
		int offset_;
		std::size_t length_;
		std::string url_;
		User user_;
	};

	MessageEntity::Type messageEntityTypeFromString(const std::string& str);

	using MessageEntities = std::vector<MessageEntity>;

	class Message;
	using MessagePtr = std::shared_ptr<Message>;

	class Message
	{
	public:
		Message();
		Message(const Message&);
		Message(Message&&);
		~Message();

		int getId() const;
		void setId(int id);

		const UserPtr getFrom() const;
		void setFrom(UserPtr from);

		time_t getDate() const;
		void setDate(time_t date);

		const Chat& getChat() const;
		void setChat(const Chat& chat);

		const UserPtr getForwardFrom() const;
		void setForwardFrom(UserPtr forwardFrom);

		const ChatPtr getForwardFromChat() const;
		void setForwardFromChat(ChatPtr forwardFromChat);

		time_t getForwardDate() const;
		void setForwardDate(time_t forwardDate);

		const MessagePtr getReplyToMessage() const;
		void setReplyToMessage(MessagePtr replyToMessage);

		time_t getEditDate() const;
		void setEditDate(time_t editDate);

		const std::string& getText() const;
		void setText(const std::string& text);

		const MessageEntities& getEntities() const;
		void setEntities(MessageEntities&& entities);

		const AttachmentPtr getAttachment() const;
		void setAttachment(AttachmentPtr attachment);

		const std::string& getCaption() const;
		void setCaption(const std::string& caption);

		const UserPtr getNewChatMember() const;
		void setNewChatMember(UserPtr newChatMember);

		const UserPtr getLeftChatMember() const;
		void setLeftChatMember(UserPtr leftChatMember);

		const std::string& getNewChatTitle() const;
		void setNewChatTitle(const std::string& newChatTitle);

		const PhotoSizeArrayPtr getNewChatPhoto() const;
		void setNewChatPhoto(PhotoSizeArrayPtr newChatPhoto);

		bool isDeleteChatPhoto() const;
		void setDeleteChatPhoto(bool deleteChatPhoto);

		bool isGroupChatCreated() const;
		void setGroupChatCreated(bool groupChatCreated);

		bool isSuperGroupChatCreated() const;
		void setSuperGroupChatCreated(bool superGroupChatCreated);

		bool isChannelChatCreated() const;
		void setChannelChatCreated(bool channelChatCreated);

		std::int64_t getMigrateToChatId() const;
		void setMigrateToChatId(std::int64_t migrateToChatId);

		std::int64_t getMigrateFromChatId() const;
		void setMigrateFromChatId(std::int64_t migrateFromChatId);

		const MessagePtr getPinnedMessage() const;
		void setPinnedMessage(MessagePtr pinnedMessage);

		void swap(Message& other) noexcept;

		const Message& operator=(Message other) noexcept;

	private:
		int id_;
		UserPtr from_;
		std::time_t date_;
		Chat chat_;
		UserPtr forwardFrom_;
		ChatPtr forwardFromChat_;
		std::time_t forwardDate_;
		MessagePtr replyToMessage_;
		std::time_t editDate_;
		std::string text_;
		MessageEntities entities_;
		AttachmentPtr attachment_;
		std::string caption_;
		UserPtr newChatMember_;
		UserPtr leftChatMember_;
		std::string newChatTitle_;
		PhotoSizeArrayPtr newChatPhoto_;
		bool deleteChatPhoto_;
		bool groupChatCreated_;
		bool superGroupChatCreated_;
		bool channelChatCreated_;
		std::int64_t migrateToChatId_;
		std::int64_t migrateFromChatId_;
		MessagePtr pinnedMessage_;
	};

	void swap(Message& lhs, Message& rhs);
}

#endif // TELEBOTXX_MESSAGE_HPP
