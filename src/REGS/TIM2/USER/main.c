
/******************** (C) COPYRIGHT  ********************
 * �ļ���  ��main.c
 * ����    ��TIM2��ʱ����ʹ��  
 * ʵ��ƽ̨��iCreate STM8������
 * �Ĵ����汾  ��V1.0.0
 * ����    ��
 * ����    ��
 * �Ա�    ��
 *�޸�ʱ�� ��
**********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "clk_conf.h"
#include "tim2.h"
#include "led.h"
#include "pwm.h"
#include "beep.h"

#define TIM2_Mode  0
#define PWM        0
#define BaseTime   1

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void)
{
  /* Infinite loop */

  /*�����ڲ�����ʱ��16MΪ��ʱ��*/ 
  Clk_conf();
  

   #if TIM2_Mode==BaseTime 
   Tim2_Time_Upmode_conf(0x04,999);
   LED_conf();
   Set_Led_Off();
   EnableInterrupt;
   
  #elif TIM2_Mode==PWM  
     PWM_Init();
     #if TIM2_Channel==TIM2_Channel1
     Set_Beep_OptionByte();
     #endif
    
  #endif
  while(1)
  {

    #if TIM2_Mode==BaseTime 
    /************��׼��51��̷��*************************/
      PD0_out = 0;    /* PD0�������0 */
      delay_ms(1000); 
      PD0_out = 1;    /* PD0�������1 */
      delay_ms(1000); 
    /**************��׼��51��̷��*************************/
    #elif TIM2_Mode==PWM 
        #if TIM2_Channel==TIM2_Channel2
        TestPWM_LED();
        #elif TIM2_Channel==TIM2_Channel1
        TestPWM_Beep();
        #endif
    #endif
  }
}






#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/
