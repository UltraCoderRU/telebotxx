cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project(tetebotxx CXX)

option (TELEBOTXX_BUILD_TESTS   "Build unit tests using Boost.Test" ON)
option (TELEBOTXX_GENERATE_DOC  "Generate API documentation with Doxygen" ON)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ext)
INCLUDE_DIRECTORIES(/usr/local/include)

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
