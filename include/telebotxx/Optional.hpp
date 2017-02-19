#ifndef TELEBOTXX_OPTIONAL_HPP
#define TELEBOTXX_OPTIONAL_HPP

#include <boost/optional.hpp>

namespace telebotxx {

template <typename T>
using optional = boost::optional<T>;

const auto none = boost::none;

}

#endif // TELEBOTXX_OPTIONAL_HPP
