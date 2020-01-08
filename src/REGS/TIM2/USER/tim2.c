/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ***************************
 * 文件名  ：tim2.c
 * 描述    ：定时器TM2配置函数库   
 * 实验平台：iCreate STM8开发板
 * 寄存器版本  ：V1.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 * 修改时间 ：2011-12-20



****************************************************************************************/


#include "tim2.h"

static  u32 TimingDelay; 
/**************************************************************************
 * 函数名：Tim2_Time_Upmode_conf
 * 描述  ：TIM2定时器功能初始化
 * 输入  ：uint8_t TIM2_Prescaler 只能是2的N次幂 1，2，4，8
           uint16_t TIM2_Period   1～65535
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
void Tim2_Time_Upmode_conf(uint8_t TIM2_Prescaler,uint16_t TIM2_Period)
{
    TIM2_PSCR = (uint8_t)(TIM2_Prescaler);
    /* Set the Autoreload value */
    TIM2_ARRH = (uint8_t)(TIM2_Period >> 8);
    TIM2_ARRL = (uint8_t)(TIM2_Period);
    /* Set or reset the UG Bit */
    TIM2_EGR = (uint8_t)TIM2_PSCRELOADMODE_IMMEDIATE; 
    /*!< Auto-Reload Preload Enable mask. */
    TIM2_CR1 |= (uint8_t)MASK_TIM2_CR1_ARPE;
    /* Enable the Interrupt sources */
    TIM2_IER |= (uint8_t)TIM2_IT_UPDATE;
    /*!< Counter Enable mask. */
    TIM2_CR1 |= (uint8_t)MASK_TIM2_CR1_CEN;

}
/**************************************************************************
 * 函数名：TimingDelay_Decrement
 * 描述  ：
 * 输入  ：无        
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：中断服务函数调用 
 *************************************************************************/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
     { 
	TimingDelay--;
      }
}
/**************************************************************************
 * 函数名：delay_ms
 * 描述  ：
 * 输入  ：nTime       
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
void delay_ms( u32 nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/
