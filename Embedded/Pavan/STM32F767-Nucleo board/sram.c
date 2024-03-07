#include "stm32f7xx.h"  // Device header


// PD8 for USART3 TX


void uart3_transmit_char(char c) {
    while (!(USART3->ISR & USART_ISR_TXE));
    USART3->TDR = (c & (uint16_t)0x01FF);
}


void uart3_transmit_string(const char *str) {
    while (*str) {
        uart3_transmit_char(*str++);
    }
}


int main(void) {
    // Define SRAM address
    uint32_t *sram_address = (uint32_t *)0x20000000;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= GPIO_MODER_MODER8_1;
    #define AF07 0x07
    GPIOD->AFR[1] |= (AF07 << 0);

    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    USART3->BRR = 0x008B; // Baud rate 115200 @16MHz
    USART3->CR1 = 0;
    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_UE;

    *sram_address = 0xAAAAA;

    while(1) {
        // Check if SRAM address equals 0xAAAAA
        if (*sram_address == 0xAAAAA) {
            uart3_transmit_string("Data in SRAM: 0x");
            // Transmit the hexadecimal value without using sprintf
            for (int i = 28; i >= 0; i -= 4) {
                // Extract each nibble and transmit it as ASCII character
                uint8_t nibble = (*sram_address >> i) & 0xF;
                if (nibble < 10) {
                    uart3_transmit_char('0' + nibble);
                } else {
                    uart3_transmit_char('A' + (nibble - 10));
                }
            }
            uart3_transmit_string("\r\n");
        } else {
            uart3_transmit_string("Error: Random data in SRAM\r\n");
        }

        for (volatile int i = 0; i < 100000; i++);
    }
}
