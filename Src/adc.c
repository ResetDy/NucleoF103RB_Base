/*
 * gpio.c
 *
 *  Created on: Jan 09, 2022
 *      Author: Dy
 */

#include "adc.h"
#include "dma.h"

uint32_t ADC_Value[8];
uint32_t MeasureTime;
uint16_t CalValue;

void Init_ADC(void)
{
    if( (RCC->APB2ENR & RCC_APB2ENR_ADC1EN) != RCC_APB2ENR_ADC1EN )
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->CR1 = 0x00000000;
    ADC1->CR2 = 0x00000000;
    ADC1->SMPR2 = 0x00000000;
    ADC1->SQR1 = 0x00000000;
    ADC1->SQR3 = 0x00000000;

    setDMA_Channel_Count(2);
    setDMA_MemoryAddress((uint32_t)ADC_Value);
    setDMA_PeripheralAddress((uint32_t)&ADC1->DR);

    ADC1->SMPR2 |= ADC_SMPR2_SMP1_2 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP0_2 | ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_0;
    ADC1->SQR1 = ADC_SQR1_L_0;                      // 0001 = 2 conversions
    ADC1->SQR3 |= ADC_SQR3_SQ2_0;                   // ADC Sequence Channel Select

    ADC1->CR1 |= ADC_CR1_SCAN;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_DMA | ADC_CR2_ADON;

    ADC1->CR2 |= ADC_CR2_CAL;    
    while(ADC1->CR2 & ADC_CR2_CAL);
    CalValue = ADC1->DR;   
    
    ADC1->CR2 |= ADC_CR2_ADON;
}

uint16_t getADC(uint8_t channel) { return ADC_Value[channel]; }