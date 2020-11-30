message(STATUS "Configuring telebotxx")

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
                 ReplyMarkup.cpp
                 RequestOptions.cpp
                 SendMessageRequest.cpp
                 SendPhotoRequest.cpp
)

add_library(telebotxx ${SOURCE_FILES})
target_include_directories(telebotxx PUBLIC ${telebotxx_SOURCE_DIR}/include)
target_include_directories(telebotxx PRIVATE ${telebotxx_SOURCE_DIR}/include/telebotxx)
target_link_libraries(telebotxx
PRIVATE
	${CPR_LIBRARIES}
	rapidjson
)

message(STATUS "Configuring telebotxx - done")
