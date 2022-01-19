/*
 * dma.c
 *
 *  Created on: Jan 18, 2022
 *      Author: Dy
 */

#include "dma.h"

uint32_t PeripheralAddress;
uint32_t MemoryAddress;
uint32_t MemoryCount;

void Init_DMA(void)
{
    if( (RCC->AHBENR & RCC_AHBENR_DMA1EN) != RCC_AHBENR_DMA1EN )
        RCC->AHBENR |= RCC_AHBENR_DMA1EN;    
    
    DMA1_Channel1->CCR = DMA_CCR_PL_0 | DMA_CCR_MSIZE_1 | DMA_CCR_PSIZE_1 | DMA_CCR_MINC | DMA_CCR_TCIE | DMA_CCR_CIRC;
    DMA1_Channel1->CNDTR = MemoryCount;
    DMA1_Channel1->CPAR = PeripheralAddress;
    DMA1_Channel1->CMAR = MemoryAddress;
    DMA1_Channel1->CCR |= DMA_CCR_EN;

    NVIC_SetPriority(DMA1_Channel1_IRQn, 1);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);  
}

void setDMA_Channel_Count(uint16_t count) { MemoryCount = count; }
void setDMA_PeripheralAddress(uint32_t address) { PeripheralAddress = address; }
void setDMA_MemoryAddress(uint32_t address) { MemoryAddress = address; }

void DMA1_Channel1_IRQHandler(void)
{
    DMA1->IFCR |= DMA_IFCR_CGIF1;
    setSystemState(SYSTEM_STATE_ADC);
}