#include "stm8s.h"
#include "delay.h"

CLK_Source_TypeDef clk_source;
u32 u32_clk_freq;

void main(void)
{
  delay_init(8);
  
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
  
  GPIO_WriteLow(GPIOB, GPIO_PIN_5);

  while (1)
  {
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5);

    delay_ms(100);
    GPIO_WriteLow(GPIOB, GPIO_PIN_5);

    delay_ms(100);
  }
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
