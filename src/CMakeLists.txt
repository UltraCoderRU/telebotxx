cmake_minimum_required(VERSION 2.8)

message(STATUS "Configuring telebotxx")

include(${CMAKE_SOURCE_DIR}/cmake/RequireCXX14.cmake)
RequireCXX14()

find_package(Boost 1.56 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Add required compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES Attachment.cpp
                 BotApi.cpp
                 Chat.cpp
                 JsonObjects.cpp
                 Logging.cpp
                 Message.cpp
                 Update.cpp
                 User.cpp
                 RequestOptions.cpp
                 SendMessageRequest.cpp
                 SendPhotoRequest.cpp
)

add_library(telebotxx ${SOURCE_FILES})
target_link_libraries(telebotxx ${CPR_LIBRARIES})

message(STATUS "Configuring telebotxx - done")
