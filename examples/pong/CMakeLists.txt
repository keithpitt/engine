cmake_minimum_required(VERSION 2.8.9)

project(Pong)

file(GLOB_RECURSE SRCS *.cpp *.h)

add_subdirectory(../../engine)

add_executable(Pong ${ENGINE_SRCS})
add_executable(Pong ${SRCS})
