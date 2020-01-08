/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ***************************
 * 文件名  ：pwm.c
 * 描述    ：PWM配置函数库   
 * 实验平台：iCreate STM8开发板
 * 寄存器版本  ：V1.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 *修改时间 ：2011-12-20



****************************************************************************************/
#include "pwm.h"
#define ARR ((uint8_t)499)
static void Delay(u16 nCount);
u16 Beep_Frequency[7]={3816,3400,3029,2864,2550,2272,2023};
/**************************************************************************
 * 函数名：PWM_Init
 * 描述  ：PWM初始化
 * 输入  ：无
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
void PWM_Init(void)
{
    TIM2_PSCR =0x04;
    /* Set the Autoreload value */
    TIM2_ARRH = (uint8_t)(ARR >> 8);
    TIM2_ARRL = (uint8_t)(ARR);
    /*TIM2 Frequency=16M/16/(499+1)=2K*/
    /* PWM1 Mode configuration: Channel1
    TIM2 Channel1 duty cycle = [TIM2_CCR1/(TIM2_ARR + 1)] * 100 = 50%*/ 
  #if TIM2_Channel==TIM2_Channel1
    /*TIM2 Frequency = TIM2 counter clock/(ARR + 1) */

    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,250, TIM2_OCPOLARITY_HIGH);
    
    
  #elif TIM2_Channel==TIM2_Channel2
  
    TIM2_OC2Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,500, TIM2_OCPOLARITY_HIGH);
   
    
  #elif TIM2_Channel==TIM2_Channel3
    
    TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,250, TIM2_OCPOLARITY_HIGH);
  
  #endif
    
  TIM2_CR1 |= (uint8_t)MASK_TIM2_CR1_CEN;
  
}

