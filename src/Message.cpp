#include <telebotxx/Message.hpp>

using namespace telebotxx;

MessageEntity::MessageEntity()
		: type_(Type::Mention),
		  offset_(-1),
		  length_(0)
{
}

MessageEntity::MessageEntity(const MessageEntity&) = default;
MessageEntity::MessageEntity(MessageEntity&&) = default;
MessageEntity::~MessageEntity() = default;

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

const std::string& MessageEntity::getUrl() const
{
	return url_;
}

void MessageEntity::setUrl(const std::string& url)
{
	url_ = url;
}

const User& MessageEntity::getUser() const
{
	return user_;
}

void MessageEntity::setUser(const User& user)
{
	user_ = user;
}

void MessageEntity::swap(MessageEntity& other) noexcept
{
	using std::swap;
	swap(type_, other.type_);
	swap(offset_, other.offset_);
	swap(length_, other.length_);
	swap(url_, other.url_);
	swap(user_, other.user_);
}

const MessageEntity& MessageEntity::operator=(MessageEntity other)
{
	swap(other);
	return *this;
}

MessageEntity::Type telebotxx::messageEntityTypeFromString(const std::string& str)
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

Message::Message()
		: id_(-1)
{
}

Message::Message(const Message&) = default;
Message::Message(Message&&) = default;
Message::~Message() = default;

int Message::getId() const
{
	return id_;
}

void Message::setId(int id)
{
	id_ = id;
}

const UserPtr Message::getFrom() const
{
	return from_;
}

void Message::setFrom(UserPtr from)
{
	from_ = from;
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

void Message::setChat(const Chat& chat)
{
	chat_ = chat;
}

const UserPtr Message::getForwardFrom() const
{
	return forwardFrom_;
}

void Message::setForwardFrom(UserPtr forwardFrom)
{
	forwardFrom_ = forwardFrom;
}

const ChatPtr Message::getForwardFromChat() const
{
	return forwardFromChat_;
}

void Message::setForwardFromChat(ChatPtr forwardFromChat)
{
	forwardFromChat_ = forwardFromChat;
}

time_t Message::getForwardDate() const
{
	return forwardDate_;
}

void Message::setForwardDate(time_t forwardDate)
{
	forwardDate_ = forwardDate;
}

const MessagePtr Message::getReplyToMessage() const
{
	return replyToMessage_;
}

void Message::setReplyToMessage(MessagePtr replyToMessage)
{
	replyToMessage_ = replyToMessage;
}

time_t Message::getEditDate() const
{
	return editDate_;
}

void Message::setEditDate(time_t editDate)
{
	editDate_ = editDate;
}

const std::string& Message::getText() const
{
	return text_;
}

void Message::setText(const std::string& text)
{
	text_ = text;
}

const MessageEntities& Message::getEntities() const
{
	return entities_;
}

void Message::setEntities(MessageEntities&& entities)
{
	entities_ = entities;
}

const AttachmentPtr Message::getAttachment() const
{
	return attachment_;
}

void Message::setAttachment(AttachmentPtr attachment)
{
	attachment_ = attachment;
}

const std::string& Message::getCaption() const
{
	return caption_;
}

void Message::setCaption(const std::string& caption)
{
	caption_ = caption;
}

const UserPtr Message::getNewChatMember() const
{
	return newChatMember_;
}

void Message::setNewChatMember(UserPtr newChatMember)
{
	newChatMember_ = newChatMember;
}

const UserPtr Message::getLeftChatMember() const
{
	return leftChatMember_;
}

void Message::setLeftChatMember(UserPtr leftChatMember)
{
	leftChatMember_ = leftChatMember;
}

const std::string& Message::getNewChatTitle() const
{
	return newChatTitle_;
}

void Message::setNewChatTitle(const std::string& newChatTitle)
{
	newChatTitle_ = newChatTitle;
}

const PhotoSizeArrayPtr Message::getNewChatPhoto() const
{
	return newChatPhoto_;
}

void Message::setNewChatPhoto(PhotoSizeArrayPtr newChatPhoto)
{
	newChatPhoto_ = newChatPhoto;
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

std::int64_t Message::getMigrateToChatId() const
{
	return migrateToChatId_;
}

void Message::setMigrateToChatId(std::int64_t migrateToChatId)
{
	migrateToChatId_ = migrateToChatId;
}

std::int64_t Message::getMigrateFromChatId() const
{
	return migrateFromChatId_;
}

void Message::setMigrateFromChatId(std::int64_t migrateFromChatId)
{
	migrateFromChatId_ = migrateFromChatId;
}

const MessagePtr Message::getPinnedMessage() const
{
	return pinnedMessage_;
}

void Message::setPinnedMessage(MessagePtr pinnedMessage)
{
	pinnedMessage_ = pinnedMessage;
}

void Message::swap(Message& other) noexcept
{
	using std::swap;
	swap(id_, other.id_);
	swap(from_, other.from_);
	swap(date_, other.date_);
	swap(chat_, other.chat_);
	swap(forwardFrom_, other.forwardFrom_);
	swap(forwardFromChat_, other.forwardFromChat_);
	swap(forwardDate_, other.forwardDate_);
	swap(replyToMessage_, other.replyToMessage_);
	swap(editDate_, other.editDate_);
	swap(text_, other.text_);
	swap(entities_, other.entities_);
	swap(attachment_, other.attachment_);
	swap(caption_, other.caption_);
	swap(newChatMember_, other.newChatMember_);
	swap(leftChatMember_, other.leftChatMember_);
	swap(newChatTitle_, other.newChatTitle_);
	swap(newChatPhoto_, other.newChatPhoto_);
	swap(deleteChatPhoto_, other.deleteChatPhoto_);
	swap(groupChatCreated_, other.groupChatCreated_);
	swap(superGroupChatCreated_, other.superGroupChatCreated_);
	swap(channelChatCreated_, other.channelChatCreated_);
	swap(migrateToChatId_, other.migrateToChatId_);
	swap(migrateFromChatId_, other.migrateFromChatId_);
	swap(pinnedMessage_, other.pinnedMessage_);
}

const Message& Message::operator=(Message other) noexcept
{
	swap(other);
	return *this;
}

void telebotxx::swap(Message& lhs, Message& rhs)
{
	lhs.swap(rhs);
}
