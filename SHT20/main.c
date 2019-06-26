#include "stm8s.h"
#include "delay.h"
#include "SHT20.h"

float temp;

void main(void)
{
  
  delay_init(16);
  
SHT2x_Init();
  while (1)
  {
    temp = SHT2x_MeasureTempPoll();
    delay_ms(500);
  }
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
