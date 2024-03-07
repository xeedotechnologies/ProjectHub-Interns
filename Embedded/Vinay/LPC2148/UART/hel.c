#include <lpc214x.h>
#include <stdio.h>

void UART_Init() {
    PINSEL0 |= 0x00000005; // Select TXD0 and RXD0 for UART0
    U0LCR = 0x83;           // 8-bit data, 1 stop bit, enable DLAB
    U0DLL = 97;             // Set baud rate to 9600
    U0LCR = 0x03;           // Disable DLAB
}

void UART_SendChar(char ch) {
    while (!(U0LSR & 0x20)); // Wait for UART to be ready to transmit
    U0THR = ch;              // Send character
}

int main() {
	  int i = 0;
	// Send "Hello, World!" over UART
    char msg[] = "Hello, World!\n";
    UART_Init();
    
    while(msg[i] != '\0') {
        UART_SendChar(msg[i]);
        i++;
    }
    
    while(1); // Infinite loop
    return 0;
}
