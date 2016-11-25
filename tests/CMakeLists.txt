cmake_minimum_required(VERSION 2.8)
if (POLICY CMP0037)
  cmake_policy(SET CMP0037 OLD)
endif()

message(STATUS "Configuring telebotxx-test")

add_definitions(-DBOOST_TEST_DYN_LINK)
find_package(Boost REQUIRED COMPONENTS unit_test_framework system)
include_directories(${Boost_INCLUDE_DIRS})

# Add required compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES Dummy.cpp TestTypes.cpp TestApi.cpp)
add_executable(telebotxx-test ${SOURCE_FILES})
target_link_libraries(telebotxx-test telebotxx stdc++ ${Boost_LIBRARIES})

add_custom_target(test COMMAND telebotxx-test WORKING_DIRECTORY ".." DEPENDS telebotxx-test)

message(STATUS "Configuring telebotxx-test - done")
