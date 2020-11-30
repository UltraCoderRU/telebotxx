#include "Update.hpp"

namespace telebotxx {

Update::Update(int id, Type type, std::unique_ptr<Message> message)
    : id_(id), type_(type), value_(std::move(message))
{
}

int Update::getId() const
{
	return id_;
}

Update::Type Update::getType() const
{
	return type_;
}

MessagePtr Update::getMessage() const
{
	return std::get<MessagePtr>(value_);
}

} // namespace telebotxx
