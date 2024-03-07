#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include <math.h>

#define PWMPERIOD 100
#define SAMPLE 100

int main(void);

void TIM4_IRQHandler(void)
{
    static uint32_t t = 0;
    static uint16_t duty = 0;

    if (TIM4->DIER & 0x01) {
        if (TIM4->SR & 0x01) {
            TIM4->SR &= ~(1U << 0);
        }
    }

    duty =(uint16_t)(PWMPERIOD/2.0 * (sin(2*M_PI*(double)t/(SAMPLE)) + 1.0));
    ++t;
    if (t == SAMPLE) t = 0;
    TIM4->CCR1 = duty;
}

int main(void)
{
    RCC->AHB1ENR |= (1 << 3);
    GPIOD->MODER |= (0x2 << 24);
    GPIOD->AFR[1] |= (0x2 << 16);
    RCC->APB1ENR |= (1 << 2);

    TIM4->PSC = 8399;
    TIM4->ARR = PWMPERIOD;
    TIM4->CCR1 = 1;

    TIM4->CCMR1 |= (0x6 << 4);
    TIM4->CCMR1 |= (1 << 3);
    TIM4->CCER |= (1 << 0);
    TIM4->DIER |= (1 << 0);

    NVIC_SetPriority(TIM4_IRQn, 2);
    NVIC_EnableIRQ(TIM4_IRQn);

    TIM4->CR1 |= (1 << 0);

    while(1)
    {
        // Do nothing.
    }

    return 0;
}
