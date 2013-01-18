# I've only tested this on 2.8.9
cmake_minimum_required(VERSION 2.8.9)

# The application name
project(Mandrill)

# Include out external dependencies
set(EXT_LIBS ...)
set(SYSTEM_LIBS "")

if(APPLE)
  file(GLOB EXT_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-osx/Frameworks/*.framework")

  # On OS X we also have to add '-framework Cocoa' and IOKit as library.  This is
  # actually a bit of an hack but it's easy enough and reliable.
  set(SYSTEM_LIBS ${SYSTEM_LIBS} "-framework Cocoa -framework IOKit")
endif()

# We also need to find the system's OpenGL version
find_package(OpenGL REQUIRED)

# Include our extlibs headers.
include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers"
)

# A list of header and source files used by your application.
file(GLOB_RECURSE SOURCES "src2/*.cpp")
file(GLOB_RECURSE HEADERS "src2/*.hpp")

# Now we define what makes our executable.  First thing is the name,
# WIN32 is needed to make this a Win32 GUI application, MACOSX_BUNDLE
# activates bundle mode on OS X and the last two things are our source
# and header files this executable consists of.
add_executable(
  ${PROJECT_NAME}
  WIN32
  MACOSX_BUNDLE
  ${SOURCES}
  ${HEADERS}
  ${EXT_LIBS}
)

# Lastly we have to link the OpenGL libraries, SDL and the cocoa
# framework to our application.  The latter is only happening on
# OS X obviously.
target_link_libraries(
  ${PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  ${EXT_LIBS}
  ${SYSTEM_LIBS}
)

if(APPLE)
  # There is a bug in cmake. ${CMAKE_COMMAND} -E copy breaks when you try to copy a folder.
  # It ends up just copying the folder, and none of the contents. As a result, we have 2
  # different ways of adding frameworks to the project :( That means I can't use a cross xcode/unix
  # method of copying the frameworks across.

  # Copying frameworks like this works like a charm in Xcode
  if(XCODE)
    set_source_files_properties(${EXT_LIBS} PROPERTIES MACOSX_PACKAGE_LOCATION Frameworks)
  endif()

  # Manually copy over the frameworks when using a makefile
  if(UNIX)
    # Set the bundle path
    set(BUNDLE_PATH "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app")
    set(BUNDLE_FRAMEWORK_PATH "${BUNDLE_PATH}/Contents/Frameworks")

    # Make the framework folder (if it doesn't exist already)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND mkdir -p ${BUNDLE_FRAMEWORK_PATH})

    # Go over all the external libraries and include them in our application
    foreach(LIB ${EXT_LIBS})
      # Copy it to the bundle
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND cp -r ${LIB} ${BUNDLE_FRAMEWORK_PATH})
    endforeach()
  endif()
endif()

if(WIN32)
    # Go over all the external libraries and include them in our application
    foreach(LIB ${EXT_LIBS})
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIB} ${VS_OUTPUT_DIR})
    endforeach()
endif()
