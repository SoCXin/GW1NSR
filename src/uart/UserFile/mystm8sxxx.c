#include "mystm8sxxx.h"
#include "stm8s_clk.h"

volatile uint32_t time_keeper=0;

/* @Brief	: 	Initialize clock module, run in mode external crystal HSE
 * @Para	:	None
 * @Return	:	None
 * @Note	:   None
 */
void clk_config_16MHz_hse(void)
{
	CLK_DeInit();
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}


/* @Brief	: 	Initialize I2C Module of MCU STM8S, mode master (400Khz)
 * @Para	:	None
 * @Return	:	None
 * @Note	:   SDA,SCL see datasheet
 */
void clk_config_16MHz_hsi(void)
{
	CLK_DeInit();
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}


/* @Brief	: 	Initialize timer4, run in mode timer basic for delay function
 * @Para	:	None
 * @Return	:	None
 * @Note	:   User must be implement function delay_isr() at
 * 				INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector.
 * 				Then call delay_ms() to start delay.
 */
void delay_using_timer4_init(void)
{
	TIM4_TimeBaseInit(TIM4_PRESCALER_128,124);//1ms if fMaster=16Mhz
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);

	enableInterrupts();
	TIM4_Cmd(DISABLE);
}


/* @Brief	: 	Timer 4 Interrupt Service Rountie for Delay function
 * @Para	:	None
 * @Return	:	None
 * @Note	:   User must be implement function delay_isr()
 * 				at INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector
 */
void delay_isr(void)
{
	if(TIM4_GetITStatus(TIM4_IT_UPDATE)==SET)
	{
		if(time_keeper!=0)
		{
			time_keeper--;
		}
		else
		{
			/* Disable Timer to reduce power consumption */
			TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
		}
		TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
	}
}


/* @Brief	: 	Delay function
 * @Para	:	Time to delay (millis seconds)
 * @Return	:	None
 * @Note	:   None
 */
void delay_ms(uint32_t time)
{
	time_keeper=time;

	/* Reset Counter Register value */
	TIM4->CNTR = (uint8_t)(0);

	/* Enable Timer */
	TIM4->CR1 |= TIM4_CR1_CEN;

	while(time_keeper);
}

/* @Brief	: 	Initialize I2C Module of MCU STM8S, mode master (400Khz)
 * @Para	:	None
 * @Return	:	None
 * @Note	:   SDA,SCL Pin see in the datasheet
 */
void i2c_master_init(void)
{
	/* Deinit I2C */
	I2C_DeInit();

	/* I2C Peripheral clock enable */
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,ENABLE);

	/* Enable I2C Module */
	I2C_Cmd( ENABLE);

	/* I2C configuration after enabling it */
	I2C_Init(400000,			// SCL 400 Khz
			0x50,				// Don't care because of I'm Master
			I2C_DUTYCYCLE_2,
			I2C_ACK_CURR,
			I2C_ADDMODE_7BIT,
			16					// Supply Frequency = 16Mhz = FCPU
	);
}


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

 * @Return	:	0 	if write OK
 * 				!0 	if error occur
 *
 * @Note	:   None
 */
