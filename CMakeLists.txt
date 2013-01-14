# Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8.9)

# Name of the project
project(demo)

SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++") 

# Include other .cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Require OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

# Require SDL
find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})

# Require FreeImage
find_package(FreeImage REQUIRED)
include_directories(${FreeImage_INCLUDE_DIRS})

add_subdirectory(lib)

add_executable(demo main.cpp)
target_link_libraries(demo
  ${OpenGL_LIBRARY_DIRS}
  ${SDL_LIBRARY_DIRS}
  ${FreeImage_LIBRARY_DIRS}
  Mandrill)
