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

## **- Active Peripheral -** <br>
### **_GPIO_**
>LED : PA5   
Button : PC13 (EXTI)

### **_USART2_**
>BPS : 2Mbps   
Rx : PA3   
Tx : PA2   

### **_USART3_**
>BPS : 2Mbps   
Rx : PC11 (Remap)   
Tx : PC10 (Remap)   

### **_I2C2_**
>Speed : FM (400Khz)   
SDA : PB11   
SCL : PB10   

### **_TIM1_**
>Mode : PWM1   
Period : 50Hz   
CH1 : PA8   
CH2 : -   
CH3 : -   
CH4 : -   

### **_TIM2_**
>Mode : PWM1   
Period : 20KHz   
CH1 : -   
CH2 : PA1   
CH3 : -   
CH4 : -   

<br>

## **- Function -** <br>
### **_TimeMeasure_**
- 시간을 us 단위로 측정하는 함수 ex)1500 = 1500us   
    >_void_ TimeMeasureStart(_void_) : 측정 시작   
    _uint32_t_ TimeMeasureEnd(_void_) : 측정 종료   

    ```C
    uint32_t time;

    TimeMeasureStart();
    printf("Hello World!!!\r\n");
    time = TimeMeasureEnd();

    printf("%d\r\n", time);
    ```