uint8_t i2c_mem_write_arr(uint16_t device_address, uint16_t mem_address_start ,i2c_memory_address_size I2C_MEMORY_ADDRESS_SIZE_X, uint8_t* data_array, uint16_t NumByteToWrite)
{
	uint16_t time_out= 5000;

	/* If I2C bus is busy wait ultil it is free */
	while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY)&& (--time_out));
	if(!time_out) return 1;

	/* Send Start Condition then wait event EV5 */
	I2C_GenerateSTART(ENABLE);
	while ((!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))&& (--time_out));
	if(!time_out) return 1;

	/* Send device address to write data then wait event EV6 */
	I2C_Send7bitAddress(device_address, I2C_DIRECTION_TX);
	while((!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))&& (--time_out));
	if(!time_out) return 1;

	/* Send memory address pointer then wait event EV8_2 */

	switch(I2C_MEMORY_ADDRESS_SIZE_X)
	{
	case I2C_MEMORY_ADDRESS_SIZE_8BIT:
		I2C_SendData((uint8_t)mem_address_start);
		break;
	case I2C_MEMORY_ADDRESS_SIZE_16BIT:

		//Send MSB
		I2C_SendData((uint8_t)(mem_address_start>>8));
		while((!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))&& (--time_out));
		if(!time_out) return 1;

		//Send LSB
		I2C_SendData((uint8_t)(mem_address_start&0x00ff));
		break;
	}

	while((!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))&& (--time_out));
	if(!time_out) return 1;

	for(uint16_t i=0;i<NumByteToWrite;i++)
	{
		I2C_SendData(*(data_array+i));
		while((!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))&& (--time_out));
		if(!time_out) return 1;
	}

	I2C_GenerateSTOP(ENABLE);
	return 0;
}


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
uint8_t i2c_mem_read_arr(uint16_t device_address, uint16_t mem_address_start,i2c_memory_address_size I2C_MEMORY_ADDRESS_SIZE_X, uint8_t* data_array, uint16_t NumByteToRead)
{
	uint16_t time_out= 5000;

	/* If I2C bus is busy wait ultil it is free */
	while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY)&& (--time_out));
	if(!time_out) return 1;

	/* Send Start Condition then wait event EV5 */
	I2C_GenerateSTART(ENABLE);
	while ((!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))&& (--time_out));
	if(!time_out) return 1;

	/* Send device address to write data then wait event EV6 */
	I2C_Send7bitAddress(device_address, I2C_DIRECTION_TX);
	while((!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))&& (--time_out));
	if(!time_out) return 1;

	/* Send memory address pointer then wait event EV8_2 */

	switch(I2C_MEMORY_ADDRESS_SIZE_X)
	{
	case I2C_MEMORY_ADDRESS_SIZE_8BIT:
		I2C_SendData((uint8_t)mem_address_start);
		break;
	case I2C_MEMORY_ADDRESS_SIZE_16BIT:

		//Send MSB
		I2C_SendData((uint8_t)(mem_address_start>>8));
		while((!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))&& (--time_out));
		if(!time_out) return 1;

		//Send LSB
		I2C_SendData((uint8_t)(mem_address_start&0x00ff));
		break;
	}

	while((!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))&& (--time_out));
	if(!time_out) return 1;

	/* Send Repeat Start Condition then wait event EV5 */
	I2C_GenerateSTART(ENABLE);
	while ((!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))&& (--time_out));
	if(!time_out) return 1;

	/* Send device address to read data then wait event EV6 */
	I2C_Send7bitAddress(device_address, I2C_DIRECTION_RX);
	while((!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))&& (--time_out));
	if(!time_out) return 1;

	if(NumByteToRead == 1)
	{
		/* Disable Acknowledgement */
		I2C_AcknowledgeConfig(I2C_ACK_NONE);

		/* Send STOP Condition */
		I2C_GenerateSTOP(ENABLE);

		/* Poll on RxNE Flag */
		while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET) && (--time_out));
		if(!time_out) return 1;

		/* Read a byte from the Slave */
		*data_array = I2C_ReceiveData();
	}
	else if(NumByteToRead == 2)
	{
		disableInterrupts();

		/* Poll on RxNE Flag */
		while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET)&& (--time_out));
		if(!time_out) return 1;

		*data_array = I2C_ReceiveData();

		data_array++;

		/* Disable Acknowledgement */
		I2C_AcknowledgeConfig(I2C_ACK_NONE);

		/* Send STOP Condition */
		I2C_GenerateSTOP(ENABLE);

		/* Poll on RxNE Flag */
		while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET)&& (--time_out));
		if(!time_out) return 1;

		enableInterrupts();
		/* Read a byte from the Slave */
		*data_array = I2C_ReceiveData();
	}
	else
	{
		while (NumByteToRead)
		{
			if (NumByteToRead != 3) /* Receive bytes from first byte until byte N-3 */
			{
				while ((I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == RESET)&& (--time_out));
				if(!time_out) return 1;

				/* Read a byte from the Slave */
				*data_array = I2C_ReceiveData();

				/* Point to the next location where the byte read will be saved */
				data_array++;

				/* Decrement the read bytes counter */
				NumByteToRead--;
			}
			if (NumByteToRead == 3)  /* it remains to read three data: data N-2, data N-1, Data N */
			{
				/* Data N-2 in DR and data N -1 in shift register */

				/* Poll on BTF */
				while ((I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == RESET)&& (--time_out));
				if(!time_out) return 1;

				/* Clear ACK */
				I2C_AcknowledgeConfig(I2C_ACK_NONE);

				/* Disable general interrupts */
				disableInterrupts();

				/* Read Data N-2 */
				*data_array = I2C_ReceiveData();

				/* Point to the next location where the byte read will be saved */
				data_array++;

				/* Program the STOP */
				I2C_GenerateSTOP(ENABLE);

				/* Read DataN-1 */
				*data_array = I2C_ReceiveData();

				/* Enable General interrupts */
				enableInterrupts();

				/* Point to the next location where the byte read will be saved */
				data_array++;

				while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET)&& (--time_out)); /* Poll on RxNE */
				if(!time_out) return 1;

				/* Read DataN */
				*data_array = I2C_ReceiveData();

				/* Reset the number of bytes to be read by master */
				NumByteToRead = 0;
			}
		}
	}
	I2C_AcknowledgeConfig(I2C_ACK_CURR);
	return 0;
}


