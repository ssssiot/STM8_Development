#include "stm8s.h"
#include "delay.h"

CLK_Source_TypeDef clk_source;
u32 u32_clk_freq;

void main(void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  delay_init(16);

  clk_source = CLK_GetSYSCLKSource();
  u32_clk_freq = CLK_GetClockFreq();
  
  GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);

  while (1)
  {
    GPIOD->ODR |= GPIO_PIN_1;
    delay_us(10);
    GPIOD->ODR &= (~GPIO_PIN_1);
    delay_us(10);
  }
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
