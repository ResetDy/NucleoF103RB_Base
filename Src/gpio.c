/*
 * gpio.c
 *
 *  Created on: Jan 09, 2022
 *      Author: Dy
 */

#include "gpio.h"

void Init_GPIO(void)
{
    RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN);

    // Nucelo F103RB Debug LED
    // PA5
    GPIOA->CRL &= ~(GPIO_CRL_CNF5);
    GPIOA->CRL |= (GPIO_CRL_MODE5_0);

    // Nucelo F103RB UART2
    // PA3 : Rx
    // PA2 : Tx
    GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_CNF2);
    GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_MODE2);
    GPIOA->CRL |= (GPIO_CRL_CNF3_1 | GPIO_CRL_CNF2_1);
    GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_MODE2_0);
    
    // Nucelo F103RB UART3 (Remap)
    // PC11(Remap) : UART3 Rx
    // PC10(Remap) : UART3 Tx
    AFIO->MAPR &= ~(AFIO_MAPR_USART3_REMAP);        // USART3 Remap
    AFIO->MAPR |= (AFIO_MAPR_USART3_REMAP_0);  
    GPIOC->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_CNF10);
    GPIOC->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_MODE10);
    GPIOC->CRH |= (GPIO_CRH_CNF11_1 | GPIO_CRH_CNF11_0 | GPIO_CRH_CNF10_1);     // PC11(AFOD), PC10(AFPP)
    GPIOC->CRH |= (GPIO_CRH_MODE10_1 | GPIO_CRH_MODE10_0);                      // Speed 2 MHz

    /* I2C2 포트설정 (PB11 : SDA, PB10 : SCL) */
    GPIOB->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_CNF10);
    GPIOB->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_MODE10);
    GPIOB->CRH |= (GPIO_CRH_CNF11_1 | GPIO_CRH_CNF11_0 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF10_0);
    GPIOB->CRH |= (GPIO_CRH_MODE11_0 | GPIO_CRH_MODE10_0);

    // PWM 채널설정 (TIM1 : CH1, PA8)
    GPIOA->CRH &= ~GPIO_CRH_CNF8;
    GPIOA->CRH |= GPIO_CRH_CNF8_1;
    GPIOA->CRH |= (GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0);

    // PWM 채널설정 (TIM2 : CH2, PA1)
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRL |= GPIO_CRL_CNF1_1;
    GPIOA->CRL |= (GPIO_CRL_MODE1_1 | GPIO_CRL_MODE1_0);
}

void EXTI_Init(void)
{
    AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC;       // EXTI Mode
    EXTI->IMR = EXTI_IMR_MR13;                      // IT Mode
    EXTI->RTSR = EXTI_FTSR_TR13;                    // Falling Edge
    EXTI->PR = 0x000FFFFF;                          // Interrupt Pending Bit Clear

    NVIC_SetPriority(EXTI15_10_IRQn, 1);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void DEBUGLED_On(void)
{
    DEBUGLED_ON;
}

void DEBUGLED_Off(void)
{
    DEBUGLED_OFF;
}

void DEBUGLED_Toggle(void)
{
    if(GPIOA->ODR & GPIO_ODR_ODR5)
        DEBUGLED_OFF;
    else
        DEBUGLED_ON;
}

void EXTI15_10_IRQHandler(void)
{
    if(EXTI->PR & EXTI_PR_PR13)
    {
        EXTI->PR |= EXTI_PR_PR13;        // Flag Reset
        setSystemState(SYSTEM_STATE_BUTTON);
    }
}