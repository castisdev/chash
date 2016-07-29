cmake_minimum_required(VERSION 3.0)
project(chash)

find_package(Boost REQUIRED)
include_directories(
  ${Boost_INCLUDE_DIRS}
  chash
)

if(WIN32)
else(WIN32)
ADD_DEFINITIONS(-Wno-deprecated-declarations -Wno-unused-variable)
endif(WIN32)

add_subdirectory(chash)
add_subdirectory(example)
