/*
 * i2c.c
 *
 *  Created on: Jan 14, 2022
 *      Author: Dy
 */

#include "i2c.h"

void Init_I2C2(void)
{    
    if( (RCC->APB1ENR & RCC_APB1ENR_I2C2EN) != RCC_APB1ENR_I2C2EN )
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    I2C2->CR1 = 0x0000;
    I2C2->CR2 = 0x0000;

    I2C2->CR2 |= 8;                 // FREQ[5:0]
    I2C2->TRISE = 0;
    I2C2->CCR = I2C_CCR_FS;
    I2C2->CCR |= 0x28;              // Timing setting

    I2C2->CR1 |= I2C_CR1_PE;
}

void raw_I2C2_Start(void)
{
    I2C2->CR1 |= I2C_CR1_ACK | I2C_CR1_START;
    while( !(I2C2->SR1 & I2C_SR1_SB) );
}

void raw_I2C2_Address(uint8_t addr)
{
    I2C2->DR = addr;
    while( !(I2C2->SR1 & I2C_SR1_ADDR) );

    uint16_t FlagClear = I2C2->SR2;
}

void raw_I2C2_Write(uint8_t data)
{
    while( !(I2C2->SR1 & I2C_SR1_TXE) );
    I2C2->DR = data;
    while( !(I2C2->SR1 & I2C_SR1_BTF) );
}

void raw_I2C2_Stop(void)
{
    I2C2->CR1 |= I2C_CR1_STOP;
}

uint8_t raw_I2C2_Read(void)
{
    uint8_t rtnData;

    I2C2->CR1 &= ~I2C_CR1_ACK;
    while( !(I2C2->SR1 & I2C_SR1_RXNE) );

    rtnData = I2C2->DR;

    return rtnData;
}

void raw_I2C2_ReadMulti(uint8_t *dataArray, uint8_t byteCount)
{
    int count = byteCount;
    uint8_t bufferIndex = 0;

    while(count--)
    {
        if(count == 0)
            I2C2->CR1 &= ~I2C_CR1_ACK;
        while( !(I2C2->SR1 & I2C_SR1_RXNE) );
        dataArray[bufferIndex++] = I2C2->DR;
    }
}

void I2C2_Wrtie(uint8_t addr, uint8_t regAddr, uint8_t data)
{
    raw_I2C2_Start();
    raw_I2C2_Address(addr << 1);
    raw_I2C2_Write(regAddr);
    raw_I2C2_Write(data);
    raw_I2C2_Stop();
}

uint8_t I2C2_Read(uint8_t addr, uint8_t regAddr)
{
    uint8_t rtnData;

    raw_I2C2_Start();
    raw_I2C2_Address(addr << 1);
    raw_I2C2_Write(regAddr);

    raw_I2C2_Start();
    raw_I2C2_Address(addr << 1 | 0x01);
    rtnData = raw_I2C2_Read();
    raw_I2C2_Stop();

    return rtnData;
}

void I2C2_ReadMulti(uint8_t addr, uint8_t regAddr, uint8_t *buffer, uint8_t size)
{
    raw_I2C2_Start();
    raw_I2C2_Address(addr << 1);
    raw_I2C2_Write(regAddr);
    
    raw_I2C2_Start();
    raw_I2C2_Address(addr << 1 | 0x01);
    raw_I2C2_ReadMulti(buffer, size);
    raw_I2C2_Stop();
}