/**************************************************************************
 * 函数名：TIM2_OC1Init
 * 描述  ：TIM2 第一通道PWM初始化
 * 输入  ：TIM2_OCMode   常用参数TIM2_OCMODE_PWM1:0x60 ,TIM2_OCMODE_PWM2:0x70
           TIM2_OutputState  TIM2_OUTPUTSTATE_ENABLE:0x11
           TIM2_Pulse     占空比
           TIM2_OCPolarity  TIM2_OCPOLARITY_HIGH:0x00 ,TIM2_OCPOLARITY_LOW:0x22
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
void TIM2_OC1Init(uint8_t TIM2_OCMode,uint8_t TIM2_OutputState,uint16_t TIM2_Pulse,uint8_t TIM2_OCPolarity )
{
      /* Disable the Channel 1: Reset the CCE Bit, Set the Output State , the Output Polarity */
    TIM2_CCER1 &= (uint8_t)(~( MASK_TIM2_CCER1_CC1E | MASK_TIM2_CCER1_CC1P));
    /* Set the Output State &  Set the Output Polarity  */
    TIM2_CCER1 |= (uint8_t)((uint8_t)(TIM2_OutputState & MASK_TIM2_CCER1_CC1E ) | 
                             (uint8_t)(TIM2_OCPolarity & MASK_TIM2_CCER1_CC1P));

    /* Reset the Output Compare Bits  & Set the Ouput Compare Mode */
    TIM2_CCMR1 = (uint8_t)((uint8_t)(TIM2_CCMR1 & (uint8_t)(~(uint8_t)MASK_TIM2_CCMR1_OC1M)) |
                            (uint8_t)TIM2_OCMode);
    /* Set the Pulse value */
    TIM2_CCR1H = (uint8_t)(TIM2_Pulse >> 8);
    TIM2_CCR1L = (uint8_t)(TIM2_Pulse);
    TIM2_CCMR1 |= (uint8_t)MASK_TIM2_CCMR1_OC1PE;
}
/**************************************************************************
 * 函数名：TIM2_OC2Init
 * 描述  ：TIM2 第二通道PWM初始化
 * 输入  ：TIM2_OCMode   常用参数TIM2_OCMODE_PWM1:0x60 ,TIM2_OCMODE_PWM2:0x70
           TIM2_OutputState  TIM2_OUTPUTSTATE_ENABLE:0x11
           TIM2_Pulse     占空比
           TIM2_OCPolarity  TIM2_OCPOLARITY_HIGH:0x00 ,TIM2_OCPOLARITY_LOW:0x22
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
void TIM2_OC2Init(uint8_t TIM2_OCMode,uint8_t TIM2_OutputState,uint16_t TIM2_Pulse,uint8_t TIM2_OCPolarity )
{
      /* Disable the Channel 1: Reset the CCE Bit, Set the Output State , the Output Polarity */
    TIM2_CCER1 &= (uint8_t)(~(MASK_TIM2_CCER1_CC2E | MASK_TIM2_CCER1_CC2P));
    /* Set the Output State &  Set the Output Polarity  */
    TIM2_CCER1 |= (uint8_t)((uint8_t)(TIM2_OutputState & MASK_TIM2_CCER1_CC2E ) | 
                             (uint8_t)(TIM2_OCPolarity & MASK_TIM2_CCER1_CC2P));

    /* Reset the Output Compare Bits  & Set the Ouput Compare Mode */
    TIM2_CCMR2 = (uint8_t)((uint8_t)(TIM2_CCMR1 & (uint8_t)(~(uint8_t)MASK_TIM2_CCMR2_OC2M )) |
                            (uint8_t)TIM2_OCMode);
    /* Set the Pulse value */
    TIM2_CCR2H = (uint8_t)(TIM2_Pulse >> 8);
    TIM2_CCR2L = (uint8_t)(TIM2_Pulse);
    TIM2_CCMR2 |= (uint8_t)MASK_TIM2_CCMR2_OC2PE;
}
/**************************************************************************
 * 函数名：TIM2_OC3Init
 * 描述  ：TIM2 第三通道PWM初始化
 * 输入  ：TIM2_OCMode   常用参数TIM2_OCMODE_PWM1:0x60 ,TIM2_OCMODE_PWM2:0x70
           TIM2_OutputState  TIM2_OUTPUTSTATE_ENABLE:0x11
           TIM2_Pulse     占空比
           TIM2_OCPolarity  TIM2_OCPOLARITY_HIGH:0x00 ,TIM2_OCPOLARITY_LOW:0x22
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
void TIM2_OC3Init(uint8_t TIM2_OCMode,uint8_t TIM2_OutputState,uint16_t TIM2_Pulse,uint8_t TIM2_OCPolarity )
{
      /* Disable the Channel 1: Reset the CCE Bit, Set the Output State , the Output Polarity */
    TIM2_CCER2 &= (uint8_t)(~( MASK_TIM2_CCER2_CC3E | MASK_TIM2_CCER2_CC3P));
    /* Set the Output State &  Set the Output Polarity  */
    TIM2_CCER2 |= (uint8_t)((uint8_t)(TIM2_OutputState & MASK_TIM2_CCER2_CC3E ) | 
                             (uint8_t)(TIM2_OCPolarity & MASK_TIM2_CCER2_CC3P));

    /* Reset the Output Compare Bits  & Set the Ouput Compare Mode */
    TIM2_CCMR3 = (uint8_t)((uint8_t)(TIM2_CCMR1 & (uint8_t)(~(uint8_t)MASK_TIM2_CCMR3_OC3M )) |
                            (uint8_t)TIM2_OCMode);
    /* Set the Pulse value */
    TIM2_CCR3H = (uint8_t)(TIM2_Pulse >> 8);
    TIM2_CCR3L = (uint8_t)(TIM2_Pulse);
    TIM2_CCMR3 |= (uint8_t)MASK_TIM2_CCMR3_OC3PE;
}


void SetTIM2_PWM_Frequency(uint16_t TIM2_Period)
{
      /* Set the Autoreload value */
  
    TIM2_ARRH = (uint8_t)(TIM2_Period >> 8);
    TIM2_ARRL = (uint8_t)(TIM2_Period);
}

void SetTIM2_PWM_DutyCycle( uint16_t TIM2_Pulse)
{
  
    
  #if TIM2_Channel==TIM2_Channel1
    /* Set the Pulse value */
    TIM2_CCR1H = (uint8_t)(TIM2_Pulse >> 8);
    TIM2_CCR1L = (uint8_t)(TIM2_Pulse);
    
  #elif TIM2_Channel==TIM2_Channel2
    TIM2_CCR2H = (uint8_t)(TIM2_Pulse >> 8);
    TIM2_CCR2L = (uint8_t)(TIM2_Pulse);
    
  #elif TIM2_Channel==TIM2_Channel3
    TIM2_CCR3H = (uint8_t)(TIM2_Pulse >> 8);
    TIM2_CCR3L = (uint8_t)(TIM2_Pulse);
    
  #endif
}

void TestPWM_LED(void)
{
  u16 Duty_Val;
  for(Duty_Val=0;Duty_Val<499;Duty_Val++)
  {
    SetTIM2_PWM_DutyCycle(Duty_Val);
    Delay(0xfff);
  }
}

void TestPWM_Beep(void)
{
  u8 i;
  for(i=0;i<7;i++)
  {
    SetTIM2_PWM_Frequency(Beep_Frequency[i]);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);

  }
}
static void Delay(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}


/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/