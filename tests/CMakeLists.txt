message(STATUS "Configuring telebotxx-test")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES TestApi.cpp)
add_executable(telebotxx-test ${SOURCE_FILES})
target_link_libraries(telebotxx-test
	telebotxx
	Catch2::Catch2WithMain
	rapidjson
)

add_custom_target(test COMMAND $<TARGET_FILE:telebotxx-test>
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DEPENDS telebotxx-test
)

message(STATUS "Configuring telebotxx-test - done")
