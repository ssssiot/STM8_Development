#include "stm8s.h"

void UART1_SendChar(uint8_t c)
{
    UART1->DR = c;
    while( UART1_GetFlagStatus(UART1_FLAG_TC)==RESET );
}

void UART1_SendString(uint8_t * str)
{
    while(*str)
    {
        UART1->DR = *str++;
        while( UART1_GetFlagStatus(UART1_FLAG_TC)==RESET );
    }
}

void main(void)
{
    UART1_DeInit();

    UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  
    UART1_Cmd(ENABLE);

    enableInterrupts();
  
    UART1_SendChar('*');
  
    UART1_SendString("SSSSIOT");
  
    while(1);
}

void assert_failed(u8* file, u32 line)
{ 
    while (1);
}
