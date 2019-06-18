#include "stm8s.h"

CLK_Source_TypeDef clk_source;
u32 u32_clk_freq;

void main(void)
{
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_MANUAL, CLK_SOURCE_LSI, ENABLE, CLK_CURRENTCLOCKSTATE_DISABLE);

  clk_source = CLK_GetSYSCLKSource();
  u32_clk_freq = CLK_GetClockFreq();
  
  while (1);
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
