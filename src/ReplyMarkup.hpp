#ifndef TELEBOTXX_REPLY_MARKUP_HPP
#define TELEBOTXX_REPLY_MARKUP_HPP

#include <telebotxx/RequestOptions.hpp>

#include <rapidjson/writer.h>

namespace telebotxx {

void writeReplyMarkup(rapidjson::Writer<rapidjson::StringBuffer>& writer, const ReplyMarkup& markup);

}

#endif // TELEBOTXX_REPLY_MARKUP_HPP
