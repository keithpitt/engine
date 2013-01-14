set(Mandrill_SOURCES ... )
file(GLOB Mandrill_SOURCES *.cpp)

# Libraries are static by default
add_library(Mandrill ${Mandrill_SOURCES})
