# Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8.9)

# Name of the project
project(demo)

# Include other .cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find and require packages
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_PATH})

# Include the CMakeLists file in lib
add_subdirectory(lib)

# Define out executable
add_executable(demo SDLMain.m SDLMain.h main.cpp)

# Link our libraries to the executable
target_link_libraries(demo
  ${OPENGL_LIBRARIES}
  ${SDL_LIBRARY}
  ${FREEIMAGE_LIBRARY}
  Mandrill)
