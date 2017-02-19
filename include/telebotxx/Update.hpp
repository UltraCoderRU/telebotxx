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
		EditedMessage,
		ChannelPost,
		EditedChannelPost,
		InlineQuery,
		ChosenInlineResult,
		CallbackQuery
	};

	Update(int id, Type type, std::unique_ptr<Message>);

	int getId() const;
	Type getType() const;
	MessagePtr getMessage() const;

private:
	int id_;
	Type type_;
	boost::variant<MessagePtr> value_;
};

using Updates = std::vector<Update>;

}

#endif // TELEBOTXX_UPDATE_HPP
