#include "JsonObjects.hpp"
#include <telebotxx/Exception.hpp>

#include <cstdint>

namespace telebotxx {
namespace impl {

template<typename T> bool is(const rapidjson::Value& obj);
template<> bool is<int>(const rapidjson::Value& obj) { return obj.IsInt(); }
template<> bool is<std::int64_t>(const rapidjson::Value& obj) { return obj.IsInt64(); }
template<> bool is<bool>(const rapidjson::Value& obj) { return obj.IsBool(); }
template<> bool is<std::string>(const rapidjson::Value& obj) { return obj.IsString(); }

template<typename T> const T get(const rapidjson::Value& obj);
template<> const int get(const rapidjson::Value& obj) { return obj.GetInt(); }
template<> const std::int64_t get(const rapidjson::Value& obj) { return obj.GetInt64(); }
template<> const bool get(const rapidjson::Value& obj) { return obj.GetBool(); }
template<> const std::string get(const rapidjson::Value& obj) { return obj.GetString(); }

template<typename T> const T null();
template<> const int null() { return 0; }
template<> const std::int64_t null() { return 0; }
template<> const bool null() { return false; }
template<> const std::string null() { return ""; }

}

template<typename T>
const T parse(const rapidjson::Value& obj, const char* name, bool required)
{
	if (obj.HasMember(name))
	{
		if (impl::is<T>(obj[name]))
			return impl::get<T>(obj[name]);
		else
			throw ParseError(std::string("Field '") + name + "' has invalid type");
	}
	else if (required)
		throw ParseError(std::string("Field '") + name + "' not found");
	else
		return impl::null<T>();
}

const rapidjson::Value& parseObject(const rapidjson::Value& parent, const char* name, bool required, bool& found)
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

const rapidjson::Value& parseArray(const rapidjson::Value& parent, const char* name, bool required, bool& found)
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

std::unique_ptr<PhotoSize> parsePhotoSize(const rapidjson::Value& obj)
{
	auto photo = std::make_unique<PhotoSize>();
	photo->setFileId(parse<std::string>(obj, "file_id", REQUIRED));
	photo->setWidth(parse<int>(obj, "width", REQUIRED));
	photo->setHeight(parse<int>(obj, "height", REQUIRED));
	photo->setFileSize(parse<int>(obj, "file_size", OPTIONAL));
	return photo;
}

std::unique_ptr<PhotoSize> parsePhotoSize(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		return parsePhotoSize(obj);
	}
	else
		return nullptr;
}

std::unique_ptr<PhotoSizeArray> parsePhotoSizeArray(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseArray(parent, name, required, found);
	if (found)
	{
		std::vector<PhotoSize> photos;
		for (auto& elem : obj.GetArray())
		{
			auto photo = parsePhotoSize(elem);
			photos.push_back(std::move(*photo));
		}
		auto result = std::make_unique<PhotoSizeArray>();
		result->setArray(photos);
		return result;
	}
	else
		return nullptr;
}

std::unique_ptr<Audio> parseAudio(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		auto audio = std::make_unique<Audio>();
		audio->setFileId(parse<std::string>(obj, "file_id", REQUIRED));
		audio->setDuration(parse<int>(obj, "duration", REQUIRED));
		audio->setPerformer(parse<std::string>(obj, "performer", OPTIONAL));
		audio->setTitle(parse<std::string>(obj, "title", OPTIONAL));
		audio->setMimeType(parse<std::string>(obj, "mime_type", OPTIONAL));
		audio->setFileSize(parse<int>(obj, "file_size", OPTIONAL));
		return audio;
	}
	else
		return nullptr;
}

std::unique_ptr<Document> parseDocument(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		auto document = std::make_unique<Document>();
		document->setFileId(parse<std::string>(obj, "file_id", REQUIRED));
		document->setThumb(parsePhotoSize(obj, "thumb", OPTIONAL));
		document->setFileName(parse<std::string>(obj, "file_name", OPTIONAL));
		document->setMimeType(parse<std::string>(obj, "mime_type", OPTIONAL));
		document->setFileSize(parse<int>(obj, "file_size", OPTIONAL));
		return document;
	}
	else
		return nullptr;
}

std::unique_ptr<Sticker> parseSticker(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		auto sticker = std::make_unique<Sticker>();
		sticker->setFileId(parse<std::string>(obj, "file_id", REQUIRED));
		sticker->setWidth(parse<int>(obj, "width", REQUIRED));
		sticker->setHeight(parse<int>(obj, "height", REQUIRED));
		sticker->setThumb(parsePhotoSize(obj, "thumb", OPTIONAL));
		sticker->setEmoji(parse<std::string>(obj, "emoji", OPTIONAL));
		sticker->setFileSize(parse<int>(obj, "file_size", OPTIONAL));
		return sticker;
	}
	else
		return nullptr;
}

