/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ***************************
 * 文件名  ：
 * 描述    ：中断服务子函数库   
 * 实验平台：iCreate STM8开发板
 * 寄存器版本  ：V1.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 *修改时间 ：2011-12-20



****************************************************************************************/
#include "tim2.h"
#pragma vector=1
__interrupt void TRAP_IRQHandler(void)
{
  
}
#pragma vector=2
__interrupt void TLI_IRQHandler(void)
{
  
}
#pragma vector=3
__interrupt void AWU_IRQHandler(void)
{
  
}
#pragma vector=4
__interrupt void CLK_IRQHandler(void)
{
  
  
}
#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
  
}
#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  
}
#pragma vector=7
__interrupt void EXTI_PORTC_IRQHandler(void)
{
  
}
#pragma vector=8
__interrupt void EXTI_PORTD_IRQHandler(void)
{
 
  
}
#pragma vector=9
__interrupt void EXTI_PORTE_IRQHandler(void)
{
   
}


#pragma vector=0xC
__interrupt void SPI_IRQHandler(void)
{
  
}
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{



}
#pragma vector=0xE
__interrupt void TIM1_CAP_COM_IRQHandler(void)
{
  
}

#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
    TimingDelay_Decrement();
  /* Clear the IT pending Bit */
  TIM2_SR1 = (uint8_t)(~TIM2_IT_UPDATE);
}
#pragma vector=0x10
__interrupt void TIM2_CAP_COM_IRQHandler(void)
{
  
}


#pragma vector=0x11
__interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)
{
  
}
#pragma vector=0x12
__interrupt void TIM3_CAP_COM_IRQHandler(void)
{
  
}


#pragma vector=0x13
__interrupt void UART1_TX_IRQHandler(void)
{
  
}
#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{ 

}

#pragma vector=0x15
__interrupt void I2C_IRQHandler(void)
{
  
}


#pragma vector=0x16
__interrupt void UART3_TX_IRQHandler(void)
{
  
}
#pragma vector=0x17
__interrupt void UART3_RX_IRQHandler(void)
{
  
}


#pragma vector=0x18
__interrupt void ADC2_IRQHandler(void)
{
   
}


#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
  
}

#pragma vector=0x1A
__interrupt void EEPROM_EEC_IRQHandler(void)
{
  
}


/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/