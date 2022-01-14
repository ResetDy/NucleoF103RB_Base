# Nucleo F103RB Base Source

## **- System Setup -**
### **_Clock_**
>HSI (RC oscillator)   
System Frequency : 64 MHz   
HPRE : 64 MHz   
APB1 : 32 MHz   
APB2 : 64 MHz   
SysTick : 1ms (64000)

<br>
<br>



## **- Active Peripheral -** <br>

<br>


### **_GPIO_**
>LED : PA5   
Button : PC13 (EXTI)

<br>


### **_USART2_**
>BPS : 2Mbps   
Rx : PA3   
Tx : PA2   

<br>


### **_USART3_**
>BPS : 2Mbps   
Rx : PC11 (Remap)   
Tx : PC10 (Remap)   

<br>


### **_I2C2_**
>Speed : FM (400Khz)   
SDA : PB11   
SCL : PB10   

<br>


### **_TIM1_**
>Mode : PWM1   
Period : 50Hz   
CH1 : PA8   
CH2 : -   
CH3 : -   
CH4 : -   

<br>


### **_TIM2_**
>Mode : PWM1   
Period : 20KHz   
CH1 : -   
CH2 : PA1   
CH3 : -   
CH4 : -   

