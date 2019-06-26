#include "SHT20.h"
#include "string.h"
#include "SHT20.h"
#include "stdio.h"
#include "delay.h"

SHT2x_PARAM g_sht2x_param;

void SHT2x_Delay(unsigned int n)
{
    delay_us(n); 
    delay_us(n);
    delay_us(n);delay_us(n);delay_us(n);
}

void SHT2x_Init(void)
{ 
    GPIO_Init(SHT2x_I2C_PORT, SHT2x_SDA_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_Init(SHT2x_I2C_PORT, SHT2x_SCL_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
    
    SHT2x_SCL_HIGH();
    SHT2x_SDA_HIGH();
    
    SHT2x_Delay(80);

    SHT2x_SoftReset();
}

void SHT2x_SCL_OUTPUT(void)
{
    GPIO_Init(SHT2x_I2C_PORT, SHT2x_SCL_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
}

/*void SHT2x_SCL_INPUT(void)
{
    
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_FL_No_IT);
  
  
}*/

void SHT2x_SDA_OUTPUT(void)
{
    GPIO_Init(SHT2x_I2C_PORT, SHT2x_SDA_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
  
}

void SHT2x_SDA_INPUT(void)
{
   GPIO_Init(SHT2x_I2C_PORT, SHT2x_SDA_PIN, GPIO_MODE_IN_FL_NO_IT);
}

void SHT2x_I2cStartCondition(void)
{
   
    SHT2x_SDA_OUTPUT();
    
    SHT2x_SDA_HIGH();
    SHT2x_SCL_HIGH();
    SHT2x_SDA_LOW();
    SHT2x_Delay(30);
    SHT2x_SCL_LOW();
    SHT2x_Delay(30);
}

void SHT2x_I2cStopCondition(void)
{
   
    SHT2x_SDA_OUTPUT();
    
    SHT2x_SDA_LOW();
    SHT2x_SCL_LOW();
    SHT2x_SCL_HIGH();
    SHT2x_Delay(30);
    SHT2x_SDA_HIGH();
    SHT2x_Delay(30);
}

void SHT2x_I2cAcknowledge(void)
{
  
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_LOW();
    
    SHT2x_SCL_HIGH();
    SHT2x_Delay(8);
    SHT2x_SCL_LOW();   
    SHT2x_Delay(8);
}

void SHT2x_I2cNoAcknowledge(void)
{  
    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    SHT2x_SCL_HIGH();
    SHT2x_Delay(8);
    SHT2x_SCL_LOW();   
    SHT2x_Delay(8);
}

unsigned char SHT2x_I2cReadByte(void)
{
    unsigned char i, val = 0;

    SHT2x_SDA_OUTPUT();
    
    SHT2x_SDA_INPUT();
        
    for(i = 0; i < 8; i++)
    {
        val <<= 1; 
        
        SHT2x_SCL_HIGH();   
        
        if(SET == SHT2x_SDA_STATE()) 
        {
            val |= 0x01;
        }
        
        SHT2x_SCL_LOW();    
    }

    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    return (val);
}

unsigned char SHT2x_I2cWriteByte(unsigned char byte)
{
    unsigned char i, ack;

    SHT2x_SDA_OUTPUT();
    SHT2x_SCL_OUTPUT();
    
    
    for(i = 0; i < 8; i++)
    {
        if(byte & 0x80) 
        {
            SHT2x_SDA_HIGH();
        }
        else 
        {
            SHT2x_SDA_LOW();
        }
        
        SHT2x_SCL_HIGH();
        SHT2x_Delay(20);
        SHT2x_SCL_LOW();   
        SHT2x_Delay(20);
        
        byte <<= 1;
    }

    SHT2x_SDA_INPUT();
    
    SHT2x_SCL_HIGH();
    
    if(SET == SHT2x_SDA_STATE()) 
    {
        ack = ACK_ERROR;
    }
    else
    {
        ack = ACK_OK;
    }
    
    SHT2x_SCL_LOW();  

    SHT2x_SDA_OUTPUT();

    SHT2x_SDA_HIGH();
    
    return (ack);
}

float SHT2x_MeasureTempHM(void)
{
    float TEMP;
    unsigned char tmp1, tmp2;
    unsigned short ST;
    

    SHT2x_SCL_OUTPUT();
    
    SHT2x_I2cStartCondition();                            
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_TEMP_MEASUREMENT_HM);

    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_R);

    SHT2x_SCL_HIGH();

    while(RESET == SHT2x_SCL_STATE())
    {
        SHT2x_Delay(20);
    }
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    ST = (tmp1 << 8) | (tmp2 << 0);
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;

    SHT2x_SCL_OUTPUT();

    return (TEMP);	  
}

float SHT2x_MeasureHumiHM(void)
{
    float HUMI;
    unsigned char tmp1, tmp2;    
    unsigned short SRH;


    SHT2x_SCL_OUTPUT();
    
    SHT2x_I2cStartCondition();                               
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_HUMI_MEASUREMENT_HM);

    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_R);

    SHT2x_SCL_HIGH();


    while(RESET == SHT2x_SCL_STATE())
    {
        SHT2x_Delay(20);
    }
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    SHT2x_SCL_OUTPUT();

    return (HUMI);
}

