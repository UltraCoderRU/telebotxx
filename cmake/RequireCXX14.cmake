cmake_minimum_required(VERSION 2.8)

function(RequireCXX14)
  message(STATUS "Checking compiler flags for C++14 support.")
  # Set C++14 support flags for various compilers
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
  check_cxx_compiler_flag("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
  if(COMPILER_SUPPORTS_CXX14)
    message(STATUS "C++14 is supported.")
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++" PARENT_SCOPE)
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" PARENT_SCOPE)
    endif()
  elseif(COMPILER_SUPPORTS_CXX1Y)
    message(STATUS "C++1y is supported.")
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++" PARENT_SCOPE)
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y" PARENT_SCOPE)
    endif()
  else()
    message(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
  endif()
endfunction()