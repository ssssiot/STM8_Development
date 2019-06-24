#include "stm8s.h"
#include "delay.h"
#include "soft_i2c.h"

CLK_Source_TypeDef clk_source;
u32 u32_clk_freq;

void main(void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  delay_init(16);

  clk_source = CLK_GetSYSCLKSource();
  u32_clk_freq = CLK_GetClockFreq();
  
  GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);

  while (1)
  {
    I2C_StartCondition();
    delay_ms(100);
    I2C_WriteByte (128);
    delay_ms(20);
    I2C_WriteByte (0xFE);  
    delay_ms(100);
    I2C_StopCondition();
    delay_ms(500);
  }
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
