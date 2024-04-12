##TODO:问题：为什么这里不能也当作一个库来引入？
## 要么从生成的makefile文件入手，要么从生成的编译结果进行对比
##加入下面的内容的话，会生成一个libCore.a的库，不加入的话，则没有
#add_library(Core "")
#
#file(GLOB_RECURSE Core_SOURCES
#        "Src/*.c"
#        "Startup/startup_stm32h750vbtx.s"
#)
#
#include_directories(Inc)
#
#target_sources(Core
#        PRIVATE
#        ${Core_SOURCES}
#        PUBLIC
#        Inc
#)
#
#
#target_include_directories(Core
#        PUBLIC
#        Inc
#)
#
#target_link_libraries(Core PRIVATE SEGGER easylogger drivers )