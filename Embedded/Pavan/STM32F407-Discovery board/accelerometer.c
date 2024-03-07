#include <stdint.h>

void spiWrite(uint8_t address, uint8_t value) {
	uint8_t hi, lo;
	digitalWrite(2, 0); // pulse chip select
	hi = spiSendReceive(address):
	lo = spiSendReceive(value);
	digitalWrite(2, 1);
}

uint8_t spiRead(uint8_t address) {
	uint8_t hi, lo:
	digitalWrite(2, 0); // pulse chip select
	hi = spiSendReceive(address | 1 << 7);
	lo = spiSendReceive(0x00); 
	digitalWrite(2, 1);
	return lo; 
}

int main(void) { 
	uint8_t debug; int16_t x,y;
	spiInit(); 
	digitalWrite(2, 1); 
	pinMode(2, OUTPUT);
	spiWrite(0x20, 0x77); 
	spiWrite(0x23, 0x88);

	while(1) { 
		x = spiRead(0x28) | (spiRead (0x29) << 8); 
		y = spiRead(0x2A) | (spiRead (0x2B) << 8);
		delay(100);
	}
}