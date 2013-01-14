set(Mandrill_SOURCES ... )
file(GLOB Mandrill_SOURCES *.cpp)

add_library(Mandrill ${Mandrill_SOURCES})
target_link_libraries(Mandrill
  ${OpenGL_LIBRARY_DIRS}
  ${SDL_LIBRARY_DIRS}
  ${FreeImage_LIBRARY_DIRS})
