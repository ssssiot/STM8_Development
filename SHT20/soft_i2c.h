#ifndef _SOFT_I2C_H_
#define _SOFT_I2C_H_

#define         GPIO_I2C        GPIOD

#define         SDA_PIN         GPIO_PIN_1
#define         SCL_PIN         GPIO_PIN_2      

#define         SET_SDA         GPIO_I2C->ODR |= SDA_PIN;
#define         SET_SCL         GPIO_I2C->ODR |= SCL_PIN;

#define         CLR_SDA         GPIO_I2C->ODR &= (~SDA_PIN);
#define         CLR_SCL         GPIO_I2C->ODR &= (~SCL_PIN);

#define         SDA_STATUS      GPIO_ReadInputPin(GPIO_I2C, SDA_PIN)

typedef enum{
  ACK                      = 0,
  NO_ACK                   = 1,
}I2C_ACK_TYPE;

void I2c_Init ();

void I2C_OutputMode();

void I2C_StartCondition ();

void I2C_StopCondition ();

unsigned char I2C_WriteByte (unsigned char txByte);

unsigned char I2C_ReadByte (I2C_ACK_TYPE ack);

#endif