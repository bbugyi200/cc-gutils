include(../shared.cmake)

file(GLOB SOURCES "*.cc")
file(GLOB HEADERS "../include/*.h")
add_library(gutils STATIC ${SOURCES})
target_include_directories(gutils PUBLIC ../include)

set_target_properties(gutils PROPERTIES PUBLIC_HEADER ${HEADERS})

install(TARGETS gutils 
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
