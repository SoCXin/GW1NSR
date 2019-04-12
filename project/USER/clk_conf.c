
#include "clk_conf.h"

void Clk_conf(void)
{
  CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
  CLK_CKDIVR|= (uint8_t)0x00;/*设置时钟为内部16M高速时钟*/
  
}
