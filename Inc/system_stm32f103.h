/*
 * sytem_stm32f103.h
 *
 *  Created on: Aug 20, 2020
 *      Author: doyun
 */

#ifndef SYSTEM_STM32F103_H_
#define SYSTEM_STM32F103_H_

#include <stdio.h>

#define SYSTEM_CLOCK_MHZ                        64
#define SYSTICK_1SEC                            (SYSTEM_CLOCK_MHZ * 1000000)
#define SYSTICK_100MS                           (SYSTEM_CLOCK_MHZ * 100000)
#define SYSTICK_10MS                            (SYSTEM_CLOCK_MHZ * 10000)
#define SYSTICK_1MS                             (SYSTEM_CLOCK_MHZ * 1000)
#define SYSTICK_100US                           (SYSTEM_CLOCK_MHZ * 100)
#define SYSTICK_10US                            (SYSTEM_CLOCK_MHZ * 10)
#define SYSTICK_1US                             (SYSTEM_CLOCK_MHZ)

#define SYSTEM_STATE_BUTTON                     0x00000001

void SystemClockConfig(void);
uint32_t getSystemState(void);
void setSystemState(uint32_t flag);
void clearSystemState(uint32_t clearFlag);
uint32_t getSysTick(void);
uint32_t getSysTickDetail(void);
uint32_t getSysTime_us(void);
void TimeMeasureStart(void);
uint32_t TimeMeasureEnd(void);
void Delay(uint32_t ms);
void Delay_us(uint16_t us);

#endif /* SYSTEM_STM32F103_H_ */
