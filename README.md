# 项目说明
这个项目是基于stm32h7xx的仓库
目的是结合segger RTT和easylogger组合，然后通过另一个项目，组合qt和openocd在电脑上显示log

## 硬件平台
[STM32H7xx Core Board](https://www.weact-tc.cn/2020/02/06/Products/)
借用了其中的控制led灯闪烁的工程代码，修改了该工程的编译方式，做了现在的这个项目

原本的工程是在keil中编译的，我使用cmake配置项目中用的文件，生成makefile文件，
然后调用`arm-none-eabi-gcc`编译项目，使用`openocd`烧录和调试项目代码。

做这个项目是为了另一个项目[openocd_display](https://github.com/panxin22911/openocd_display)而做的,具体信息请点击链接查看。

# 文件说明

`STM32H750VBTX_FLASH.ld`是链接文件，就是说明了代码的各个段都是怎么在内存中分配的。

## openocd文件夹

`openocd_config`文件夹中放置的是`openocd`的配置文件，其中有两个配置文件，
`stlink-rtt.cfg`是查看log和调试时用的配置文件
`stm32h750vbt6.cfg`是下载和调试时用的配置文件

## easylogger文件夹
这里是放置的是[easylogger](https://github.com/armink/EasyLogger)项目的代码，
其中我只修改了一个`elog_port.c`中的代码
```
void elog_port_output(char *log, size_t size) {
    /* add your code here */
    *(log + size) = 0;  //这行的目的是在输出的字符串的末尾增加\0,用了标识结束
    SEGGER_RTT_printf(0,log);  //这里是easy_logger调用segger rtt输出信息
}
```

## SEGGER文件夹

[SEGGER's Real Time Transfer (RTT)](https://wiki.segger.com/RTT)的api说明可以看这里

[代码仓库](https://github.com/adfernandes/segger-rtt):这个仓库不是官方的仓库，但是可以从这里复制下载代码


