#include "TestGlobal.hpp"

#include <telebotxx/User.hpp>

using namespace telebotxx;

BOOST_AUTO_TEST_SUITE(TestUser)

	BOOST_AUTO_TEST_CASE(DefaultConstructor)
	{
		PRINT_TESTNAME;
		BOOST_REQUIRE_NO_THROW(User user);
	}

	BOOST_AUTO_TEST_CASE(CopyConstructor)
	{
		PRINT_TESTNAME;
		User other;
		other.setId(1);
		other.setFirstName(std::string("John"));
		other.setLastName(std::string("Smith"));
		other.setUsername(std::string("john_smith"));
		std::unique_ptr<User> user;
		BOOST_REQUIRE_NO_THROW(user.reset(new User(other)));
		BOOST_REQUIRE_EQUAL(user->getId(), 1);
		BOOST_REQUIRE_EQUAL(user->getFirstName(), "John");
		BOOST_REQUIRE_EQUAL(*user->getLastName(), "Smith");
		BOOST_REQUIRE_EQUAL(*user->getUsername(), "john_smith");
	}

	BOOST_AUTO_TEST_CASE(MoveConstructor)
	{
		PRINT_TESTNAME;
		User other;
		other.setId(1);
		other.setFirstName(std::string("John"));
		other.setLastName(std::string("Smith"));
		other.setUsername(std::string("john_smith"));
		std::unique_ptr<User> user;
		BOOST_REQUIRE_NO_THROW(user.reset(new User(std::move(other))));
		BOOST_REQUIRE_EQUAL(user->getId(), 1);
		BOOST_REQUIRE_EQUAL(user->getFirstName(), "John");
		BOOST_REQUIRE_EQUAL(*user->getLastName(), "Smith");
		BOOST_REQUIRE_EQUAL(*user->getUsername(), "john_smith");
	}

BOOST_AUTO_TEST_SUITE_END()
