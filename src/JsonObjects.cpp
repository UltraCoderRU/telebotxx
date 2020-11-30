#include "JsonObjects.hpp"

#include <cstdint>

namespace telebotxx {
namespace impl {
template <>
bool is<int>(const rapidjson::Value& obj)
{
	return obj.IsInt();
}
template <>
bool is<std::int64_t>(const rapidjson::Value& obj)
{
	return obj.IsInt64();
}
template <>
bool is<bool>(const rapidjson::Value& obj)
{
	return obj.IsBool();
}
template <>
bool is<std::string>(const rapidjson::Value& obj)
{
	return obj.IsString();
}

template <>
const int get(const rapidjson::Value& obj)
{
	return obj.GetInt();
}
template <>
const std::int64_t get(const rapidjson::Value& obj)
{
	return obj.GetInt64();
}
template <>
const bool get(const rapidjson::Value& obj)
{
	return obj.GetBool();
}
template <>
const std::string get(const rapidjson::Value& obj)
{
	return obj.GetString();
}

} // namespace impl

bool check(const rapidjson::Value& obj, const char* name)
{
	if (auto value = parse<bool>(obj, name, OPTIONAL))
		return *value;
	else
		return false;
}

const rapidjson::Value&
parseObject(const rapidjson::Value& parent, const char* name, bool required, bool& found)
{
	if (parent.HasMember(name))
	{
		if (parent[name].IsObject())
		{
			found = true;
			return parent[name];
		}
		else
			throw ParseError(std::string("Field '") + name + "' has invalid type");
	}
	else if (required)
		throw ParseError(std::string("Field '") + name + "' not found");
	else
	{
		found = false;
		return parent;
	}
}

const rapidjson::Value&
parseArray(const rapidjson::Value& parent, const char* name, bool required, bool& found)
{
	if (parent.HasMember(name))
	{
		if (parent[name].IsArray())
		{
			found = true;
			return parent[name];
		}
		else
			throw ParseError(std::string("Field '") + name + "' has invalid type");
	}
	else if (required)
		throw ParseError(std::string("Field '") + name + "' not found");
	else
	{
		found = false;
		return parent;
	}
}

template <>
std::optional<Chat> parse<Chat>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<Chat> chat;
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		chat.emplace();
		chat->setId(require<std::int64_t>(obj, "id"));
		chat->setType(chatTypeFromString(require<std::string>(obj, "type")));
		chat->setTitle(allow<std::string>(obj, "title"));
		chat->setUsername(parse<std::string>(obj, "username", OPTIONAL));
		chat->setFirstName(parse<std::string>(obj, "first_name", OPTIONAL));
		chat->setLastName(parse<std::string>(obj, "last_name", OPTIONAL));
		chat->setAllAdmins(check(obj, "all_members_are_administrators"));
	}
	return chat;
}

template <>
std::optional<User> parse<User>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<User> user;
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		user.emplace();
		user->setId(require<int>(obj, "id"));
		user->setFirstName(require<std::string>(obj, "first_name"));
		user->setLastName(allow<std::string>(obj, "last_name"));
	}
	return user;
}

PhotoSize parsePhotoSize(const rapidjson::Value& obj)
{
	PhotoSize photo;
	photo.setFileId(require<std::string>(obj, "file_id"));
	photo.setWidth(require<int>(obj, "width"));
	photo.setHeight(require<int>(obj, "height"));
	photo.setFileSize(allow<int>(obj, "file_size"));
	return photo;
}

template <>
std::optional<PhotoSize>
parse<PhotoSize>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<PhotoSize> photo;
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		photo.emplace(parsePhotoSize(obj));
	}
	return photo;
}

template <>
std::optional<PhotoSizeArray>
parse<PhotoSizeArray>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<PhotoSizeArray> photos;
	bool found;
	auto& obj = parseArray(parent, name, required, found);
	if (found)
	{
		photos.emplace();
		photos->reserve(obj.GetArray().Size());
		for (auto& elem : obj.GetArray())
			photos->emplace_back(parsePhotoSize(elem));
	}
	return photos;
}

template <>
std::optional<Audio> parse<Audio>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<Audio> audio;
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		audio->setFileId(require<std::string>(obj, "file_id"));
		audio->setDuration(require<int>(obj, "duration"));
		audio->setPerformer(allow<std::string>(obj, "performer"));
		audio->setTitle(allow<std::string>(obj, "title"));
		audio->setMimeType(allow<std::string>(obj, "mime_type"));
		audio->setFileSize(allow<int>(obj, "file_size"));
	}
	return audio;
}

template <>
std::optional<Document> parse<Document>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<Document> document;
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		document.emplace();
		document->setFileId(require<std::string>(obj, "file_id"));
		document->setThumb(allow<PhotoSize>(obj, "thumb"));
		document->setFileName(allow<std::string>(obj, "file_name"));
		document->setMimeType(allow<std::string>(obj, "mime_type"));
		document->setFileSize(allow<int>(obj, "file_size"));
	}
	return document;
}

