/*
 * sytem_stm32f103.h
 *
 *  Created on: Aug 20, 2020
 *      Author: doyun
 */

#ifndef SYSTEM_STM32F103_H_
#define SYSTEM_STM32F103_H_

#include <stdio.h>

void SystemClockConfig(void);
uint32_t getSysTick(void);
void Delay(uint32_t ms);


#endif /* SYSTEM_STM32F103_H_ */
