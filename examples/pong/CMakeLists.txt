cmake_minimum_required(VERSION 2.8.9)

project(Pong)

file(GLOB SRCS *.cpp)
add_executable(Pong ${SRCS})

add_subdirectory(engine)
target_link_libraries(Pong engine)
