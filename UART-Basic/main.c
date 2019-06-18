#include "stm8s.h"

void main(void)
{
  UART1_DeInit();

  UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  
  UART1_Cmd(ENABLE);
  
  UART1_SendData8('*');
}

void assert_failed(u8* file, u32 line)
{ 
  while (1);
}
