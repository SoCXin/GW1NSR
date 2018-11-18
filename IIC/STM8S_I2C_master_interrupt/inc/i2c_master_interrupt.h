#ifndef __I2C_MST_INT_H
#define __I2C_MST_INT_H

#include "stm8s.h"

#define MAX_DUMMY 10

/* flag clearing sequence - uncoment next for peripheral clock under 2MHz */
#define dead_time() { /* _asm("nop"); _asm("nop"); */ }

#define I2C_TOUT  40

#define delay(a)          { TIM4_tout= a; while(TIM4_tout); }
#define tout()            (TIM4_tout)
#define set_tout_ms(a)    { TIM4_tout= a; }

#define WRITE 0
#define READ  1
#define SEV_BIT_ADDRESS 0
#define TEN_BIT_ADDRESS 1
#define STOP 0
#define NOSTOP 1

// Define I2C STATE MACHINE :

#define INI_00 00

// Write states 0x
#define SB_01 01
#define ADD10_02 02
#define ADDR_03 03
#define BTF_04 04

// Read states 1x
#define SB_11 11
#define ADD10_12 12
#define ADDR_13 13
#define BTF_14 14
#define BTF_15 15
#define RXNE_16 16
#define BTF_17 17
#define RXNE_18 18


// Eval STM8/128-EVAL board constant 
#define LED1  0x01
#define LED2  0x02
#define LED3  0x04
#define LED4  0x08
#define switch_on(msk) GPIOH->ODR &= ~(msk);
#define switch_off(msk) GPIOH->ODR |= (msk);


// Exported function 

void I2C_Init(void);
void TIM4_Init(void);
void ErrProc (void);
u8 I2C_WriteRegister(u16 u16_SlaveAdd, u8 u8_AddType, u8 u8_NoStop, u8 u8_NumByteToWrite, u8 *pu8_DataBuffer);
u8 I2C_ReadRegister(u16 u16_SlaveAdd, u8 u8_AddType, u8 u8_NoStop, u8 u8_NumByteToRead, u8 *u8_DataBuffer);

// Exported Interrupt handler 

#ifdef _COSMIC_
@far @interrupt void I2CInterruptHandle (void);
#else
void I2CInterruptHandle (void) interrupt 19;
#endif

#ifdef _COSMIC_
@far @interrupt void TIM4InterruptHandle (void);
#else
void TIM4InterruptHandle (void) interrupt 25;
#endif



#endif /* __I2C_MST_INT_H */

