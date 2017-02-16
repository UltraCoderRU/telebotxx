#ifndef TELEBOTXX_UPDATE_HPP
#define TELEBOTXX_UPDATE_HPP

#include "Message.hpp"

#include <vector>
#include <memory>

namespace telebotxx {

class Update
{
public:
	enum class Type
	{
		Message,
		InlineQuery,
		ChosenInlineResult,
		CallbackQuery
	};

	Update(int id, Type type);
	Update(const Update&);
	Update(Update&&);
	virtual ~Update() = 0;

	int getId() const;
	Type getType() const;

	void swap(Update& other) noexcept;

private:
	int id_;
	Type updateType_;
};

using UpdatePtr = std::shared_ptr<Update>;
using Updates = std::vector<UpdatePtr>;

class MessageUpdate : public Update
{
public:
	enum class MessageType
	{
		Message,
		EditedMessage,
		ChannelPost,
		EditedChannelPost
	};

	MessageUpdate(int id, MessageType type, const Message& message);
	MessageUpdate(const MessageUpdate&);
	MessageUpdate(MessageUpdate&&);
	~MessageUpdate();

	MessageType getMessageType() const;
	const Message& getMessage() const;

	void swap(MessageUpdate& other) noexcept;
	const MessageUpdate& operator=(MessageUpdate other);

private:
	MessageType type_;
	Message message_;
};

}

#endif // TELEBOTXX_UPDATE_HPP
