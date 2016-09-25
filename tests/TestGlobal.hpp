#ifndef TELEBOTXX_TEST_GLOBAL_HPP
#define TELEBOTXX_TEST_GLOBAL_HPP

#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace boost::unit_test;

#define BOOST_TEST_SUITE_NAME (boost::unit_test::framework::get<boost::unit_test::test_suite>(boost::unit_test::framework::current_test_case().p_parent_id).p_name)
#define BOOST_TEST_NAME (boost::unit_test::framework::current_test_case().p_name)
#define PRINT_TESTNAME std::cout << "\x1B[36mRunning unit test " << BOOST_TEST_SUITE_NAME << "::" << BOOST_TEST_NAME << "...\x1B[0m" << std::endl;

#endif // TELEBOTXX_TEST_GLOBAL_HPP
