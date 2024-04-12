add_library(SEGGER "")

file(GLOB_RECURSE SEGGER_SOURCES
        RTT/*.c
)

target_sources(SEGGER
        PRIVATE
        ${SEGGER_SOURCES}
        PUBLIC
        RTT/SEGGER_RTT.h
        RTT/SEGGER_RTT_Conf.h
)

target_include_directories(SEGGER
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/RTT
)