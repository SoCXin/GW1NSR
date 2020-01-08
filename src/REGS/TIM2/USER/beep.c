/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************************

 * �ļ���  ��beep.c
 * ����    ��BEEP���ú�����     
 * ʵ��ƽ̨��iCreate STM8������
 * �Ĵ����汾  ��V1.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 *�޸�ʱ�� ��2011-12-20
  iCreate STM8������Ӳ������


****************************************************************************************/
#include "beep.h"

static uint16_t FLASH_ReadOptionByte(uint16_t Address);
static void FLASH_ProgramOptionByte(uint16_t Address, uint8_t Data);
static void FLASH_WaitForLastOperation(void);







/**************************************************************************
 * ��������Set_Beep_OptionByte
 * ����  ������Beep��ѡ����
 * ����  ����
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� ��Beep���ú�������
 *************************************************************************/
 void Set_Beep_OptionByte(void)
{
  uint16_t Beep_Option_status;/*��¼���ѡ����Beep��״̬*/
  Beep_Option_status=FLASH_ReadOptionByte(Beep_OptionAdd);
  if(!(Beep_Option_status&0x8000))
  {
    FLASH_ProgramOptionByte(Beep_OptionAdd,(uint8_t)((Beep_Option_status|0x8000)>>8));
    /*��Beep_OptionAdd  0x4803 ��1��������Beep*/
  }
}
/**************************************************************************
 * ��������FLASH_ReadOptionByte
 * ����  ����ȡ��ѡ����
 * ����  ����
 *
 * ���  ����
 * ����  ��ѡ���ֵ�ֵ 
 * ����  ���ڲ����� ����Beep��ѡ���ֺ�������
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
 * ��������FLASH_ProgramOptionByte
 * ����  ��FLASH���
 * ����  ��uint16_t Address, uint8_t Data
 *
 * ���  ����
 * ����  ����
 * ����  ���ڲ����� ����Beep��ѡ���ֺ�������
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
 * ��������FLASH_WaitForLastOperation
 * ����  ���ȵ�FLASH������
 * ����  ����
 *
 * ���  ����
 * ����  ����
 * ����  ���ڲ����� FLASH��̺�������
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
/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/