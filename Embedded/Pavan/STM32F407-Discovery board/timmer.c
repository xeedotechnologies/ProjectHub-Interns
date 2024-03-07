#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

int main(void);

void TIM2_IRQHandler(void)
{
    static uint32_t i = 1;

    if (TIM2->DIER & 0x01) {
        if (TIM2->SR & 0x01) {
            TIM2->SR &= ~(1U << 0);
        }
    }

    GPIOD->ODR = (i << 12);

    if (i == 0x08) {
        i = 1;
    }
    else {
        i = (i << 1);
    }
}

int main(void)
{
    RCC->AHB1ENR |= (1 << 3);
    GPIOD->MODER &= 0x00FFFFFF;
    GPIOD->MODER |= 0x55000000;
    GPIOD->ODR = 0;
    RCC->APB1ENR |= (1 << 0);
    TIM2->PSC = 8399;
    TIM2->ARR = 10000;

    TIM2->DIER |= (1 << 0);

    NVIC_SetPriority(TIM2_IRQn, 2);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= (1 << 0);

    while(1)
    {
        // Do nothing.
    }

    return 0;
}
