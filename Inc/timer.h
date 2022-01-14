/*
 * timer.h
 *
 *  Created on: Jan 14, 2022
 *      Author: Dy
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f1xx.h"

#define TIM1_PRESCALE       32
#define TIM1_PERIOD         40000       // ((1 / (64Mhz / TIM1_PRESCALE)) * TIM1_PERIOD = Period Time(sec)
#define TIM2_PRESCALE       2
#define TIM2_PERIOD         1600

void Init_TIMER1(void);
void Init_TIMER2(void);

#endif /* TIMER_H_ */