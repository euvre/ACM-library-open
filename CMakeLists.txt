cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

project(ACM
    VERSION 2023.12
    DESCRIPTION "The algorithm librarys for ACM."
    LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("The compiler is ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}.")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "19.40.33521.0")
        message(FATAL_ERROR "MSVC version must be greater than or equal to 19.40.33521.0")
    endif()
else()
    message(FATAL_ERROR "Only MSVC compiler is supported.")
endif()

# Uncomment the following lines to enable Debug mode.
set(CMAKE_BUILD_TYPE "Debug")

set(HOST_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
string(TOLOWER "${HOST_ARCH}" HOST_ARCH)

if(NOT (HOST_ARCH MATCHES "x86_64" OR HOST_ARCH MATCHES "amd64"))
    message(FATAL_ERROR "Only support x86_64 or amd64 arch.")
else()
    message("This library is running on ${HOST_ARCH} arch.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party)

enable_testing()
