/*
 * timer.c
 *
 *  Created on: Jan 14, 2022
 *      Author: Dy
 */

#include "timer.h"

// APB1 : 64 Mhz (APB1 버스는 최대 32 Mhz 이지만 TIM의 경우 APB1 프리스캐일1 외에는 x2 로 동작하여 64MHz이다. RM0008 p126참고)
// APB2 : 64 Mhz
// PSC : 16 Bit

void Init_TIMER1(void)
{
    if( (RCC->APB2ENR & RCC_APB2ENR_TIM1EN) != RCC_APB2ENR_TIM1EN )
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    TIM1->CR1 = 0x0000;
    TIM1->CR2 = 0x0000;
    TIM1->CCMR1 = 0x0000;
    TIM1->CCER = 0x0000;

    TIM1->PSC = TIM1_PRESCALE - 1;
    TIM1->ARR = TIM1_PERIOD - 1;

    TIM1->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);       // Output Compare PWM1 Mode
    TIM1->CR2 = TIM_CR2_OIS1;                                  // Output Idle State
    //TIM1->CCER = TIM_CCER_CC1E;                              // 왜 아웃풋 설정을 하면 출력이 안나오는가?

    TIM1->CCR1 = 0;    

    TIM1->CR1 |= TIM_CR1_CEN;
}

void Init_TIMER2(void)
{
    if( (RCC->APB1ENR & RCC_APB1ENR_TIM2EN) != RCC_APB1ENR_TIM2EN )
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    
    TIM2->CR1 = 0x0000;
    TIM2->CR2 = 0x0000;
    TIM2->CCMR1 = 0x0000;
    TIM2->CCER = 0x0000;

    TIM2->PSC = TIM2_PRESCALE - 1;      
    TIM2->ARR = TIM2_PERIOD - 1;

    TIM2->CCMR1 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
    TIM2->CR2 = TIM_CR2_OIS2;
    TIM2->CCER = TIM_CCER_CC2E;

    TIM2->CCR2 = 0;

    TIM2->CR1 |= TIM_CR1_CEN;
}