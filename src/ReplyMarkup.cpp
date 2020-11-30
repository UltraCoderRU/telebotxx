#include "ReplyMarkup.hpp"

namespace telebotxx {

void writeInlineKeyboardButton(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                               const InlineKeyboardButton& button)
{
	writer.StartObject();

	writer.String("text");
	writer.String(button.getText().c_str());

	switch (button.getActionType())
	{
	case InlineKeyboardButton::ActionType::Url:
	{
		writer.String("url");
		writer.String(button.getUrl().getValue().c_str());
		break;
	}
	case InlineKeyboardButton::ActionType::CallbackData:
	{
		writer.String("callback_data");
		writer.String(button.getCallbackData().getValue().c_str());
		break;
	}
	case InlineKeyboardButton::ActionType::SwitchInlineQuery:
	{
		writer.String("switch_inline_query");
		writer.String(button.getSwitchInlineQuery().getValue().c_str());
		break;
	}
	case InlineKeyboardButton::ActionType::SwitchInlineQueryCurrentChat:
	{
		writer.String("switch_inline_query_current_chat");
		writer.String(button.getSwitchInlineQueryCurrentChat().getValue().c_str());
		break;
	}
	}

	writer.EndObject();
}

void writeInlineKeyboardMarkup(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                               const InlineKeyboardMarkup& markup)
{
	writer.StartObject();
	writer.String("inline_keyboard");
	writer.StartArray();
	auto rows = markup.getRows();
	for (auto& row : rows)
	{
		writer.StartArray();
		for (auto& button : row)
			writeInlineKeyboardButton(writer, button);
		writer.EndArray();
	}
	writer.EndArray();
	writer.EndObject();
}

void writeReplyMarkup(rapidjson::Writer<rapidjson::StringBuffer>& writer, const ReplyMarkup& markup)
{
	if (markup.getType() == ReplyMarkup::Type::InlineKeyboardMarkup)
		writeInlineKeyboardMarkup(writer, markup.getInlineKeyboardMarkup());
}

} // namespace telebotxx
