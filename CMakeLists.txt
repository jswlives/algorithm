cmake_minimum_required(VERSION 3.4)
project(LIBEVENT_LEARN)

set( CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_C_COMPILER_ARG1 "")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_COMPILER_ARG1 "")



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#############################################################
include_directories(${CMAKE_SOURCE_DIR}/ext/libevent/include)
#############################################################
link_directories(${CMAKE_SOURCE_DIR}/ext/libevent/lib)


###################################
link_libraries(event)

####################################
add_subdirectory(src)
add_subdirectory(client)
