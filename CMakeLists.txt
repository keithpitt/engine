# Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8.9)

# Name of the project
project(demo)

set(TARGET demo)

# Used to define custom compile options
set(EXTRA_LIBS "")

IF(APPLE)
  set(VENDOR_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vendor/osx")
ENDIF()

# Include our vendor directory in the search paths.
# set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${VENDOR_DIRECTORY})
# set(CMAKE_INCLUDE_PATH ${CMAKE_LIBRARY_PATH} ${VENDOR_DIRECTORY})
# include_directories(${VENDOR_DIRECTORY})

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
add_executable(
  ${TARGET}
  WIN32
  MACOSX_BUNDLE
  SDLMain.m
  SDLMain.h
  main.cpp
)

# Link our libraries to the executable
target_link_libraries(
  ${TARGET}
  ${OPENGL_LIBRARIES}
  ${SDL_LIBRARY}
  ${FREEIMAGE_LIBRARY}
  Mandrill
)

IF(APPLE)
  set(BUNDLE_BINARY ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.app/Contents/MacOS/${TARGET})

  add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND "python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/frameworkify.py ${BUNDLE_BINARY} ${SDL_LIBRARY}")
ENDIF()
