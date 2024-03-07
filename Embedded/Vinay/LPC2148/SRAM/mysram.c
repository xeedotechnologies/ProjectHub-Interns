#include <lpc214x.h>

#define BAUD_RATE 9600
#define SRAM_BASE_ADDRESS 0x40000000

void initUART() {
    // Initialize UART0 with baud rate
    PINSEL0 |= 0x00000005; // Enable UART0 Rx and Tx pins
    U0LCR = 0x83;           // 8 bits, 1 stop bit, Enable DLAB
    U0DLM = 0x00;           // For baud rate 9600 with Pclk = 15MHz
    U0DLL = 0x61;           // 9600 baud rate
    U0LCR = 0x03;           // 8 bits, 1 stop bit, DLAB = 0
}

void initSRAM() {
    // No specific initialization needed for SRAM on LPC2148
    // SRAM is memory-mapped and should be ready for use
}

void writeToSRAM(char *data, int len) {
    char *sram_ptr = (char *)SRAM_BASE_ADDRESS;
    int i;
    for (i = 0; i < len; i++) {
        *sram_ptr++ = data[i];
    }
}

void transmitDataUART(char *data, int len) {
    int i;
    for (i = 0; i < len; i++) {
        while (!(U0LSR & 0x20)); // Wait for UART transmit holding register empty
        U0THR = data[i];
    }
}

int main() {
    char data[] = "AAAA";
    int len = sizeof(data) - 1; // excluding null terminator

    initUART();
    initSRAM();

    writeToSRAM(data, len);
    transmitDataUART(data, len);

    while (1); // Endless loop
    return 0;
}
