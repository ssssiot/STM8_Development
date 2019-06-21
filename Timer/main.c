#include "stm8s.h"

void main(void)
{
  u32 u32_clk_freq;
  u32_clk_freq = CLK_GetClockFreq();

  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  TIM1_TimeBaseInit(2000,TIM1_COUNTERMODE_UP,1000,0);
  
  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  
  TIM1_ARRPreloadConfig(ENABLE);
  
  __enable_interrupt();
  
  TIM1_Cmd(ENABLE);
  
  while (1);
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
