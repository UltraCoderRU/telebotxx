#ifndef TELEBOTXX_JSON_OBJECTS_HPP
#define TELEBOTXX_JSON_OBJECTS_HPP

#include <telebotxx/Attachment.hpp>
#include <telebotxx/Message.hpp>
#include <telebotxx/Update.hpp>
#include <telebotxx/User.hpp>
#include <telebotxx/Exception.hpp>

#include <rapidjson/document.h>

#include <memory>
#include <optional>

namespace telebotxx {

const bool REQUIRED = true;
const bool OPTIONAL = false;

namespace impl {

template<typename T> bool is(const rapidjson::Value& obj);
template<> bool is<int>(const rapidjson::Value& obj);
template<> bool is<std::int64_t>(const rapidjson::Value& obj);
template<> bool is<bool>(const rapidjson::Value& obj);
template<> bool is<std::string>(const rapidjson::Value& obj);

template<typename T> const T get(const rapidjson::Value& obj);
template<> const int get(const rapidjson::Value& obj);
template<> const std::int64_t get(const rapidjson::Value& obj);
template<> const bool get(const rapidjson::Value& obj);
template<> const std::string get(const rapidjson::Value& obj);

}

template<typename T>
std::optional<T> parse(const rapidjson::Value& obj, const char* name, bool required)
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
		return std::nullopt;
}

template <typename T>
T require(const rapidjson::Value& obj, const char* name)
{
	return *parse<T>(obj, name, REQUIRED);
}

template <typename T>
std::optional<T> allow(const rapidjson::Value& obj, const char* name)
{
	return parse<T>(obj, name, OPTIONAL);
}

bool check(const rapidjson::Value& obj, const char* name);

/// \brief Parse JSON object to User
/// \param parent reference to parent JSON object
/// \param name field with Document object
/// \param required REQUIRED or OPTIONAL
/// \return pointer to User
template<> std::optional<User> parse<User>(const rapidjson::Value& parent, const char* name, bool required);

/// \brief Parse JSON object to Message
/// \param parent reference to parent JSON object
/// \param name field with Message object
/// \param required REQUIRED or OPTIONAL
/// \return pointer to Message
std::unique_ptr<Message> parseMessage(const rapidjson::Value& parent, const char* name, bool required);

/// \brief Parse JSON array of Update
/// \param parent reference to parent JSON object
/// \param name field with array of Update objects
/// \return Updates (vector of UpdatePtr>
Updates parseUpdates(const rapidjson::Value& parent, const char* name);

/// \brief Check JSON response
///
/// Throws an exception if error code recieved.
/// \param doc reference to JSON document
void checkResponse(const rapidjson::Document& doc);

}

#endif // TELEBOTXX_JSON_OBJECTS_HPP
