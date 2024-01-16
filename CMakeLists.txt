cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED on)

project(ACM
		VERSION 2023.12	
		DESCRIPTION "The algorithm librarys for ACM."
		LANGUAGES CXX
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message("The compiler is ${CMAKE_CXX_COMPILER_ID}.")
else()
	message(FATAL_ERROR "You are using ${CMAKE_CXX_COMPILER_ID}, which is/may not support C++20 modules and other morden features.")
endif()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party)