std::unique_ptr<Message> parseMessage(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		auto message = std::make_unique<Message>();

		message->setId(parse<int>(obj, "message_id", REQUIRED));
		message->setFrom(parseUser(obj, "from", OPTIONAL));
		message->setDate(parse<int>(obj, "date", REQUIRED));
		message->setChat(*parseChat(obj, "chat", REQUIRED));
		message->setForwardFrom(parseUser(obj, "forward_from", OPTIONAL));
		message->setForwardFromChat(parseChat(obj, "forward_from_chat", OPTIONAL));
		message->setForwardDate(parse<int>(obj, "forward_date", OPTIONAL));
		message->setReplyToMessage(parseMessage(obj, "reply_to_message", OPTIONAL));
		message->setEditDate(parse<int>(obj, "edit_date", OPTIONAL));
		message->setText(parse<std::string>(obj, "text", OPTIONAL));
		//message->setEntities(parseEntities(obj, "entities", OPTIONAL));

		/// \todo: Parse one of the possible attachments
		std::shared_ptr<Attachment> attachment;
		if (!(attachment = parsePhotoSizeArray(obj, "photo", OPTIONAL)))
			if (!(attachment = parseAudio(obj, "audio", OPTIONAL)))
				if (!(attachment = parseDocument(obj, "document", OPTIONAL)))
					attachment = parseSticker(obj, "sticker", OPTIONAL);
		message->setAttachment(attachment);

		message->setCaption(parse<std::string>(obj, "caption", OPTIONAL));
		message->setNewChatMember(parseUser(obj, "new_chat_member", OPTIONAL));
		message->setLeftChatMember(parseUser(obj, "left_chat_member", OPTIONAL));
		message->setNewChatTitle(parse<std::string>(obj, "new_chat_title", OPTIONAL));
		message->setNewChatPhoto(parsePhotoSizeArray(obj, "new_chat_photo", OPTIONAL));
		message->setDeleteChatPhoto(parse<bool>(obj, "delete_chat_photo", OPTIONAL));
		message->setGroupChatCreated(parse<bool>(obj, "group_chat_created", OPTIONAL));
		message->setSuperGroupChatCreated(parse<bool>(obj, "supergroup_chat_created", OPTIONAL));
		message->setChannelChatCreated(parse<bool>(obj, "channel_chat_created", OPTIONAL));
		message->setMigrateToChatId(parse<std::int64_t>(obj, "migrate_to_chat_id", OPTIONAL));
		message->setMigrateFromChatId(parse<std::int64_t>(obj, "migrate_from_chat_id", OPTIONAL));
		message->setPinnedMessage(parseMessage(obj, "pinned_message", OPTIONAL));

		return message;
	}
	else
		return nullptr;
}

std::unique_ptr<Chat> parseChat(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		auto chat = std::make_unique<Chat>();
		chat->setId(parse<std::int64_t>(obj, "id", REQUIRED));
		chat->setType(chatTypeFromString(parse<std::string>(obj, "type", REQUIRED)));
		chat->setTitle(parse<std::string>(obj, "title", OPTIONAL));
		chat->setUsername(parse<std::string>(obj, "username", OPTIONAL));
		chat->setFirstName(parse<std::string>(obj, "first_name", OPTIONAL));
		chat->setLastName(parse<std::string>(obj, "last_name", OPTIONAL));
		chat->setAllAdmins(parse<bool>(obj, "all_members_are_administrators", OPTIONAL));
		return chat;
	}
	else
		return nullptr;
}

/// \todo Other updates
std::unique_ptr<Update> parseUpdate(const rapidjson::Value& obj)
{
	int id = parse<int>(obj, "update_id", REQUIRED);

	std::unique_ptr<Message> message;
	if ((message = parseMessage(obj, "message", OPTIONAL)))
		return std::make_unique<MessageUpdate>(id, MessageUpdate::MessageType::Message, *message);
	else if ((message = parseMessage(obj, "edited_message", OPTIONAL)))
		return std::make_unique<MessageUpdate>(id, MessageUpdate::MessageType::EditedMessage, *message);
	else if ((message = parseMessage(obj, "channel_post", OPTIONAL)))
		return std::make_unique<MessageUpdate>(id, MessageUpdate::MessageType::ChannelPost, *message);
	else if ((message = parseMessage(obj, "edited_channel_post", OPTIONAL)))
		return std::make_unique<MessageUpdate>(id, MessageUpdate::MessageType::EditedChannelPost, *message);
	else
		///throw ParseError("Unknown update type");
		return nullptr;
}

std::unique_ptr<Updates> parseUpdates(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseArray(parent, name, required, found);
	if (found)
	{
		Updates updates;
		for (auto& elem : obj.GetArray())
			updates.emplace_back(parseUpdate(elem));
		return std::make_unique<Updates>(std::move(updates));
	}
	else
		return nullptr;
}

std::unique_ptr<User> parseUser(const rapidjson::Value& parent, const char* name, bool required)
{
	bool found;
	auto& obj = parseObject(parent, name, required, found);
	if (found)
	{
		auto user = std::make_unique<User>();
		user->setId(parse<int>(obj, "id", REQUIRED));
		user->setFirstName(parse<std::string>(obj, "first_name", REQUIRED));
		user->setLastName(parse<std::string>(obj, "last_name", OPTIONAL));
		user->setUsername(parse<std::string>(obj, "username", OPTIONAL));
		return user;
	}
	else
		return nullptr;
}

void checkResponse(const rapidjson::Document& doc)
{
	if (!doc.IsObject())
		throw ParseError("Object expected");

	// Get status
	bool ok = parse<bool>(doc, "ok", REQUIRED);
	if (!ok)
	{
		int code = parse<int>(doc, "error_code", REQUIRED);
		std::string description(parse<std::string>(doc, "description", REQUIRED));
		throw ApiError(code, description);
	}
}

}
