#include <LPC214x.h>
#include <stdlib.h>
#include <stdio.h> // Include for printf function

#define PCLK            12000000        // Define the peripheral clock frequency
#define BAUD_RATE       9600            // Define the UART baud rate

void UART_Init() {
    PINSEL0 |= 0x00000005;              // Enable RxD0 and TxD0 functionality for UART0
    U0LCR = 0x83;                       // 8-bit data, 1 stop bit, Enable DLAB
    U0DLM = (PCLK / (16 * BAUD_RATE)) / 256;
    U0DLL = (PCLK / (16 * BAUD_RATE)) % 256;
    U0LCR = 0x03;                       // Disable DLAB
}

void UART_SendChar(char ch) {
    while (!(U0LSR & 0x20));            // Wait until U0THR and U0TSR are both empty
    U0THR = ch;                         // Load the character to be transmitted into U0THR
}

void UART_SendString(const char *str) {
    while (*str != '\0') {              // Loop until end of string
        UART_SendChar(*str);             // Send each character
        str++;                          // Move to the next character
    }
}

int main() {
    unsigned int rand_value;
    char buffer[20];
    int i;
	
    UART_Init();                        // Initialize UART
    srand(10);                         // Seed the random number generator

    while (1) {
        rand_value = rand();            // Generate pseudo-random number using standard library function
        sprintf(buffer, "Random number: %d\r\n", rand_value); // Format the random number as a string
        UART_SendString(buffer);        // Send the random number via UART
        for (i = 0; i < 1000000; i++); // Delay before generating the next random number
    }
    return 0;
}
