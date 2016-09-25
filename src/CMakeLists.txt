cmake_minimum_required(VERSION 2.8)

message(STATUS "Configuring telebotxx")

find_package(CURLpp REQUIRED)
include_directories(${CURLPP_INCLUDE_DIRS})

# Add required gcc flags
# For Windows we suppress all warnings because of Boost garbage :(
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
else(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -w")
endif(NOT WIN32)

# Put compiled library to 'lib' directory
set(LIBRARY_OUTPUT_PATH "../lib")


set(SOURCE_FILES BotApi.cpp
)

add_library(telebotxx SHARED ${SOURCE_FILES})
target_link_libraries(telebotxx curlpp ${CURL_LIBRARIES})
