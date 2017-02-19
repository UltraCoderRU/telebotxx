#ifndef TELEBOTXX_EXCEPTION_HPP
#define TELEBOTXX_EXCEPTION_HPP

#include <stdexcept>

namespace telebotxx {

class ParseError : public std::invalid_argument
{
public:
	ParseError(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};

class ApiError : public std::runtime_error
{
public:
	ApiError(int code, std::string message)
		: std::runtime_error(std::move(message)), code_(code)
	{
	}

	int getCode() const
	{
		return code_;
	}

protected:
	int code_;
};

}

#endif // TELEBOTXX_EXCEPTION_HPP
