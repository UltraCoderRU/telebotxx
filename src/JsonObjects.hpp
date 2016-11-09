#ifndef TELEBOTXX_JSON_OBJECTS_HPP
#define TELEBOTXX_JSON_OBJECTS_HPP

#include <telebotxx/Attachment.hpp>
#include <telebotxx/Message.hpp>
#include <telebotxx/User.hpp>

#include <memory>

#include <rapidjson/document.h>

namespace telebotxx
{
	const bool REQUIRED = true;
	const bool OPTIONAL = false;

	/// \brief Parse JSON object to PhotoSize
	/// \param parent reference to parent JSON object
	/// \param name field with PhotoSize object
	/// \param required REQUIRED or OPTIONAL
	/// \return pointer to PhotoSize
	std::unique_ptr<PhotoSize> parsePhotoSize(const rapidjson::Value& parent, const char* name, bool required);

	/// \brief Parse JSON object to Audio
	/// \param parent reference to parent JSON object
	/// \param name field with Audio object
	/// \param required REQUIRED or OPTIONAL
	/// \return pointer to Audio
	std::unique_ptr<Audio> parseAudio(const rapidjson::Value& parent, const char* name, bool required);

	/// \brief Parse JSON object to Document
	/// \param parent reference to parent JSON object
	/// \param name field with Document object
	/// \param required REQUIRED or OPTIONAL
	/// \return pointer to Document
	std::unique_ptr<Document> parseDocument(const rapidjson::Value& parent, const char* name, bool required);

	/// \brief Parse JSON object to Sticker
	/// \param parent reference to parent JSON object
	/// \param name field with Sticker object
	/// \param required REQUIRED or OPTIONAL
	/// \return pointer to Sticker
	std::unique_ptr<Document> parseDocument(const rapidjson::Value& parent, const char* name, bool required);

	/// \brief Parse JSON object to Chat
	/// \param parent reference to parent JSON object
	/// \param name field with Chat object
	/// \param required REQUIRED or OPTIONAL
	/// \return pointer to Chat
	std::unique_ptr<Chat> parseChat(const rapidjson::Value& parent, const char* name, bool required);

	/// \brief Parse JSON object to User
	/// \param parent reference to parent JSON object
	/// \param name field with Document object
	/// \param required REQUIRED or OPTIONAL
	/// \return pointer to User
	std::unique_ptr<User> parseUser(const rapidjson::Value& parent, const char* name, bool required);

	/// \brief Parse JSON object to Message
	/// \param parent reference to parent JSON object
	/// \param name field with Message object
	/// \param required REQUIRED or OPTIONAL
	/// \return pointer to Message
	std::unique_ptr<Message> parseMessage(const rapidjson::Value& parent, const char* name, bool required);

	/// \brief Check JSON response
	///
	/// Throws an exception if error code recieved.
	/// \param doc reference to JSON document
	void checkResponse(const rapidjson::Document& doc);
}

#endif // TELEBOTXX_JSON_OBJECTS_HPP
