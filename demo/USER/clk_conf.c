
#include "clk_conf.h"

void Clk_conf(void)
{
  CLK_CKDIVR&= (uint8_t)(~0x18);/*ʹ���ڲ�ʱ��*/
  CLK_CKDIVR|= (uint8_t)0x00;/*����ʱ��Ϊ�ڲ�16M����ʱ��*/
  
}
