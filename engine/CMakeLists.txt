file(GLOB_RECURSE ENGINE_HEADERS src/*.hpp)
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers")

add_library(engine ${ENGINE_HEADERS} ${ENGINE_SOURCES})
