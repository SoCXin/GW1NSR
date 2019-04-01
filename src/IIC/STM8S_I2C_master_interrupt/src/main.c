/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V0.0.3
  * @date    Feb 2010
  * @brief   This file contains main test loop for optimized I2C master
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  *                COPYRIGHT 2009 STMicroelectronics
  */ 
	
#include "stm8s.h"
#include "i2c_master_interrupt.h"


// table to store data to be sent
 u8 dummy_Tab[MAX_DUMMY]= { 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90};

// table used to store received data
u8 dummy[MAX_DUMMY];

// Var initialised with u8_NumByte at every add ack to know the initial number of byte to be read or write durring comm
u8 NumByteToRW;


/******************************************************************************
* Function name : main
* Description 	: Main testing loop
* Input param 	: None
* Return 		    : None
* See also 		  : None
*******************************************************************************/
void main (void) 
{ 
	
	// - System CLK configuration 
	#ifdef FAST_I2C_MODE
  CLK->CKDIVR = 0x00;             // sys clock / 1
	#else
  CLK->CKDIVR = 0x01;             // sys clock / 2
	#endif
 
 // - GPIO initialisation for LED
  GPIOA->DDR |=  0xF0;            // GPIO init
  GPIOA->CR1 |=  0xF0;            // all LEDs push pull outputs
  GPIOA->ODR |=  0xF0;
  
  
	// initialize timer 4 mandatory for I2C timout measurement 
  TIM4_Init();                    
  
	// Initialize I2C for communication
	I2C_Init();                     
	
	// Enable all interrupt
  enableInterrupts();

  /* main loop */

	while (!I2C_WriteRegister(0x51,SEV_BIT_ADDRESS,STOP,0x05, &dummy_Tab[0]));
	while(1) 
	{

		while (!I2C_WriteRegister(0x51,SEV_BIT_ADDRESS,NOSTOP,0x01, &dummy_Tab[0]));
		while (!I2C_ReadRegister(0x51,SEV_BIT_ADDRESS,NOSTOP,0x03, &dummy[0]));
		
		while (!I2C_WriteRegister(0x51,SEV_BIT_ADDRESS,NOSTOP,0x01, &dummy_Tab[0]));
		while (!I2C_ReadRegister(0x51,SEV_BIT_ADDRESS,NOSTOP,0x02, &dummy[0]));
		
		while (!I2C_WriteRegister(0x51,SEV_BIT_ADDRESS,NOSTOP,0x01, &dummy_Tab[0]));
		while (!I2C_ReadRegister(0x51,SEV_BIT_ADDRESS,NOSTOP,0x01, &dummy[0]));
	}
	
}





















