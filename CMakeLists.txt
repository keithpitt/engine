# I've only tested this on 2.8.9
cmake_minimum_required(VERSION 2.8.9)

# The application name
project(Mandrill)

# A list of header and source files used by your application.
set(SOURCES ...)
file(GLOB_RECURSE SOURCES "src2/*.cpp")

set(HEADERS ...)
file(GLOB_RECURSE HEADERS "src2/*.hpp")

# Define what SFML components we want
set(SFML_COMPONENTS system window graphics network audio)
foreach(COMPONENT ${SFML_COMPONENTS})
  set(SFML_LIBRARIES ${SFML_LIBRARIES} "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-osx/sfml-${COMPONENT}.framework")
endforeach()

# we also need to find the system's OpenGL version
find_package(OpenGL REQUIRED)

# on OS X we also have to add '-framework Cocoa' as library.  This is
# actually a bit of an hack but it's easy enough and reliable.
set(EXTRA_LIBS "")
if (APPLE)
set(EXTRA_LIBS ${EXTRA_LIBS} "-framework Cocoa -framework IOKit")
endif()

# our own include folder and the SDL one are additional folders we
# want to have on our path.
include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers"
)

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
)

# Lastly we have to link the OpenGL libraries, SDL and the cocoa
# framework to our application.  The latter is only happening on
# OS X obviously.
target_link_libraries(
  ${PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  ${SFML_LIBRARIES}
  ${EXTRA_LIBS}
)

if(APPLE)
  # Set the bundle path
  set(BUNDLE_PATH "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/")
  set(BUNDLE_FRAMEWORK_PATH "${BUNDLE_PATH}/Contents/Frameworks")

  # Make the framework folder (if it doesn't exist already)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND test -d ${BUNDLE_FRAMEWORK_PATH} || mkdir -p ${BUNDLE_FRAMEWORK_PATH})

  # Go over all the SFML_COMPONENTS and add them to the final bundle
  foreach(SFML_FRAMEWORK ${SFML_LIBRARIES})
    # Copy it to the bundle
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND cp -r ${SFML_FRAMEWORK} ${BUNDLE_FRAMEWORK_PATH})
  endforeach()
endif()

if(WIN32)
    set(VS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL_FOLDER}/VisualC/SDL/Release/SDL2.dll ${VS_OUTPUT_DIR}/SDL2.dll)
endif()
