/*
 * main.c
 *
 *  Created on: Jan 09, 2022
 *      Author: Dy
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f1xx.h"
#include "system_stm32f103.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "timer.h"

int main(void)
{
    SystemClockConfig();
    SysTick_Config(64000);

    Init_GPIO();
    EXTI_Init();
    Init_UART3(BPS_2000000);
    Init_UART2(BPS_2000000);
    Init_I2C2();
    Init_TIMER1();
    Init_TIMER2();

    Delay(1);

    printf("Test System start >>> \r\n");

    while(1)
    {
        /* Button */
        if(getSystemState() & SYSTEM_STATE_BUTTON)
        {
            clearSystemState(SYSTEM_STATE_BUTTON);
            printf("Button\r\n");
        }
        DEBUGLED_Toggle();
        Delay(500);
    }

    return 0;
}
