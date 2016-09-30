cmake_minimum_required(VERSION 2.8)

message(STATUS "Configuring telebotxx")

find_package(Boost 1.54 REQUIRED log system)
include_directories(${Boost_INCLUDE_DIRS})

#find_package(CURLpp REQUIRED)
#include_directories(${CURLPP_INCLUDE_DIRS})

# Add required gcc flags
# For Windows we suppress all warnings because of Boost garbage :(
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
else(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif(NOT WIN32)

# Put compiled library to 'lib' directory
set(LIBRARY_OUTPUT_PATH "../lib")


set(SOURCE_FILES BotApi.cpp
                 User.cpp
)

add_library(telebotxx SHARED ${SOURCE_FILES})
target_link_libraries(telebotxx ${Boost_LIBRARIES} ${CPR_LIBRARIES})
set_property(TARGET telebotxx APPEND PROPERTY COMPILE_DEFINITIONS BOOST_LOG_DYN_LINK)
