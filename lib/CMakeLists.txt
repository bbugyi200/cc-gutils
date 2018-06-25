include(../shared.cmake)

file(GLOB SOURCES "*.cc")
add_library(gutils STATIC ${SOURCES})
install(TARGETS gutils DESTINATION lib)
