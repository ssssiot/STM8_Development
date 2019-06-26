#include "delay.h"

volatile u8 fac_us=0; 


void delay_init(u8 clk)
{
    if(clk>16)
        fac_us=(16-4)/4;
    else if(clk>4)
        fac_us=(clk-4)/4; 
    else 
        fac_us=1;
}

void delay_us(u16 nus)
{  
    __asm(
    "PUSH A          \n"  
    "DELAY_XUS:      \n"   
    "LD A,fac_us     \n"   
    "DELAY_US_1:     \n"  
    "NOP             \n"  
    "DEC A           \n"  
    "JRNE DELAY_US_1 \n" 
    "NOP             \n" 
    "DECW X          \n" 
    "JRNE DELAY_XUS  \n"   
    "POP A           \n" 
); 
} 
void delay_ms(u32 nms)
{
    u8 t;
    if(nms>65)
    {
        t=nms/65;
        while(t--)
            delay_us(65000);
        nms=nms%65;
    }
    delay_us(nms*1000);
}
