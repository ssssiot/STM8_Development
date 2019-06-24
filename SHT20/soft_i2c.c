#include "stm8s.h"
#include "delay.h"
#include "soft_i2c.h"

void I2c_Init ()
{
  SET_SDA;
  SET_SCL;
}

void I2C_OutputMode()
{
  GPIO_Init(GPIO_I2C, SDA_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIO_I2C, SCL_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}

void I2C_InputMode()
{
  GPIO_Init(GPIO_I2C, SDA_PIN, GPIO_MODE_IN_FL_NO_IT);
}

void I2C_StartCondition ()
{
  SET_SDA;
  SET_SCL;
  delay_ms(5); 
  CLR_SDA;
  delay_ms(5); 
  CLR_SCL;
  delay_ms(5);
}

void I2C_StopCondition ()
{
  CLR_SDA;
  CLR_SCL;
  delay_ms(5); 
  SET_SCL;
  delay_ms(5); 
  SET_SDA;
  delay_ms(5);
}

unsigned char I2C_WriteByte (unsigned char txByte)
{
  unsigned char mask,error=0;
  
  for (mask=0x80; mask>0; mask>>=1)   //shift bit for masking (8 times)
  { 
    if ((mask & txByte) == 0) 
    {
      CLR_SDA;  //masking txByte, write bit to SDA-Line
    }
      
    else
    {
      SET_SDA;
    }
      
    delay_ms(1);             //data set-up time (t_SU;DAT)
    SET_SCL;                         //generate clock pulse on SCL
    delay_ms(5);             //SCL high time (t_HIGH)
    CLR_SCL;
    delay_ms(1);             //data hold time(t_HD;DAT)
  }
  SET_SDA;                           //release SDA-line
  SET_SCL;                           //clk #9 for ack
  delay_ms(1);               //data set-up time (t_SU;DAT)
  //if(SDA_CONF==HIGH) 
  //  error=ACK_ERROR;            //check ack from i2c slave
  CLR_SCL;
  delay_ms(20);              //wait time to see byte package on scope
  
  return error;                       //return error code
}

unsigned char I2C_ReadByte (I2C_ACK_TYPE ack)
{
  unsigned char mask,rxByte=0;
  //SDA=HIGH;                           //release SDA-line
  I2C_InputMode();
  for (mask=0x80; mask>0; mask>>=1)   //shift bit for masking (8 times)
  { 
    SET_SCL;                         //start clock on SCL-line
    delay_ms(1);             //data set-up time (t_SU;DAT)
    delay_ms(3);             //SCL high time (t_HIGH)
    if (SDA_STATUS==1) 
    {
      rxByte=(rxByte | mask); //read bit
    }
    CLR_SCL;
    delay_ms(1);             //data hold time(t_HD;DAT)
  }
  
  I2C_OutputMode();
  if( ack==1 )//send acknowledge if necessary
  {
    SET_SDA;
  }
  else
  {
    CLR_SDA;
  }
                              
  delay_ms(1);               //data set-up time (t_SU;DAT)
  SET_SCL;                           //clk #9 for ack
  delay_ms(5);               //SCL high time (t_HIGH)
  CLR_SCL;
  SET_SDA;                           //release SDA-line
  delay_ms(20);              //wait time to see byte package on scope
  return rxByte;                      //return error code
}