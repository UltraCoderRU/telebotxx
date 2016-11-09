#ifndef TELEBOTXX_UPDATE_HPP
#define TELEBOTXX_UPDATE_HPP

#include "Message.hpp"

#include <vector>
#include <memory>

namespace telebotxx
{
	class Update
	{
	public:
		enum class Type
		{
			Message,
			EditedMessage,
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
		MessageUpdate(int id, const Message& message);
		MessageUpdate(const MessageUpdate&);
		MessageUpdate(MessageUpdate&&);
		~MessageUpdate();

		const Message& getMessage() const;

		void swap(MessageUpdate& other) noexcept;

		const MessageUpdate& operator=(MessageUpdate other);

	private:
		Message message_;
	};

	class EditedMessageUpdate: public MessageUpdate
	{
	public:
		EditedMessageUpdate(int id, const Message& message);
		EditedMessageUpdate(const EditedMessageUpdate&);
		EditedMessageUpdate(EditedMessageUpdate&&);
		~EditedMessageUpdate();

		void swap(EditedMessageUpdate& other) noexcept;

		const EditedMessageUpdate& operator=(EditedMessageUpdate other);
	};

}

#endif // TELEBOTXX_UPDATE_HPP
