add_library(drivers "")

file(GLOB_RECURSE drivers_SOURCES
        "STM32H7xx_HAL_Driver/Src/*.c"
)


target_sources(drivers
        PRIVATE
        ${drivers_SOURCES}
        PUBLIC
        STM32H7xx_HAL_Driver/Inc
        STM32H7xx_HAL_Driver/Inc/Legacy
        CMSIS/Device/ST/STM32H7xx/Include
        CMSIS/Include
)


target_include_directories(drivers
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/STM32H7xx_HAL_Driver/Inc
        ${CMAKE_CURRENT_LIST_DIR}/STM32H7xx_HAL_Driver/Inc/Legacy
        ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32H7xx/Include
        ${CMAKE_CURRENT_LIST_DIR}/CMSIS/Include
)
#target_link_libraries(drivers PRIVATE Core )