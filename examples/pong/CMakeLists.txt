cmake_minimum_required(VERSION 2.8.9)

project(Pong)

# Add the pong source code to the project
file(GLOB SRCS *.cpp)
add_executable(${PROJECT_NAME} ${SRCS})

# Add the engine subdirectory (which has its own CMakeLists.txt)
add_subdirectory(engine)

# Link the engine to Pong
target_link_libraries(${PROJECT_NAME} engine)
