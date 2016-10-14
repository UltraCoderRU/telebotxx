cmake_minimum_required(VERSION 2.8)

message(STATUS "Configuring telebotxx")

# Add required gcc flags
# For Windows we suppress all warnings because of Boost garbage :(
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
else(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif(NOT WIN32)

# Put compiled library to 'lib' directory
set(LIBRARY_OUTPUT_PATH "../lib")

set(SOURCE_FILES Attachment.cpp
                 BotApi.cpp
                 Chat.cpp
                 Logging.cpp
                 User.cpp
)

add_library(telebotxx SHARED ${SOURCE_FILES})
target_link_libraries(telebotxx ${CPR_LIBRARIES})

message(STATUS "Configuring telebotxx - done")
