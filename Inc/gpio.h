/*
 * gpio.h
 *
 *  Created on: Jan 09, 2022
 *      Author: Dy
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f1xx.h"
#include "system_stm32f103.h"

#define DEBUGLED_ON         (GPIOA->BSRR |= GPIO_BSRR_BS5)
#define DEBUGLED_OFF        (GPIOA->BRR |= GPIO_BRR_BR5)

void Init_GPIO(void);
void DEBUGLED_On(void);
void DEBUGLED_Off(void);
void DEBUGLED_Toggle(void);

#endif /* GPIO_H_ */