float SHT2x_MeasureTempPoll(void)
{
    float TEMP;
    unsigned short ack, tmp1, tmp2;
    unsigned short ST;
    SHT2x_I2cStartCondition();                            
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_TEMP_MEASUREMENT_POLL);
    do 
    {
        delay_ms(40);     
        SHT2x_I2cStartCondition();
        ack = SHT2x_I2cWriteByte(I2C_ADR_R);
    } while(ACK_ERROR == ack);
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();

    ST = (tmp1 << 8) | (tmp2 << 0);    
    ST &= ~0x0003;   
    TEMP = ((float)ST * 0.00268127) - 46.85;   
    return (TEMP);
    	  
}

float SHT2x_MeasureHumiPoll(void)
{
    float HUMI;
    unsigned char ack, tmp1, tmp2;    
    unsigned short SRH;

    
    SHT2x_I2cStartCondition();                               
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(TRIG_HUMI_MEASUREMENT_POLL);
    
    do {
        delay_ms(40);
        SHT2x_I2cStartCondition();
        ack = SHT2x_I2cWriteByte(I2C_ADR_R);
    } while(ACK_ERROR == ack);
    
    tmp1 = SHT2x_I2cReadByte();
    SHT2x_I2cAcknowledge();
    tmp2 = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    return (HUMI);
}

unsigned char SHT2x_ReadUserReg(void)    
{
    unsigned char reg;

    
    SHT2x_I2cStartCondition();                 
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(USER_REG_R);
    SHT2x_I2cStartCondition(); 
    SHT2x_I2cWriteByte(I2C_ADR_R);
    reg = SHT2x_I2cReadByte();
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
    
    return (reg); 
}

unsigned char SHT2x_WriteUserReg(unsigned char reg)
{
    unsigned char ack;

    
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(USER_REG_W);
    ack = SHT2x_I2cWriteByte(reg);
    SHT2x_I2cStopCondition();  
    
    return (ack);
}

void SHT2x_SoftReset(void)
{
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W);
    SHT2x_I2cWriteByte(SOFT_RESET);
    SHT2x_I2cStopCondition();

    SHT2x_Delay(80);
}

void SHT2x_GetSerialNumber(unsigned char *buf)
{
    /* Read from memory location 1 */
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W); //I2C address
    SHT2x_I2cWriteByte(0xFA); //Command for readout on-chip memory
    SHT2x_I2cWriteByte(0x0F); //on-chip memory address
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_R); //I2C address
    buf[5] = SHT2x_I2cReadByte(); //Read SNB_3
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); //Read CRC SNB_3 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[4] = SHT2x_I2cReadByte(); //Read SNB_2
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); //Read CRC SNB_2 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[3] = SHT2x_I2cReadByte(); //Read SNB_1
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); //Read CRC SNB_1 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[2] = SHT2x_I2cReadByte(); //Read SNB_0
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); //Read CRC SNB_0 (CRC is not analyzed)
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();

    /* Read from memory location 2 */
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_W); //I2C address
    SHT2x_I2cWriteByte(0xFC); //Command for readout on-chip memory
    SHT2x_I2cWriteByte(0xC9); //on-chip memory address
    SHT2x_I2cStartCondition();
    SHT2x_I2cWriteByte(I2C_ADR_R); //I2C address
    buf[1] = SHT2x_I2cReadByte(); //Read SNC_1
    SHT2x_I2cAcknowledge();
    buf[0] = SHT2x_I2cReadByte(); //Read SNC_0
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); //Read CRC SNC0/1 (CRC is not analyzed)
    SHT2x_I2cAcknowledge();
    buf[7] = SHT2x_I2cReadByte(); //Read SNA_1
    SHT2x_I2cAcknowledge();
    buf[6] = SHT2x_I2cReadByte(); //Read SNA_0
    SHT2x_I2cAcknowledge();
    SHT2x_I2cReadByte(); //Read CRC SNA0/1 (CRC is not analyzed)
    SHT2x_I2cNoAcknowledge();
    SHT2x_I2cStopCondition();
}

void SHT2x_Test(void)
{   
    g_sht2x_param.TEMP_HM = SHT2x_MeasureTempHM();
    g_sht2x_param.HUMI_HM = SHT2x_MeasureHumiHM();

    g_sht2x_param.TEMP_POLL = SHT2x_MeasureTempPoll();
    g_sht2x_param.HUMI_POLL = SHT2x_MeasureHumiPoll();
    
    SHT2x_GetSerialNumber(g_sht2x_param.SerialNumber);
}
