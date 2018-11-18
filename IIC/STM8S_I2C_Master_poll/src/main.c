/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V0.0.3
  * @date    Feb 2010
  * @brief   This file contains main test loop for optimized I2C master
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 
#include "stm8s.h"
#include "i2c_master_poll.h"
#include <string.h>

const u8 DUMMY_INIT[MAX_DUMMY]= { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0 };

u8 Dummy[MAX_DUMMY];
volatile u8 err_save;
volatile u16 TIM4_tout;
u16 loop_count;


/******************************************************************************
* Function name : main
* Description 	: Main testing loop
* Input param 	: None
* Return 		    : None
* See also 		  : None
*******************************************************************************/
void main (void) { 
  /* peripheral initialization */  
	#ifdef FAST_I2C_MODE
  CLK->CKDIVR = 0x00;             // sys clock / 1
	#else
  CLK->CKDIVR = 0x01;             // sys clock / 2
	#endif
  
	// Set GPIO for LED uses 
  GPIOH->DDR |=  0x0F;            
  GPIOH->CR1 |=  0x0F;            
  
	// initialize timer 4 mandatory for timout and tick measurement 
  TIM4_Init();                    
  
	// Initialize I2C for communication
	I2C_Init();                     
  
  // initialization of dummy field for test purpose    
  memcpy(Dummy, DUMMY_INIT, MAX_DUMMY);
  
	#ifndef _COSMIC_
  err_save= 0;
  TIM4_tout= loop_count= 0;
	#endif
  
	// Enable all interrupts  
	enableInterrupts();

  /* main test loop */
  while(1) {
		// switch on LED1 at the beginning of test
    switch_on(LED1);
		// write 1 data bytes with offset 8 from Dummy filed to slave memory
    set_tout_ms(10);
    I2C_WriteRegister(8, 1, &Dummy[8]);
    // read 1 byte with offset 8 back from the image at slave memory
    if(tout()) {
      set_tout_ms(10);
      I2C_ReadRegister(8, 1, &Dummy[8]);
    }
    // write 6 bytes with offset 2 from Dummy filed to slave memory
    if(tout()) {
      set_tout_ms(10);
      I2C_WriteRegister(2, 6, &Dummy[2]);
    }
    // read 6 bytes with offset 2 back from the image at slave memory
    if(tout()) {
      set_tout_ms(10);
      I2C_ReadRegister(2, 6, &Dummy[2]);
    }
    // write 1 byte with offset 9 from Dummy filed to slave memory
    if(tout()) {
      set_tout_ms(10);
      I2C_WriteRegister(9, 1, &Dummy[9]);
    }
    // read 1 byte with offset 9 back from the image at slave memory
    if(tout()) {
      set_tout_ms(10);
      I2C_ReadRegister(9, 1, &Dummy[9]);
    }
    // write 2 bytes with offset 0 from Dummy filed to slave memory
    if(tout()) {
      set_tout_ms(10);
      I2C_WriteRegister(0, 2, &Dummy[0]);
    }
    // read 2 bytes with offset 0 back from the image at slave memory
    if(tout()) {
      set_tout_ms(10);
      I2C_ReadRegister(0, 2, &Dummy[0]);
    }
    // if a timout error occures switch on LED2 
    if(!tout())
      switch_on(LED2);
		// switch off LED1 at the end of test
    switch_off(LED1);
    // check if dummy field is not corrupted => switch on LED 4 if test not successful   
    if(memcmp(Dummy, DUMMY_INIT, MAX_DUMMY) != 0)
      switch_on(LED4);
    delay(1);
  }
}