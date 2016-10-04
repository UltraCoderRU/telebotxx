cmake_minimum_required(VERSION 2.8)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project(telebotxx CXX)

message(STATUS "Checking compiler flags for C++14 support.")
# Set C++14 support flags for various compilers
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
check_cxx_compiler_flag("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
if(COMPILER_SUPPORTS_CXX14)
  message(STATUS "C++14 is supported.")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  endif()
elseif(COMPILER_SUPPORTS_CXX1Y)
  message(STATUS "C++1y is supported.")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
  endif()
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

option (TELEBOTXX_BUILD_TESTS   "Build unit tests using Boost.Test" ON)
option (TELEBOTXX_GENERATE_DOC  "Generate API documentation with Doxygen" ON)

# Build and include Curl for People
set(BUILD_CPR_TESTS OFF CACHE BOOL "Do not build cpr tests")
set(USE_SYSTEM_CURL ON CACHE BOOL "Use system libcurl")
set(BUILD_SHARED_LIBS ON)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/cpr)
include_directories(${CPR_INCLUDE_DIRS})

# Include RapidJSON headers
include_directories(${PROJECT_SOURCE_DIR}/ext/rapidjson/include)

# Build library
include_directories(include)
add_subdirectory(src build)

# Build tests
if(TELEBOTXX_BUILD_TESTS)
  add_subdirectory(tests build-tests)
endif(TELEBOTXX_BUILD_TESTS)

# Generate docs
if(TELEBOTXX_GENERATE_DOC)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_custom_target(telebotxx-doc ALL COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile COMMENT "Generating API documentation with Doxygen")
    else(DOXYGEN_FOUND)
        message(STATUS "WARNING: Doxygen not found - Reference manual will not be created")
    endif(DOXYGEN_FOUND)
endif(TELEBOTXX_GENERATE_DOC)
