#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

int main(void);
void dummy_function(volatile uint32_t s);

void WWDG_IRQHandler(void)
{
    for (;;);
}

int main(void)
{
    RCC->AHB1ENR |= (1 << 3);

    GPIOD->MODER &= 0x00FFFFFF;
    GPIOD->MODER |= 0x55000000;
    // flash all LEDs to demonstrate a reset
    GPIOD->ODR |= 0xF000;
    dummy_function(10000000);
    GPIOD->ODR = 0x0000;
    RCC->APB1ENR |= (1 << 11);
    WWDG->CFR |= (0x2 << 7);
    WWDG->CFR |= (0x70);
    WWDG->CR |= (0xFF);


    // blink an LED ten times to show the operation
    for (int i=0; i<20; i++){
        GPIOD->ODR ^= 0x8000;  // Toggle blue LED
        for (int j=0; j<10; j++){
            dummy_function(100000);
            WWDG->CR |= (0x7F);
        }
    }

    while(1)
    {
        dummy_function(1000);
        GPIOD->ODR ^= 0x1000;  // Toggle green LED
    }

    return 0;
}

void dummy_function(volatile uint32_t s)
{
    for (s;s>0;s--);
}
