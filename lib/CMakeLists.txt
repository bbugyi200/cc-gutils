include(../shared.cmake)

file(GLOB SOURCES "*.cc")
file(GLOB HEADERS "*.h")
add_library(gutils STATIC ${HEADERS} ${SOURCES})

install(TARGETS gutils DESTINATION lib)
install(FILES gutils.h DESTINATION include)