template <>
std::optional<Sticker> parse<Sticker>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<Sticker> sticker;
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		sticker.emplace();
		sticker->setFileId(require<std::string>(obj, "file_id"));
		sticker->setWidth(require<int>(obj, "width"));
		sticker->setHeight(require<int>(obj, "height"));
		sticker->setThumb(allow<PhotoSize>(obj, "thumb"));
		sticker->setEmoji(allow<std::string>(obj, "emoji"));
		sticker->setFileSize(allow<int>(obj, "file_size"));
	}
	return sticker;
}

template <>
std::optional<Attachment>
parse<Attachment>(const rapidjson::Value& parent, const char* name, bool required)
{
	std::optional<Attachment> attachment;
	if (auto photo = allow<PhotoSizeArray>(parent, "photo"))
		attachment.emplace(std::move(*photo));
	else if (auto audio = allow<Audio>(parent, "audio"))
		attachment.emplace(std::move(*audio));
	else if (auto document = allow<Document>(parent, "document"))
		attachment.emplace(std::move(*document));
	else if (auto sticker = allow<Sticker>(parent, "sticker"))
		attachment.emplace(std::move(*sticker));
	/// \todo Other attachments
	return attachment;
}

std::unique_ptr<Message> parseMessage(const rapidjson::Value& parent, const char* name, bool required)
{
	std::unique_ptr<Message> message;
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		message = std::make_unique<Message>();
		message->setId(require<int>(obj, "message_id"));
		message->setFrom(allow<User>(obj, "from"));
		message->setDate(require<int>(obj, "date"));
		message->setChat(require<Chat>(obj, "chat"));
		message->setForwardFrom(allow<User>(obj, "forward_from"));
		message->setForwardFromChat(allow<Chat>(obj, "forward_from_chat"));
		message->setForwardDate(allow<std::int64_t>(obj, "forward_date"));
		message->setReplyToMessage(parseMessage(obj, "reply_to_message", OPTIONAL));
		message->setEditDate(allow<std::int64_t>(obj, "edit_date"));
		message->setText(parse<std::string>(obj, "text", OPTIONAL));
		// message->setEntities(parseEntities(obj, "entities", OPTIONAL));
		message->setAttachment(allow<Attachment>(obj, ""));
		message->setCaption(allow<std::string>(obj, "caption"));
		message->setNewChatMember(allow<User>(obj, "new_chat_member"));
		message->setLeftChatMember(allow<User>(obj, "left_chat_member"));
		message->setNewChatTitle(allow<std::string>(obj, "new_chat_title"));
		message->setNewChatPhoto(allow<PhotoSizeArray>(obj, "new_chat_photo"));
		message->setDeleteChatPhoto(check(obj, "delete_chat_photo"));
		message->setGroupChatCreated(check(obj, "group_chat_created"));
		message->setSuperGroupChatCreated(check(obj, "supergroup_chat_created"));
		message->setChannelChatCreated(check(obj, "channel_chat_created"));
		message->setMigrateToChatId(allow<std::int64_t>(obj, "migrate_to_chat_id"));
		message->setMigrateFromChatId(allow<std::int64_t>(obj, "migrate_from_chat_id"));
		message->setPinnedMessage(parseMessage(obj, "pinned_message", OPTIONAL));
	}
	return message;
}

/// \todo Other updates
Update parseUpdate(const rapidjson::Value& obj)
{
	int id = require<int>(obj, "update_id");

	std::unique_ptr<Message> message;
	if ((message = parseMessage(obj, "message", OPTIONAL)))
		return Update(id, Update::Type::Message, std::move(message));
	else if ((message = parseMessage(obj, "edited_message", OPTIONAL)))
		return Update(id, Update::Type::EditedMessage, std::move(message));
	else if ((message = parseMessage(obj, "channel_post", OPTIONAL)))
		return Update(id, Update::Type::ChannelPost, std::move(message));
	else if ((message = parseMessage(obj, "edited_channel_post", OPTIONAL)))
		return Update(id, Update::Type::EditedChannelPost, std::move(message));
	else
		throw ParseError("Unknown update type");
}

Updates parseUpdates(const rapidjson::Value& parent, const char* name)
{
	Updates updates;
	bool found;
	auto& obj = parseArray(parent, name, REQUIRED, found);
	if (found)
	{
		updates.reserve(obj.GetArray().Size());
		for (auto& elem : obj.GetArray())
			updates.emplace_back(parseUpdate(elem));
	}
	return updates;
}

void checkResponse(const rapidjson::Document& doc)
{
	if (!doc.IsObject())
		throw ParseError("Object expected");

	// Get status
	bool ok = require<bool>(doc, "ok");
	if (!ok)
	{
		int code = require<int>(doc, "error_code");
		std::string description(require<std::string>(doc, "description"));
		throw ApiError(code, description);
	}
}

} // namespace telebotxx
