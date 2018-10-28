
#ifndef __type_def_h
#define __type_def_h
/*主控芯片的头文件*/
#include "iostm8s207rb.h"
/*bool 类型头文件*/
#include "stdbool.h"
/*总中断头文件*/
#include "intrinsics.h"
/*常用数据类型定义*/
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;
#define FlagStatus     bool
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define EnableInterrupt  __enable_interrupt() 
#endif


