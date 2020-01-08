#ifndef __TIM2_H
#define __TIM2_H
#include "type_def.h"

#define TIM2_PSCRELOADMODE_IMMEDIATE      0x01
#define TIM2_IT_UPDATE       ((uint8_t)0x01)
void Tim2_Time_Upmode_conf(uint8_t TIM2_Prescaler,uint16_t TIM2_Period);
void TimingDelay_Decrement(void);
void delay_ms( u32 nTime);
#endif