#include "stm32f4xx.h"
int main (void) {
int result;

RCC->AHB1ENR |= 0x00000008;
GPIOD->MODER |= 0x04000000;

RCC->AHB1ENR |= 1;
GPIOA->MODER |= 0xC;
RCC->APB2ENR |= 0x00000100;
ADC1->CR2 = 0;
ADC1->SQR3 = 1;
ADC1->SQR1 = 0;
ADC1->CR2 |= 1; /* enable ADC1 */

while (1) {
	ADC1->CR2 |= 0x40000000;
	while(!(ADC1->SR & 2)) {}
	result = ADC1->DR;
	if (result & 0x100)
		GPIOD->BSRRL = 0x00002000; /* turn on LED */
	else
		GPIOD->BSRRH = 0x2000; /* turn off LED */
	}
}
