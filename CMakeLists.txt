# Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8.9)

# Name of the project
project(demo)

# Standard C++
SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++") 

# Include other .cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find and require packages
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(FreeImage REQUIRED)

# Include the CMakeLists file in lib
add_subdirectory(lib)

# Define out executable
add_executable(demo main.cpp)

# Link our libraries to the executable
target_link_libraries(demo
  ${OPENGL_LIBRARIES}
  ${SDL_LIBRARY}
  SDLmain # Sadly not included in SDL_LIBRARY variable
  ${FREEIMAGE_LIBRARY}
  Mandrill)
