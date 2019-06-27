#include "stm8s.h"
#include "delay.h"
#include "SHT20.h"

float temp;

void main(void)
{
  delay_init(16);
  
  UART1_DeInit();

  UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  
  UART1_Cmd(ENABLE); 
  
  SHT2x_Init();
  while (1)
  {
    temp = SHT2x_MeasureTempHM();
    temp = SHT2x_MeasureHumiHM();
    delay_ms(50);
  }
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
