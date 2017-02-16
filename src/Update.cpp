#include <telebotxx/Update.hpp>

namespace telebotxx {

Update::Update(int id, Type type)
	: id_(id),
	  updateType_(type)
{
}

Update::Update(const Update&) = default;
Update::Update(Update&&) = default;
Update::~Update() = default;

int Update::getId() const
{
	return id_;
}

Update::Type Update::getType() const
{
	return updateType_;
}

void Update::swap(Update& other) noexcept
{
	using std::swap;
	swap(id_, other.id_);
	swap(updateType_, other.updateType_);
}

////////////////////////////////////////////////////////////////

MessageUpdate::MessageUpdate(int id, MessageType type, const Message& message)
	: Update(id, Type::Message), type_(type), message_(message)
{
}

MessageUpdate::MessageUpdate(const MessageUpdate&) = default;
MessageUpdate::MessageUpdate(MessageUpdate&&) = default;
MessageUpdate::~MessageUpdate() = default;

MessageUpdate::MessageType MessageUpdate::getMessageType() const
{
	return type_;
}

const Message& MessageUpdate::getMessage() const
{
	return message_;
}

void MessageUpdate::swap(MessageUpdate& other) noexcept
{
	using std::swap;
	Update::swap(other);
	swap(message_, other.message_);
}

const MessageUpdate& MessageUpdate::operator=(MessageUpdate other)
{
	swap(other);
	return *this;
}

}
