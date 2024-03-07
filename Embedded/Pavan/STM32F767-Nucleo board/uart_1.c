#include "stm32f7xx.h"                  // Device header

//PD8 for USART3 TX

void uart3_write(unsigned char x)
{

USART3->TDR =(x);
while(!((USART3->ISR)&USART_ISR_TC)){;}
}

int main(void)
	{

		//Configure GPIOD PD8 as TX pin
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
		GPIOD->MODER|=GPIO_MODER_MODER8_1;
		#define AF07 0x07
		GPIOD->AFR[1]|=(AF07<<0);

		//Configure the UART

		RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
		USART3->BRR    = 0x008B; // baud rate 115200 @16MHz
		USART3->CR1    = 0; // Enable Tx and Rx and Enable USART3
		USART3->CR1|=USART_CR1_TE; //enbale TX
		USART3->CR1|=USART_CR1_UE;

	while(1)
	{
		uart3_write('a');
		uart3_write('\r');
		uart3_write('\n');
		for(volatile int i=0;i<100000;i++);

	}


	}
