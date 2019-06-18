#include "stm8s.h"

void main(void)
{
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  while (1);
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
