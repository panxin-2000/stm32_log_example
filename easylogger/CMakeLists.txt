add_library(easylogger "")

file(GLOB_RECURSE easylogger_SOURCES
        port/elog_port.c
        src/*.c

)
#include_directories(
#        ../SEGGER/RTT
#)

target_sources(easylogger
        PRIVATE
        ${easylogger_SOURCES}
        PUBLIC
)


target_include_directories(easylogger
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(easylogger PRIVATE SEGGER )