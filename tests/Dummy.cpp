#define BOOST_TEST_MODULE AllTests
#include "TestGlobal.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_CASE(Dummy)
{
	PRINT_TESTNAME;
	BOOST_REQUIRE(1 == 1);
	BOOST_REQUIRE_THROW(throw 1, int);
}