/* @Brief	: 	Initialize SPI Module of MCU STM8S, run in mode (0,0). In this mode Clock to 0 when
 * 				idle and The first clock transition is the first data capture edge.
 *
 * @Para	:	SPI_BaudRatePrescaler_X - This is SPI BaudRate Prescaler,
 * 				SPI frequency = frequency(CPU)/SPI_BaudRatePrescaler_X.
 *
 * @Return	:	None
 * @Note	:   MISO, MOSI, SCK see datasheet
 */
void spi_master_initialize(SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler_X)
{
	/* Enable SPI clock */
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI,ENABLE);

	/* Set the MOSI,MISO and SCK at high level */
	GPIO_ExternalPullUpConfig(GPIOC, (GPIO_Pin_TypeDef)(GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7), ENABLE);

	/* Initialize SPI mode master 0 */
	SPI_Init( SPI_FIRSTBIT_MSB,
			SPI_BaudRatePrescaler_X,
			SPI_MODE_MASTER,
			SPI_CLOCKPOLARITY_LOW,
			SPI_CLOCKPHASE_1EDGE,
			SPI_DATADIRECTION_2LINES_FULLDUPLEX,
			SPI_NSS_SOFT, 0x07);

	/* SD_SPI enable */
	SPI_Cmd( ENABLE);
}


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
		uint16_t length)
{

	uint16_t time_out= 5000;

	/*!< Wait until the transmit buffer is empty */
	while((!SPI_GetFlagStatus(SPI_FLAG_TXE))&& (--time_out));
	if(!time_out) return 1;

	/* Empty receive buffer */
	if(SPI_GetFlagStatus(SPI_FLAG_RXNE))
	{
		uint8_t temp_data=SPI_ReceiveData();
	}

	/* Enable communication */
	GPIO_WriteLow(CS_PORT,CS_PIN);

	for(uint16_t i=0; i< length; i++)
	{
		SPI_SendData(*(send_data+i));

		if(receive_data != NULL)
		{
			while((!SPI_GetFlagStatus(SPI_FLAG_RXNE))&& (--time_out));
			if(!time_out) return 1;
			*(receive_data+i)=SPI_ReceiveData();
		}
		else
		{
			while((!SPI_GetFlagStatus(SPI_FLAG_TXE))&& (--time_out));
			if(!time_out) return 1;
		}
	}

	/* Disable communication */
	GPIO_WriteHigh(CS_PORT,CS_PIN);
	return 0;
}
