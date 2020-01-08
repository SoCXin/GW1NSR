/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************************
 * �ļ���  ��tim2.c
 * ����    ����ʱ��TM2���ú�����   
 * ʵ��ƽ̨��iCreate STM8������
 * �Ĵ����汾  ��V1.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 * �޸�ʱ�� ��2011-12-20



****************************************************************************************/


#include "tim2.h"

static  u32 TimingDelay; 
/**************************************************************************
 * ��������Tim2_Time_Upmode_conf
 * ����  ��TIM2��ʱ�����ܳ�ʼ��
 * ����  ��uint8_t TIM2_Prescaler ֻ����2��N���� 1��2��4��8
           uint16_t TIM2_Period   1��65535
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
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
 * ��������TimingDelay_Decrement
 * ����  ��
 * ����  ����        
 *
 * ���  ����
 * ����  ���� 
 * ����  ���жϷ��������� 
 *************************************************************************/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
     { 
	TimingDelay--;
      }
}
/**************************************************************************
 * ��������delay_ms
 * ����  ��
 * ����  ��nTime       
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
 *************************************************************************/
void delay_ms( u32 nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/
