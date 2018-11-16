# [STM8S](https://github.com/mcuyun/STM8S) 

STM8S高性能通用系列

[![sites](mcuyun/mcuyun.png)](http://www.mcuyun.com)

#### 更多MCU：[mcuyun](https://github.com/mcuyun/whyme)可访问 www.mcuyun.com

---

## 组成

#### docs

包括芯片手册等资料  STM8S中文参考手册.pdf

#### demo

包括IAR工程和相关库文件

#### examples

包括makefile工程



## Code Structure
* `stm8s` contain libraries and examples for corresponding microcontroller families
* `lib` contains `stm8s.h` header with register definitions and very basic peripheral drivers
* `examples` contains directories with example code

## Building
Dependencies:
 1. [sdcc](https://sourceforge.net/projects/sdcc/)
 2. [stm8flash](https://github.com/vdudouyt/stm8flash)

Building and flashing example project:

```
cd ./stm8s/examples/<example>
make flash
```
Uncomment `--peep-file $(LIBDIR)/util/extra.def` option in the Makefile to enable additional optimizer rules.

---

###  www.mcuyun.com   |    qitas@qitas.cn



