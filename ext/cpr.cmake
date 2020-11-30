# Build Curl for People
set(BUILD_CPR_TESTS OFF CACHE BOOL "Do not build cpr tests")
find_package(CURL)
if(CURL_FOUND)
	set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()

add_subdirectory(cpr)
