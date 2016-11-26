cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} cmake)

if (NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Type of build (Release, Debug, RelWithDebInfo, MinSizeRel)")
endif()

project(telebotxx CXX)

option (TELEBOTXX_BUILD_TESTS   "Build unit tests using Boost.Test" ON)
option (TELEBOTXX_GENERATE_DOC  "Generate API documentation with Doxygen" ON)

set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

# Build and include Curl for People
set(BUILD_CPR_TESTS OFF CACHE BOOL "Do not build cpr tests")
find_package(CURL)
if(CURL_FOUND)
  set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/ext/cpr)
include_directories(${CPR_INCLUDE_DIRS})

# Include RapidJSON headers
include_directories(${PROJECT_SOURCE_DIR}/ext/rapidjson/include)

# Build library
include_directories(include)
add_subdirectory(src)

# Build tests
if(TELEBOTXX_BUILD_TESTS)
  add_subdirectory(tests)
endif(TELEBOTXX_BUILD_TESTS)

# Generate docs
if(TELEBOTXX_GENERATE_DOC)
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in Doxyfile)
    # Bootstrap theme for Doxygen
    file(COPY ${PROJECT_SOURCE_DIR}/doc/bootstrap.min.js
              ${PROJECT_SOURCE_DIR}/doc/bootstrap.min.css
              ${PROJECT_SOURCE_DIR}/doc/doxy-boot.js
              DESTINATION doc/html)
    add_custom_target(telebotxx-doc ALL COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile COMMENT "Generating API documentation with Doxygen")
  else(DOXYGEN_FOUND)
    message(STATUS "WARNING: Doxygen not found - Reference manual will not be created")
  endif(DOXYGEN_FOUND)
endif(TELEBOTXX_GENERATE_DOC)
