/*
 * adc.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Dy
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f1xx.h"
#include "system_stm32f103.h"

void Init_ADC(void);
uint16_t getADC(uint8_t channel);

#endif /* ADC_H_ */