#include "stm32f4xx.h"

#define LEDDELAY    1000000
int main(void);
void delay(volatile uint32_t);

int main(void)
{
    RCC->AHB1ENR |= 0x00000008;

    GPIOD->MODER &= 0xFCFFFFFF;   
    GPIOD->MODER |= 0x01000000;   

    GPIOD->ODR |= 0x1000;
    while(1)
    {
        delay(LEDDELAY);
        GPIOD->ODR ^= (1U << 12);  // Toggle LED
    }

    __asm("NOP"); // Assembly inline can be used if needed
    return 0;
}

void delay(volatile uint32_t s)
{
    for(; s>0; s--);
}