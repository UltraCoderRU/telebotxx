cmake_minimum_required(VERSION 2.8)

message(STATUS "Configuring telebotxx")

# Add required compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Put compiled library to 'lib' directory
set(LIBRARY_OUTPUT_PATH "../lib")

set(SOURCE_FILES Attachment.cpp
                 BotApi.cpp
                 Chat.cpp
                 JsonObjects.cpp
                 Logging.cpp
                 Message.cpp
                 Update.cpp
                 User.cpp
)

add_library(telebotxx SHARED ${SOURCE_FILES})
target_link_libraries(telebotxx ${CPR_LIBRARIES})

message(STATUS "Configuring telebotxx - done")
