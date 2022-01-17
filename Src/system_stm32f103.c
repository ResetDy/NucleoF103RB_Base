/*
 * system_stm32f103.c
 *
 *  Created on: Jan 09, 2022
 *      Author: Dy
 */

#include "stm32f1xx.h"
#include "system_stm32f103.h"

__IO uint32_t sysTick;
__IO uint32_t SystemStateFlag;
__IO uint32_t TimeMeasure_Before;

#ifdef __GNUC__
int __io_putchar(int ch)
#else
int fputc(int ch, FILE *f)
#endif
{
    USART2->DR = *(uint8_t *) &ch & 0xFF;
    while( !(USART2->SR & USART_SR_TC) );
    return ch;
}

void SystemInit(void)
{
    /* HSION bit 활성화 */
    RCC->CR |= RCC_CR_HSION;		// 0x00000001

    /* MCO, ADCPRE, PPRE2, PPRE1, HPRE, SW bit 초기화 */
    RCC->CFGR &= ~(RCC_CFGR_MCO | RCC_CFGR_ADCPRE | RCC_CFGR_PPRE2 | RCC_CFGR_PPRE1 | RCC_CFGR_HPRE | RCC_CFGR_SWS | RCC_CFGR_SW);	// 0xF8FF0000

    /* PLLON, CSSON, HSEON bit 초기화 */
    RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSON | RCC_CR_HSEON);		// 0xFEF6FFFF

    /* HSEBYP bit 초기화 */
    RCC->CR &= ~(RCC_CR_HSEBYP);		// 0xFFFBFFFF

    /* USBPRE/OTGFSPRE, PLLMUL, PLLXTPRE, PLLSRC 초기화 */
    RCC->CFGR &= ~(RCC_CFGR_USBPRE | RCC_CFGR_PLLMULL | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC);		// 0xFF80FFFF

    /* 모든 인터럽트 요청비트 초기화 */
    RCC->CIR = (RCC_CIR_CSSC | RCC_CIR_PLLRDYC | RCC_CIR_HSERDYC | RCC_CIR_HSIRDYC | RCC_CIR_LSERDYC | RCC_CIR_LSIRDYC);	// 0x009F0000
}


void SystemClockConfig(void)
{
    // FLASH Latency 2로 설정
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_1;

    /* HSION 비트 활성화 및 대기 */
    RCC->CR |= RCC_CR_HSION;
    while( (RCC->CR & RCC_CR_HSIRDY) == 0);		// HSION 비트를 활성화 했을때, 정상으로 작동하면 HSIRDY 비트가 1로 Set 됨

    /* PLL 설정 */
    RCC->CR &= ~RCC_CR_PLLON;					// PLL OFF
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;				// PLL 소스선택 (0 : HSI의 /2, 1 : HSE)
    RCC->CFGR |= RCC_CFGR_PLLMULL16;			// PLL 체배값 설정
    RCC->CR |= RCC_CR_PLLON;					// PLL ON
    while( (RCC->CR & RCC_CR_PLLRDY) == 0);		// PLL 비트 활성화 이후, 정상적으로 작동할때까지 대기해준다.

    /* HCLK, APB1, APB2 라인에 사용할 Clock 분배를 지정 */
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

    /* SYSCLK로 사용할 소스(System Clock Mux)로 PLL 선택 및 대 */
    RCC->CFGR |= RCC_CFGR_SW_1;
    while( (RCC->CFGR & RCC_CFGR_SWS) == 0);

}

uint32_t getSystemState(void)
{
    return SystemStateFlag;
}

void setSystemState(uint32_t flag)
{
    SystemStateFlag |= flag;
}

void clearSystemState(uint32_t clearFlag)
{
    SystemStateFlag &= ~clearFlag;
}

uint32_t getSysTick(void)
{
    return sysTick;
}

uint32_t getSysTickDetail(void)
{
    uint32_t tickVal = SysTick->VAL;

    return tickVal;
}

uint32_t getSysTime_us(void)
{
    uint32_t currentUs = getSysTickDetail();
    uint32_t currentMs = getSysTick();	
    uint32_t rtnValue;

    rtnValue = (currentMs * 1000) + ((64000 - currentUs) >> 6);

    return rtnValue;
}

void TimeMeasureStart(void)
{
    TimeMeasure_Before = getSysTime_us();
}

uint32_t TimeMeasureEnd(void)
{
    uint32_t curTime = getSysTime_us();
    uint32_t rtnValue;
    
    rtnValue = curTime - TimeMeasure_Before;

    return rtnValue;
}

void Delay(uint32_t ms)
{
    uint32_t startTick = getSysTime_us();
    uint32_t target = startTick + ms * 1000;

    while( target >= getSysTime_us() );
}

void SysTick_Handler(void)		// Config 값에 따라 인터럽트 주기를 변경 할 수 있음
{
    sysTick++;
}