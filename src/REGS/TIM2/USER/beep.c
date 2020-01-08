/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ***************************

 * 文件名  ：beep.c
 * 描述    ：BEEP配置函数库     
 * 实验平台：iCreate STM8开发板
 * 寄存器版本  ：V1.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 *修改时间 ：2011-12-20
  iCreate STM8开发板硬件连接


****************************************************************************************/
#include "beep.h"

static uint16_t FLASH_ReadOptionByte(uint16_t Address);
static void FLASH_ProgramOptionByte(uint16_t Address, uint8_t Data);
static void FLASH_WaitForLastOperation(void);







/**************************************************************************
 * 函数名：Set_Beep_OptionByte
 * 描述  ：设置Beep的选项字
 * 输入  ：无
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 供Beep配置函数调用
 *************************************************************************/
 void Set_Beep_OptionByte(void)
{
  uint16_t Beep_Option_status;/*记录激活备选功能Beep的状态*/
  Beep_Option_status=FLASH_ReadOptionByte(Beep_OptionAdd);
  if(!(Beep_Option_status&0x8000))
  {
    FLASH_ProgramOptionByte(Beep_OptionAdd,(uint8_t)((Beep_Option_status|0x8000)>>8));
    /*向Beep_OptionAdd  0x4803 置1，激活了Beep*/
  }
}
/**************************************************************************
 * 函数名：FLASH_ReadOptionByte
 * 描述  ：读取的选项字
 * 输入  ：无
 *
 * 输出  ：无
 * 返回  ：选项字的值 
 * 调用  ：内部调用 设置Beep的选项字函数调用
 *************************************************************************/
static uint16_t FLASH_ReadOptionByte(uint16_t Address)
{
    uint8_t value_optbyte, value_optbyte_complement = 0;
    uint16_t res_value = 0;
    value_optbyte = *((NEAR uint8_t*)Address); /* Read option byte */
    value_optbyte_complement = *(((NEAR uint8_t*)Address) + 1); /* Read option byte complement */


        if (value_optbyte == (uint8_t)(~value_optbyte_complement))
        {
            res_value = (uint16_t)((uint16_t)value_optbyte << 8);
            res_value = res_value | (uint16_t)value_optbyte_complement;
        }
        else
        {
            res_value = FLASH_OPTIONBYTE_ERROR;
        }
    return(res_value);
}
/**************************************************************************
 * 函数名：FLASH_ProgramOptionByte
 * 描述  ：FLASH编程
 * 输入  ：uint16_t Address, uint8_t Data
 *
 * 输出  ：无
 * 返回  ：无
 * 调用  ：内部调用 设置Beep的选项字函数调用
 *************************************************************************/
static void FLASH_ProgramOptionByte(uint16_t Address, uint8_t Data)
{
  /* Enable write access to option bytes */
  FLASH_CR2 |= MASK_FLASH_CR2_OPT;
  FLASH_NCR2 &= (uint8_t)(~MASK_FLASH_NCR2_NOPT );
  /* Program option byte and his complement */
  *((NEAR uint8_t*)Address) = Data;
  *((NEAR uint8_t*)((uint16_t)(Address + 1))) = (uint8_t)(~Data);
  FLASH_WaitForLastOperation();
  /* Disable write access to option bytes */
  FLASH_CR2 &= (uint8_t)(~MASK_FLASH_CR2_OPT);
  FLASH_NCR2 |= MASK_FLASH_NCR2_NOPT;
}
/**************************************************************************
 * 函数名：FLASH_WaitForLastOperation
 * 描述  ：等到FLASH编程完毕
 * 输入  ：无
 *
 * 输出  ：无
 * 返回  ：无
 * 调用  ：内部调用 FLASH编程函数调用
 *************************************************************************/
static void FLASH_WaitForLastOperation(void)
{
    uint8_t flagstatus = 0x00;
    uint32_t timeout = OPERATION_TIMEOUT;
    while ((flagstatus == 0x00) && (timeout != 0x00))
        {
            flagstatus = (uint8_t)(FLASH_IAPSR & (uint8_t)(MASK_FLASH_IAPSR_EOP  |
                                              MASK_FLASH_IAPSR_WR_PG_DIS));
            timeout--;
        }
    
}
/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/