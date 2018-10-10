file(GLOB SOURCES "*.cc")
include(../shared.cmake)
add_library(gutils STATIC ${SOURCES})
target_include_directories(gutils PUBLIC ../include)

file(GLOB HEADERS "../include/*.h")
set_target_properties(gutils PROPERTIES PUBLIC_HEADER ${HEADERS})

glib_opts(gutils)

install(TARGETS gutils 
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
