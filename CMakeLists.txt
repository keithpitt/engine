# I've only tested this on 2.8.9
cmake_minimum_required(VERSION 2.8.9)

# The application name
project(Mandrill)

# Find and add the OpenGL libraries to it
find_package(OpenGL REQUIRED)
set(SYSTEM_LIBS ${SYSTEM_LIBS} ${OPENGL_LIBRARIES})

# Include out external dependencies
if(APPLE)
  # Set the bundle path
  set(BUNDLE_PATH "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app")
  set(BUNDLE_FRAMEWORK_PATH "${BUNDLE_PATH}/Contents/Frameworks")

  # Framework files to be included
  file(GLOB EXT_OPTIMIZED_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-osx/*.dylib")

  # On OS X we also have to add '-framework Cocoa' and IOKit as library.  This is
  # actually a bit of an hack but it's easy enough and reliable.
  set(SYSTEM_LIBS ${SYSTEM_LIBS} "-framework Cocoa -framework IOKit")
endif()

if(WIN32)
  # Define the output directory
  set(VS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
  set(EXT_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-msvc")

  # Optimized dependencies for linking and shipping
  file(GLOB EXT_OPTIMIZED_LIBS "${EXT_LIB_PATH}/release/*.lib")
  file(GLOB EXT_OPTIMIZED_DLLS "${EXT_LIB_PATH}/release/*.dll")

  # Debugging dependencies for linking and shipping
  file(GLOB EXT_DEBUG_LIBS "${EXT_LIB_PATH}/debug/*.lib")
  file(GLOB EXT_DEBUG_DLLS "${EXT_LIB_PATH}/debug/*.dll")
endif()

# Include our extlibs headers.
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers")

# A list of header and source files used by your application.
file(GLOB_RECURSE SOURCES "src4/*.cpp")
file(GLOB_RECURSE HEADERS "src4/*.hpp")

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
  ${EXT_OPTIMIZED_LIBS} # This is here so we can set source_file_properties on it for Xcode
)

# Link the system libraries to the target
target_link_libraries(${PROJECT_NAME} ${SYSTEM_LIBS})

# We'll always have a release lib, but not always a debug one. So if we have a debug one,
# link the optimized and the debug versions. If we don't have it, just the release one.
if(DEFINED EXT_DEBUG_LIBS)
  SET(LINK_LIBRARY optimized ${EXT_OPTIMIZED_LIBS} debug ${EXT_DEBUG_LIBS})
elseif(DEFINED EXT_OPTIMIZED_LIBS)
  SET(LINK_LIBRARY ${EXT_OPTIMIZED_LIBS})
endif()

target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARY})

if(APPLE)
  # There is a bug in cmake. ${CMAKE_COMMAND} -E copy breaks when you try to copy a folder.
  # It ends up just copying the folder, and none of the contents. As a result, we have 2
  # different ways of adding frameworks to the project :( That means I can't use a cross xcode/unix
  # method of copying the frameworks across.

  # Copying frameworks like this works like a charm in Xcode
  if(XCODE)
    foreach(LIB ${EXT_OPTIMIZED_LIBS})
      set_source_files_properties(${LIB} PROPERTIES MACOSX_PACKAGE_LOCATION Frameworks)
    endforeach()
  else()
    # Make the framework folder (if it doesn't exist already)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND mkdir -p ${BUNDLE_FRAMEWORK_PATH})

    # Go over all the external libraries and include them in our application
    foreach(LIB ${EXT_OPTIMIZED_LIBS})
      # Copy it to the bundle
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND cp -r ${LIB} ${BUNDLE_FRAMEWORK_PATH})
    endforeach()
  endif()
endif()

if(WIN32)
  # Ship the DLL's with the package. I know we're not doing release/debug testing.
  # But I have no idea how to do it...
  foreach(DLL ${EXT_OPTIMIZED_DLLS})
    get_filename_component(DLL_NAME ${DLL} NAME EXT)

    # Copy the dll over.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:${PROJECT_NAME}>/${DLL_NAME})
  endforeach()
endif()
