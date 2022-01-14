/*
 * i2c.h
 *
 *  Created on: Jan 14, 2022
 *      Author: Dy
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f1xx.h"
#include "system_stm32f103.h"

void Init_I2C2(void);
void raw_I2C2_Start(void);
void raw_I2C2_Address(uint8_t addr);
void raw_I2C2_Write(uint8_t data);
void raw_I2C2_Stop(void);
uint8_t raw_I2C2_Read(void);
void raw_I2C2_ReadMulti(uint8_t *dataArray, uint8_t byteCount);

void I2C2_Wrtie(uint8_t addr, uint8_t regAddr, uint8_t data);
uint8_t I2C2_Read(uint8_t addr, uint8_t regAddr);
void I2C2_ReadMulti(uint8_t addr, uint8_t regAddr, uint8_t *buffer, uint8_t size);

#endif /* I2C_H_ */