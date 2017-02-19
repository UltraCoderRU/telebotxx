#ifndef TELEBOTXX_MESSAGE_HPP
#define TELEBOTXX_MESSAGE_HPP

#include "User.hpp"
#include "Chat.hpp"
#include "Attachment.hpp"
#include "Optional.hpp"

#include <vector>
#include <ctime>
#include <memory>
#include <boost/variant/variant.hpp>

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

	const optional<std::string>& getUrl() const;
	void setUrl(std::string url);

	const optional<User>& getUser() const;
	void setUser(User user);

private:
	Type type_;
	int offset_;
	std::size_t length_;
	optional<std::string> url_;
	optional<User> user_;
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

	const optional<User>& getFrom() const;
	void setFrom(optional<User> from);

	time_t getDate() const;
	void setDate(time_t date);

	const Chat& getChat() const;
	void setChat(Chat chat);

	const optional<User>& getForwardFrom() const;
	void setForwardFrom(optional<User> forwardFrom);

	const optional<Chat>& getForwardFromChat() const;
	void setForwardFromChat(optional<Chat> forwardFromChat);

	const optional<time_t>& getForwardDate() const;
	void setForwardDate(optional<time_t> forwardDate);

	MessagePtr getReplyToMessage() const;
	void setReplyToMessage(MessagePtr replyToMessage);

	const optional<time_t>& getEditDate() const;
	void setEditDate(optional<time_t> editDate);

	const optional<std::string>& getText() const;
	void setText(optional<std::string> text);

	const optional<MessageEntities>& getEntities() const;
	void setEntities(optional<MessageEntities> entities);

	const optional<Attachment>& getAttachment() const;
	void setAttachment(optional<Attachment> attachment);

	const optional<std::string>& getCaption() const;
	void setCaption(optional<std::string> caption);

	const optional<User>& getNewChatMember() const;
	void setNewChatMember(optional<User> newChatMember);

	const optional<User>& getLeftChatMember() const;
	void setLeftChatMember(optional<User> leftChatMember);

	const optional<std::string>& getNewChatTitle() const;
	void setNewChatTitle(optional<std::string> newChatTitle);

	const optional<PhotoSizeArray> getNewChatPhoto() const;
	void setNewChatPhoto(optional<PhotoSizeArray> newChatPhoto);

	bool isDeleteChatPhoto() const;
	void setDeleteChatPhoto(bool deleteChatPhoto);

	bool isGroupChatCreated() const;
	void setGroupChatCreated(bool groupChatCreated);

	bool isSuperGroupChatCreated() const;
	void setSuperGroupChatCreated(bool superGroupChatCreated);

	bool isChannelChatCreated() const;
	void setChannelChatCreated(bool channelChatCreated);

	const optional<std::int64_t>& getMigrateToChatId() const;
	void setMigrateToChatId(optional<std::int64_t> migrateToChatId);

	const optional<std::int64_t>& getMigrateFromChatId() const;
	void setMigrateFromChatId(optional<std::int64_t> migrateFromChatId);

	MessagePtr getPinnedMessage() const;
	void setPinnedMessage(MessagePtr pinnedMessage);

private:
	int id_;
	optional<User> from_;
	std::time_t date_;
	Chat chat_;
	optional<User> forwardFrom_;
	optional<Chat> forwardFromChat_;
	optional<int> forwardFromMessageId_;
	optional<std::time_t> forwardDate_;
	MessagePtr replyToMessage_;
	optional<std::time_t> editDate_;
	optional<std::string> text_;
	optional<MessageEntities> entities_;
	optional<Attachment> attachment_;
	optional<std::string> caption_;
	optional<User> newChatMember_;
	optional<User> leftChatMember_;
	optional<std::string> newChatTitle_;
	optional<PhotoSizeArray> newChatPhoto_;
	bool deleteChatPhoto_;
	bool groupChatCreated_;
	bool superGroupChatCreated_;
	bool channelChatCreated_;
	optional<std::int64_t> migrateToChatId_;
	optional<std::int64_t> migrateFromChatId_;
	MessagePtr pinnedMessage_;
};

}

#endif // TELEBOTXX_MESSAGE_HPP
