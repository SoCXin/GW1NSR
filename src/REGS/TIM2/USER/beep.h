#ifndef __BEEP_H
#define __BEEP_H
#include "type_def.h"
#define Beep_OptionAdd  0x4803
#define FLASH_OPTIONBYTE_ERROR  ((uint16_t)0x5555)
#define OPERATION_TIMEOUT  ((uint32_t)0xFFFFF)
#define LSI_128kHz 128000
#define BEEP_FREQUENCY_2KHZ 0x40
#define NEAR __near
void Set_Beep_OptionByte(void);
#endif