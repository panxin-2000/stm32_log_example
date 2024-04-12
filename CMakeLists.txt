#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.24)

# specify cross-compilers and tools
# 指定交叉编译期和工具
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
# 可以通过 man objcopy 查看具体的描述和执行时的参数
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(stm32_log_example C CXX ASM)
# 设置项目的编程语言，我在这个项目中只用到了c和汇编，没有用c++
set(CMAKE_CXX_STANDARD 17)
# 设置c++的标准
set(CMAKE_C_STANDARD 11)
# 设置c的标准，其实常用的c99标准，看标准的时候也是看这个版本的标准，c11的标准我并没有看过并和c99进行对比
# 个人的小项目，暂时先留着不改了

#Uncomment for hardware floating point
#add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
#add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
#add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)

add_compile_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

#解释一下下面是怎么工作的
#cmake -D CMAKE_BUILD_TYPE=Release ..
#cmake -D CMAKE_BUILD_TYPE=RelWithDebInfo ..
#cmake -D CMAKE_BUILD_TYPE=MinSizeRel ..
#cmake -D CMAKE_BUILD_TYPE=Debug ..
#当默认不做设置时就是Debug模式

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    # 没搞清楚${CMAKE_BUILD_TYPE}这个参数是从那里传递过来的，所以就先把上面的都注释掉了
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
    add_definitions(-DDEBUG)
    add_definitions(-DUSE_FULL_ASSERT)
    #  USE_FULL_ASSERT这个hal库中用来判断参数是否合法的，具体细节见下一行
    #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
    # __FILE__ 和 __LINE__ 编译器内置的宏，可以参数非法时输出哪一行的参数非法了
endif ()

# 添加宏定义的选项，
# 其实上面已经添加过和调试相关的两个宏了
add_definitions(-DUSE_HAL_DRIVER)
add_definitions(-DSTM32H750xx)


include_directories(
        Core/Inc)
file(GLOB_RECURSE SOURCES
        "Core/*.c"
        #        "Drivers/*.c"
        "Core/Startup/startup_stm32h750vbtx.s"
)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32H750VBTX_FLASH.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork -specs=nano.specs -specs=nosys.specs)
add_link_options(-T ${LINKER_SCRIPT})


add_subdirectory(SEGGER)
add_subdirectory(easylogger)
add_subdirectory(Drivers)

add_executable(${PROJECT_NAME}.elf ${SOURCES}  ${LINKER_SCRIPT})


target_link_libraries(${PROJECT_NAME}.elf PRIVATE SEGGER easylogger drivers)


set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        # 最后执行的命令如下
        #  arm-none-eabi-objcopy -Oihex cmake-build-debug/GPIO.elf cmake-build-debug/GPIO.bin
        # 执行 ls -l 查看结果
        #-rw-rw-r-- 1 panxin panxin  57531  4月 11 10:37 GPIO.bin
        #-rwxrwxr-x 1 panxin panxin 401776  4月 10 17:05 GPIO.elf
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        # 这个command就不再去具体说明了

        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
