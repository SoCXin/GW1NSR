/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ********************/
#ifndef __PWM_H
#define __PWM_H
#include "type_def.h"


#define TIM2_Channel   2
#define TIM2_Channel1  1
#define TIM2_Channel2  2
#define TIM2_Channel3  3

#define TIM2_OCMODE_PWM1 0x60 
#define TIM2_OCMODE_PWM2 0x70
#define TIM2_OUTPUTSTATE_ENABLE 0x11
#define TIM2_OCPOLARITY_HIGH 0x00 
#define TIM2_OCPOLARITY_LOW 0x22

void PWM_Init(void);
void SetTIM2_PWM_Frequency(uint16_t TIM2_Period);
void SetTIM2_PWM_DutyCycle( uint16_t TIM2_Pulse);
void TIM2_OC1Init(uint8_t TIM2_OCMode,uint8_t TIM2_OutputState,\
                  uint16_t TIM2_Pulse,uint8_t TIM2_OCPolarity );
void TIM2_OC2Init(uint8_t TIM2_OCMode,uint8_t TIM2_OutputState,\
                  uint16_t TIM2_Pulse,uint8_t TIM2_OCPolarity );
void TIM2_OC3Init(uint8_t TIM2_OCMode,uint8_t TIM2_OutputState,\
                  uint16_t TIM2_Pulse,uint8_t TIM2_OCPolarity );
void TestPWM_LED(void);
void TestPWM_Beep(void);


#endif


/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/