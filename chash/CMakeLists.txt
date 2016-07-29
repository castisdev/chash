cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME chash)
project(${PROJECT_NAME})
find_package(Boost)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
add_definitions(-D_AFXDLL -D_UNICODE -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS)
# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else(WIN32)
add_definitions(-Wall -g -Os -fPIC -fno-strict-aliasing -D_REENTRANT -D_GNU_SOURCE)
endif(WIN32)

set(SOURCE_FILES
	consistent_hash.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
