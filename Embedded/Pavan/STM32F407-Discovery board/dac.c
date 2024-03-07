#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

int main(void);

int main(void)
{
    uint32_t dac_value = 0xD00;
    int32_t i = 0;

    RCC->AHB1ENR |= (1 << 0);

    GPIOA->MODER &= 0xFFFFFCFF;
    GPIOA->MODER |= 0x00000300;

    RCC->APB1ENR |= (1 << 29);

    DAC->CR |= (1 << 0);
    DAC->CR |= (0 << 1);
    DAC->CR |= (1 << 2);
    DAC->CR |= (7 << 3);

    DAC->DHR12R1 = dac_value;
    DAC->SWTRIGR |= (1 << 0); // trigger ch1

    while(1)
    {
        dac_value += 0x10;
        DAC->DHR12R1 = dac_value;
        DAC->SWTRIGR |= (1 << 0 ); // trigger ch1
        for (i=0; i<1000; i++);
    }

    return 0;
}
