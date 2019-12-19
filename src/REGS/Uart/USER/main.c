
/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ********************
 * 文件名  ：main.c
 * 描述    ：串口通信   
 * 实验平台：iCreate STM8开发板
 * 寄存器版本  ：V1.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 *修改时间 ：2011-12-20
**********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "clk_conf.h"
#include "uart.h"



/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern u8 RxBuffer[RxBufferSize];
extern u8 UART_RX_NUM;
int main(void)
{
  /* Infinite loop */
   u8 len ;
  /*设置内部高速时钟16M为主时钟*/ 
  Clk_conf();
  uart_conf();
  EnableInterrupt;
  printf("\r\n MCU:%s\r\n","STM8S");
  printf("\r\n%s\r\n","TEST V1.0.0");
  printf("\r\nFOR:%s\r\n","在串口助手输入字符或者字符串必须要按下回车键，再点击发送");
  while(1)
  {
      /* 添加你的代码  */
      if(UART_RX_NUM&0x80)
      {
        len=UART_RX_NUM&0x3f;/*得到此次接收到的数据长度*/
        UART1_SendString("You sent the messages is:",sizeof("You sent the messages is"));
        UART1_SendString(RxBuffer,len);
        printf("\r\nlen:%dByte\r\n",len);
        UART_RX_NUM=0;
      }
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

/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/
