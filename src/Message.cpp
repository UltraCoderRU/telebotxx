#include <telebotxx/Message.hpp>

#include <stdexcept>

namespace telebotxx {

MessageEntity::MessageEntity()
	: type_(Type::Mention),
	  offset_(-1),
	  length_(0)
{
}

MessageEntity::Type MessageEntity::getType() const
{
	return type_;
}

void MessageEntity::setType(MessageEntity::Type type)
{
	type_ = type;
}

int MessageEntity::getOffset() const
{
	return offset_;
}

void MessageEntity::setOffset(int offset)
{
	offset_ = offset;
}

size_t MessageEntity::getLength() const
{
	return length_;
}

void MessageEntity::setLength(size_t length)
{
	length_ = length;
}

const std::optional<std::string>& MessageEntity::getUrl() const
{
	return url_;
}

void MessageEntity::setUrl(std::string url)
{
	url_ = std::move(url);
}

const std::optional<User>& MessageEntity::getUser() const
{
	return user_;
}

void MessageEntity::setUser(User user)
{
	user_ = std::move(user);
}

MessageEntity::Type messageEntityTypeFromString(const std::string& str)
{
	if (str == "mention")
		return MessageEntity::Type::Mention;
	else if (str == "hashtag")
		return MessageEntity::Type::Hashtag;
	else if (str == "bot_command")
		return MessageEntity::Type::BotCommand;
	else if (str == "url")
		return MessageEntity::Type::Url;
	else if (str == "email")
		return MessageEntity::Type::Email;
	else if (str == "bold")
		return MessageEntity::Type::Bold;
	else if (str == "italic")
		return MessageEntity::Type::Italic;
	else if (str == "code")
		return MessageEntity::Type::Code;
	else if (str == "pre")
		return MessageEntity::Type::Pre;
	else if (str == "text_link")
		return MessageEntity::Type::TextLink;
	else if (str == "text_mention")
		return MessageEntity::Type::TextMention;
	else
		throw std::invalid_argument("Unknown message entity type");
}

////////////////////////////////////////////////////////////////

Message::Message()
	: id_(-1),
	  deleteChatPhoto_(false),
	  groupChatCreated_(false),
	  superGroupChatCreated_(false),
	  channelChatCreated_(false)
{
}

int Message::getId() const
{
	return id_;
}

void Message::setId(int id)
{
	id_ = id;
}

const std::optional<User>& Message::getFrom() const
{
	return from_;
}

void Message::setFrom(std::optional<User> from)
{
	from_ = std::move(from);
}

time_t Message::getDate() const
{
	return date_;
}

void Message::setDate(time_t date)
{
	date_ = date;
}

const Chat& Message::getChat() const
{
	return chat_;
}

void Message::setChat(Chat chat)
{
	chat_ = std::move(chat);
}

const std::optional<User>& Message::getForwardFrom() const
{
	return forwardFrom_;
}

void Message::setForwardFrom(std::optional<User> forwardFrom)
{
	forwardFrom_ = std::move(forwardFrom);
}

const std::optional<Chat>& Message::getForwardFromChat() const
{
	return forwardFromChat_;
}

void Message::setForwardFromChat(std::optional<Chat> forwardFromChat)
{
	forwardFromChat_ = std::move(forwardFromChat);
}

const std::optional<time_t>& Message::getForwardDate() const
{
	return forwardDate_;
}

void Message::setForwardDate(std::optional<time_t> forwardDate)
{
	forwardDate_ = forwardDate;
}

MessagePtr Message::getReplyToMessage() const
{
	return replyToMessage_;
}

void Message::setReplyToMessage(MessagePtr replyToMessage)
{
	replyToMessage_ = replyToMessage;
}

const std::optional<time_t>& Message::getEditDate() const
{
	return editDate_;
}

void Message::setEditDate(std::optional<time_t> editDate)
{
	editDate_ = editDate;
}

const std::optional<std::string>& Message::getText() const
{
	return text_;
}

void Message::setText(std::optional<std::string> text)
{
	text_ = std::move(text);
}

const std::optional<MessageEntities>& Message::getEntities() const
{
	return entities_;
}

void Message::setEntities(std::optional<MessageEntities> entities)
{
	entities_ = std::move(entities);
}

const std::optional<Attachment>& Message::getAttachment() const
{
	return attachment_;
}

void Message::setAttachment(std::optional<Attachment> attachment)
{
	attachment_ = std::move(attachment);
}

const std::optional<std::string>& Message::getCaption() const
{
	return caption_;
}

void Message::setCaption(std::optional<std::string> caption)
{
	caption_ = std::move(caption);
}

const std::optional<User>& Message::getNewChatMember() const
{
	return newChatMember_;
}

void Message::setNewChatMember(std::optional<User> newChatMember)
{
	newChatMember_ = std::move(newChatMember);
}

const std::optional<User>& Message::getLeftChatMember() const
{
	return leftChatMember_;
}

void Message::setLeftChatMember(std::optional<User> leftChatMember)
{
	leftChatMember_ = std::move(leftChatMember);
}

const std::optional<std::string>& Message::getNewChatTitle() const
{
	return newChatTitle_;
}

void Message::setNewChatTitle(std::optional<std::string> newChatTitle)
{
	newChatTitle_ = std::move(newChatTitle);
}

const std::optional<PhotoSizeArray> Message::getNewChatPhoto() const
{
	return newChatPhoto_;
}

void Message::setNewChatPhoto(std::optional<PhotoSizeArray> newChatPhoto)
{
	newChatPhoto_ = std::move(newChatPhoto);
}

bool Message::isDeleteChatPhoto() const
{
	return deleteChatPhoto_;
}

void Message::setDeleteChatPhoto(bool deleteChatPhoto)
{
	deleteChatPhoto_ = deleteChatPhoto;
}

bool Message::isGroupChatCreated() const
{
	return groupChatCreated_;
}

void Message::setGroupChatCreated(bool groupChatCreated)
{
	groupChatCreated_ = groupChatCreated;
}

bool Message::isSuperGroupChatCreated() const
{
	return superGroupChatCreated_;
}

void Message::setSuperGroupChatCreated(bool superGroupChatCreated)
{
	superGroupChatCreated_ = superGroupChatCreated;
}

bool Message::isChannelChatCreated() const
{
	return channelChatCreated_;
}

void Message::setChannelChatCreated(bool channelChatCreated)
{
	channelChatCreated_ = channelChatCreated;
}

const std::optional<std::int64_t>& Message::getMigrateToChatId() const
{
	return migrateToChatId_;
}

void Message::setMigrateToChatId(std::optional<std::int64_t> migrateToChatId)
{
	migrateToChatId_ = migrateToChatId;
}

const std::optional<std::int64_t>& Message::getMigrateFromChatId() const
{
	return migrateFromChatId_;
}

void Message::setMigrateFromChatId(std::optional<std::int64_t> migrateFromChatId)
{
	migrateFromChatId_ = migrateFromChatId;
}

MessagePtr Message::getPinnedMessage() const
{
	return pinnedMessage_;
}

void Message::setPinnedMessage(MessagePtr pinnedMessage)
{
	pinnedMessage_ = pinnedMessage;
}

}
