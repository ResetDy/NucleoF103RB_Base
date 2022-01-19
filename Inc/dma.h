/*
 * adc.h
 *
 *  Created on: Jan 18, 2022
 *      Author: Dy
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f1xx.h"
#include "system_stm32f103.h"

void Init_DMA(void);
void setDMA_Channel_Count(uint16_t count);
void setDMA_PeripheralAddress(uint32_t address);
void setDMA_MemoryAddress(uint32_t address);

#endif /* DMA_H_ */