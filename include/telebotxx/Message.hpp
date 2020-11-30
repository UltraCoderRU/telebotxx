#ifndef TELEBOTXX_MESSAGE_HPP
#define TELEBOTXX_MESSAGE_HPP

#include "Attachment.hpp"
#include "Chat.hpp"
#include "User.hpp"

#include <ctime>
#include <memory>
#include <optional>
#include <vector>

namespace telebotxx {

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

	Type getType() const;
	void setType(Type type);

	int getOffset() const;
	void setOffset(int offset);

	size_t getLength() const;
	void setLength(size_t length);

	const std::optional<std::string>& getUrl() const;
	void setUrl(std::string url);

	const std::optional<User>& getUser() const;
	void setUser(User user);

private:
	Type type_;
	int offset_;
	std::size_t length_;
	std::optional<std::string> url_;
	std::optional<User> user_;
};

MessageEntity::Type messageEntityTypeFromString(const std::string& str);

using MessageEntities = std::vector<MessageEntity>;

class Message;
using MessagePtr = std::shared_ptr<Message>;

class Message
{
public:
	Message();

	int getId() const;
	void setId(int id);

	const std::optional<User>& getFrom() const;
	void setFrom(std::optional<User> from);

	time_t getDate() const;
	void setDate(time_t date);

	const Chat& getChat() const;
	void setChat(Chat chat);

	const std::optional<User>& getForwardFrom() const;
	void setForwardFrom(std::optional<User> forwardFrom);

	const std::optional<Chat>& getForwardFromChat() const;
	void setForwardFromChat(std::optional<Chat> forwardFromChat);

	const std::optional<time_t>& getForwardDate() const;
	void setForwardDate(std::optional<time_t> forwardDate);

	MessagePtr getReplyToMessage() const;
	void setReplyToMessage(MessagePtr replyToMessage);

	const std::optional<time_t>& getEditDate() const;
	void setEditDate(std::optional<time_t> editDate);

	const std::optional<std::string>& getText() const;
	void setText(std::optional<std::string> text);

	const std::optional<MessageEntities>& getEntities() const;
	void setEntities(std::optional<MessageEntities> entities);

	const std::optional<Attachment>& getAttachment() const;
	void setAttachment(std::optional<Attachment> attachment);

	const std::optional<std::string>& getCaption() const;
	void setCaption(std::optional<std::string> caption);

	const std::optional<User>& getNewChatMember() const;
	void setNewChatMember(std::optional<User> newChatMember);

	const std::optional<User>& getLeftChatMember() const;
	void setLeftChatMember(std::optional<User> leftChatMember);

	const std::optional<std::string>& getNewChatTitle() const;
	void setNewChatTitle(std::optional<std::string> newChatTitle);

	const std::optional<PhotoSizeArray> getNewChatPhoto() const;
	void setNewChatPhoto(std::optional<PhotoSizeArray> newChatPhoto);

	bool isDeleteChatPhoto() const;
	void setDeleteChatPhoto(bool deleteChatPhoto);

	bool isGroupChatCreated() const;
	void setGroupChatCreated(bool groupChatCreated);

	bool isSuperGroupChatCreated() const;
	void setSuperGroupChatCreated(bool superGroupChatCreated);

	bool isChannelChatCreated() const;
	void setChannelChatCreated(bool channelChatCreated);

	const std::optional<std::int64_t>& getMigrateToChatId() const;
	void setMigrateToChatId(std::optional<std::int64_t> migrateToChatId);

	const std::optional<std::int64_t>& getMigrateFromChatId() const;
	void setMigrateFromChatId(std::optional<std::int64_t> migrateFromChatId);

	MessagePtr getPinnedMessage() const;
	void setPinnedMessage(MessagePtr pinnedMessage);

private:
	int id_;
	std::optional<User> from_;
	std::time_t date_;
	Chat chat_;
	std::optional<User> forwardFrom_;
	std::optional<Chat> forwardFromChat_;
	std::optional<int> forwardFromMessageId_;
	std::optional<std::time_t> forwardDate_;
	MessagePtr replyToMessage_;
	std::optional<std::time_t> editDate_;
	std::optional<std::string> text_;
	std::optional<MessageEntities> entities_;
	std::optional<Attachment> attachment_;
	std::optional<std::string> caption_;
	std::optional<User> newChatMember_;
	std::optional<User> leftChatMember_;
	std::optional<std::string> newChatTitle_;
	std::optional<PhotoSizeArray> newChatPhoto_;
	bool deleteChatPhoto_;
	bool groupChatCreated_;
	bool superGroupChatCreated_;
	bool channelChatCreated_;
	std::optional<std::int64_t> migrateToChatId_;
	std::optional<std::int64_t> migrateFromChatId_;
	MessagePtr pinnedMessage_;
};

} // namespace telebotxx

#endif // TELEBOTXX_MESSAGE_HPP
