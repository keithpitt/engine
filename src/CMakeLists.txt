set(Mandrill_SOURCES ...)
file(GLOB_RECURSE Mandrill_SOURCES *.cpp)

set(Mandrill_HEADERS ...)
file(GLOB_RECURSE Mandrill_HEADERS "*.h")

# Libraries are static by default
add_library(Mandrill ${Mandrill_HEADERS} ${Mandrill_SOURCES})
