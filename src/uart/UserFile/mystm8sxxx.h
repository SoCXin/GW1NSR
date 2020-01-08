#ifndef __MYSTM8SXXX__H
#define __MYSTM8SXXX__H

#include "stm8s.h"
#include "stdlib.h"

typedef enum
{
	I2C_MEMORY_ADDRESS_SIZE_8BIT=	0x00,
	I2C_MEMORY_ADDRESS_SIZE_16BIT=  0x01
}i2c_memory_address_size;


/* @Brief	: 	Initialize clock module, run in mode external crystal HSE
 * @Para	:	None
 * @Return	:	None
 * @Note	:   None
 */
void clk_config_16MHz_hse(void);


/* @Brief	: 	Initialize clock module, run in mode internal crystal HSI
 * @Para	:	None
 * @Return	:	None
 * @Note	:   None
 */
void clk_config_16MHz_hsi(void);


/* @Brief	: 	Initialize timer4, run in mode timer basic for delay function
 * @Para	:	None
 * @Return	:	None
 * @Note	:   User must be implement function delay_isr()
 * 				at INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector
 * 				Then call delay_ms() to start delay.
 */
void delay_using_timer4_init(void);


/* @Brief	: 	Timer 4 Interrupt Service Rountie for Delay function
 * @Para	:	None
 * @Return	:	None
 * @Note	:   User must be implement function delay_isr()
 *  			at INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector
 */
void delay_isr(void);


/* @Brief	: 	Delay function
 * @Para	:	Time to delay (millis seconds)
 * @Return	:	None
 * @Note	:   None
 */
void delay_ms(uint32_t time);


/* @Brief	: 	Initialize I2C Module of MCU STM8S, mode master (400Khz)
 * @Para	:	None
 * @Return	:	None
 * @Note	:   SDA,SCL see datasheet
 */
void i2c_master_init(void);


/* @Brief	: 	Write single or multi bytes data to memory of slave device.
 * @Para	:	+ 	device_address - This is a 7-bit address of slave device sent in the following format
 *					[A6:A5:A4:A3:A2:A1:A0:R/W]. The address of slave device in datasheet must be shift left by 1.
 *
 *				+	mem_address_start - This is address of register in slave device, which is started to write.
 *
 *				+	I2C_MEMORY_ADDRESS_SIZE_X - This is type of address of register in slave device, 8 bit or 16 bit.
 *
 *				+ 	data_array - This is pointer to buffer, which data is written.
 *
 *				+	NumByteToWrite - The length of bytes want to write.
 *
 * @Return	:	0 	if write OK
 * 				!0 	if error occur
 *
 * @Note	:   None
 */
uint8_t i2c_mem_write_arr(uint16_t device_address, uint16_t mem_address_start,i2c_memory_address_size I2C_MEMORY_ADDRESS_SIZE_X, uint8_t* data_array, uint16_t NumByteToWrite);


/* @Brief	: 	Read single or multi bytes data from memory of slave device.
 * @Para	:	+ 	device_address - This is a 7-bit address of slave device sent in the following format
 *					[A6:A5:A4:A3:A2:A1:A0:R/W]. The address of slave device in datasheet must be shift left by 1.
 *
 *				+	mem_address_start - This is address of register in slave device, which is started to read.
 *
 *				+	I2C_MEMORY_ADDRESS_SIZE_X - This is type of address of register in slave device, 8 bit or 16 bit.
 *
 *				+ 	data_array - This is pointer to buffer, which data is stored.
 *
 *				+	NumByteToWrite - The length of bytes want to read.

 * @Return	:	0 	if write OK
 * 				!0 	if error occur
 *
 * @Note	:   None
 */
uint8_t i2c_mem_read_arr(uint16_t device_address, uint16_t mem_address_start,i2c_memory_address_size I2C_MEMORY_ADDRESS_SIZE_X, uint8_t* data_array, uint16_t NumByteToRead);


/* @Brief	: 	Initialize SPI Module of MCU STM8S, run in fullduplex mode (0,0). In this mode Clock to 0
 * 				when idle and The first clock transition is the first data capture edge.
 *
 * @Para	:	SPI_BaudRatePrescaler_X - This is SPI BaudRate Prescaler, SPI frequency = frequency(CPU)/SPI_BaudRatePrescaler_X.
 * @Return	:	None
 * @Note	:   MISO, MOSI, SCK see datasheet
 */
void spi_master_initialize(SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler_X);



/* @Brief	: 	Send and receive single or multi bytes to slave device.
 * @Para	:	+	CS_PORT - This is GPIO PORT of CS pin, for select slave device.
 *
 *				+	CS_PIN - This is GPIO PIN of CS pin, for select slave device.
 *
 *				+ 	send_data - This is pointer to buffer, which data is written.
 *
 *				+ 	receive_data - This is pointer to buffer, which data is stored.
 *					If user only want send data, puts NULL parameter in this position.
 *
 *				+	length	- The length of bytes want to send/receives.
 *
 * @Return	:	0 	if communicate OK
 * 				!0 	if error occur
 *
 * @Note	:   This is fullduplex mode.
 */
uint8_t spi_master_transmit_receive(GPIO_TypeDef* CS_PORT,
		GPIO_Pin_TypeDef CS_PIN,
		uint8_t* send_data,
		uint8_t* receive_data,
		uint16_t length);

#endif

