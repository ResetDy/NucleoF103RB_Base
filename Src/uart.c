/*
 * uart.h
 *
 *  Created on: Jan 09, 2022
 *      Author: Dy
 */

#include "uart.h"

void Init_UART1(uint16_t baud)
{
    // UART1 GPIO 설정 필요
    if( (RCC->APB2ENR & RCC_APB2ENR_USART1EN) != RCC_APB2ENR_USART1EN )
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    USART1->CR1 = 0x0000;
    USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    USART1->BRR = baud << 4;

    USART1->CR1 |= USART_CR1_UE;
}

void Init_UART2(uint16_t baud)
{
    if( (RCC->APB1ENR & RCC_APB1ENR_USART2EN) != RCC_APB1ENR_USART2EN )
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    USART2->CR1 = 0x0000;
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    USART2->BRR = baud << 4;
	
    USART2->CR1 |= USART_CR1_UE;
}

void Init_UART3(uint16_t baud)
{
    if( (RCC->APB1ENR & RCC_APB1ENR_USART3EN) != RCC_APB1ENR_USART3EN )
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    USART3->CR1 = 0x0000;
    USART3->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    USART3->BRR = baud << 4;
	
    USART3->CR1 |= USART_CR1_UE;
}

void UART2_tx(uint8_t character)
{
    USART2->DR = character;
    while( !(USART2->SR & USART_SR_TXE) );
}

void UART2_msg(char *msg)
{
    while(*msg) { UART2_tx( *(msg++) ); }
}

uint8_t UART2_rx(void)
{
    uint8_t tmp;

    while( !(USART2->SR & USART_SR_RXNE) );
    tmp = USART2->DR;
    
    return tmp;
}

void UART3_tx(uint8_t character)
{
    USART3->DR = character;
    while( !(USART3->SR & USART_SR_TXE) );
}

void UART3_msg(char *msg)
{
    while(*msg) { UART3_tx( *(msg++) ); }
}

uint8_t UART3_rx(void)
{
    uint8_t tmp;

    while( !(USART3->SR & USART_SR_RXNE) );
    tmp = USART3->DR;
    
    return tmp;
}