/*
 * uart.h
 *
 *  Created on: Jan 09, 2022
 *      Author: Dy
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f1xx.h"
#include "system_stm32f103.h"

#define APH1_CLK             32000000
#define BPS_4800             (APH1_CLK / (16 * 4800))
#define BPS_9600             (APH1_CLK / (16 * 9600))
#define BPS_19200            (APH1_CLK / (16 * 19200))
#define BPS_38400            (APH1_CLK / (16 * 38400))
#define BPS_57600            (APH1_CLK / (16 * 57600))
#define BPS_76800            (APH1_CLK / (16 * 76800))
#define BPS_115200           (APH1_CLK / (16 * 115200))
#define BPS_230400           (APH1_CLK / (16 * 230400))
#define BPS_250000           (APH1_CLK / (16 * 250000))
#define BPS_500000           (APH1_CLK / (16 * 500000))
#define BPS_1000000          (APH1_CLK / (16 * 1000000))
#define BPS_2000000          (APH1_CLK / (16 * 2000000))

void Init_UART1(uint16_t baud);
void Init_UART2(uint16_t baud);
void Init_UART3(uint16_t baud);

void UART2_tx(uint8_t character);
void UART2_msg(char *msg);
uint8_t UART2_rx(void);

void UART3_tx(uint8_t character);
void UART3_msg(char *msg);
uint8_t UART3_rx(void);

#endif /* UART_H_ */