cmake_minimum_required(VERSION 3.4)
project(LIBEVENT_LEARN)

set( CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_C_COMPILER_ARG1 "")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_COMPILER_ARG1 "")

set(CMAKE_COMM_FLAGS "-rdynamic -std=c++11 -g3 -ggdb3 -Wall -Wfatal-errors -Wextra -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_COMM_FLAGS}")


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#############################################################
include_directories(${CMAKE_SOURCE_DIR}/ext/libevent/include)
#############################################################
link_directories(${CMAKE_SOURCE_DIR}/ext/libevent/lib)


###################################


####################################
add_subdirectory(libevent/src)
add_subdirectory(libevent/client)
add_subdirectory(alth)
add_subdirectory(linux)
