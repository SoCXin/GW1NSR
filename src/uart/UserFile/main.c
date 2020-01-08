#include "stm8s.h"
#include "mystm8sxxx.h"


/* In this example UART1 will send data UART3 receive data then echo it back to UART1 */

/* UART1 TX (PA5) connect to UART3 RX(PD6) */
/* UART1 RX (PA4) connect to UART3 TX(PD5) */


uint8_t send_data=32;
volatile int8_t receive_data=0,echo_data=0;


void main(void)
{

	clk_config_16MHz_hse();
	delay_using_timer4_init();

	/* UART1 Initialize*/
	UART1_Init(9600,UART1_WORDLENGTH_8D,
			UART1_STOPBITS_1,
			UART1_PARITY_NO,
			UART1_SYNCMODE_CLOCK_DISABLE,
			UART1_MODE_TXRX_ENABLE);

	/* Enable UART1 receive complete interrupt */
	UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);

	/* Enable UART1 Module */
	UART1_Cmd(ENABLE);

	/* Enable Global Interrupt */
	enableInterrupts();

	while (1)
	{
		UART1_SendData8(send_data);
		delay_ms(1000);
		if(++send_data==127)
		{
			send_data=32;
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
