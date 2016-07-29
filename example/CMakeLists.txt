cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME chash_example)
project(${PROJECT_NAME})
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-Wall -D_REENTRANT -D_GNU_SOURCE -D_UNICODE -g -Os)

set(SOURCE_FILES
	example.cpp
)

set(LIBS
	pthread
	rt
)

add_executable(chash_example ${SOURCE_FILES})

if(KERNELTYPE EQUAL 32)
  add_definitions(-m32)
  message(STATUS "Set `-m32` flags.")
else(KERNELTYPE EQUAL 32)
endif()


target_link_libraries(
	chash_example
	
	${LIBS}
	${Boost_LIBRARIES}
	uuid
	chash
)
