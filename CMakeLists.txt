cmake_minimum_required(VERSION 3.15)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} cmake)

if (NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

project(telebotxx CXX)

option(TELEBOTXX_USE_LIBCXX    "Use LLVM libc++ as C++ standard library" OFF)
option(TELEBOTXX_BUILD_TESTS   "Build unit tests using Boost.Test" OFF)
option(TELEBOTXX_GENERATE_DOC  "Generate API documentation with Doxygen" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (TELEBOTXX_USE_LIBCXX)
	if (UNIX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
		link_libraries(c++abi)
	endif()
	if(MSVC)
		# TODO
		message(WARNING "libc++ with MSVC is not yet supported")
	endif()
endif()

set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH     "${CMAKE_BINARY_DIR}/lib")

# Build dependencies
add_subdirectory(ext)

# Build library
add_subdirectory(src)

# Build tests
if(TELEBOTXX_BUILD_TESTS)
	add_subdirectory(tests)
endif()

# Generate docs
if(TELEBOTXX_GENERATE_DOC)
	add_subdirectory(doc)
endif()
