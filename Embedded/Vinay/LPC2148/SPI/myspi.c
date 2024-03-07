#include <lpc214x.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>


#define RS	24	  
#define RW	25	  
#define Elcm 26	

#define busy	0x0800

#define	uchar unsigned char
#define uint unsigned int


//extern long volatile timeval;
int timeval;
unsigned char const mcu123[]=" MASTER SEND "	;
unsigned char const mcu124[]=" i =         " ;

unsigned char const mcu125[]=" SLAVE RECIEVED ";

void Io_Set(uchar pin)
{
unsigned int io_data=1;
io_data=io_data<<pin;
IOSET0=io_data;        
}


void Io_Clr(uchar pin)
{
unsigned int io_data=1;
io_data=io_data<<pin;
IOCLR0=io_data;        
}

void Io_Set1(uchar pin)
{
unsigned int io_data=1;
io_data=io_data<<pin;
IOSET1=io_data;        
}


void Io_Clr1(uchar pin)
{
unsigned int io_data=1;
io_data=io_data<<pin;
IOCLR1=io_data;      
}


void Sent_Byte(unsigned char data)
{
unsigned char i;
for(i=0;i<8;i++) 
  {
  
   if(data&1) {Io_Set1(i+16);}	 
   else {Io_Clr1(i+16);}
   data=data>>1;
   }
}

void Sent_Byte2(unsigned char data)
{
unsigned char n;

for(n=0;n<8;n++) 
  {
    if(data&1) {Io_Set(n+16);}	 
   else {Io_Clr(n+16);}
   data=data>>1;
   }
}



void delay(unsigned int i)
{
	unsigned int k=1000;
	while(i>0)
	{
		i--;
	}
	while(k>1)k--;
}

void delayms (unsigned int i) {                        /* Delay function */
unsigned int n;
while(i>1)
{
	for(n=65535;n>1;n--);
	i--;
}
}

void	delay1s(unsigned char i)
{
	while(i>1)
	{
		i--;
		delayms(20);
	}
}




void WaitForEnable( void ) {

	//unsigned int i;
	
	Io_Clr1(RS);
	delay(1);
	Io_Set1(RW);
	delay(1);
	Io_Set1(Elcm);
	delayms(10);
	//	i=IO1PIN;		//¶ÁP1	
	while( IO1PIN & busy );
	Io_Clr1(Elcm);
}	


void LcdWrite_CMD( uchar CMD,uchar AttribC ) {

	if (AttribC) WaitForEnable();				
	
	Io_Clr1(RS);
	delay(1);
	Io_Clr1(RW);
	delay(1);
	Sent_Byte(CMD);
	Io_Set1(Elcm);
	delay(1);
	delay(1);
	Io_Clr1(Elcm);
	delay(1);
}


void LcdWrite_D( char dataW ) {

	WaitForEnable();						

	Io_Set1(RS);
	delay(1);
	Io_Clr1(RW);
	delay(1);
	Sent_Byte(dataW);
	Io_Set1(Elcm);
	delay(1);
	Io_Clr1(Elcm);
	delay(1);


}


void LocateXY( char posx,char posy) {

uchar temp;

	temp = posx & 0xf;
	posy &= 0x1;
	if ( posy )temp |= 0x40;
	temp |= 0x80;
	LcdWrite_CMD(temp,0);
}



void DispOneChar(uchar x,uchar y,uchar Wdata) {

	LocateXY( x, y );				
	LcdWrite_D( Wdata );			
}

void disp(uchar x,uchar y,const unsigned char *ptr) {
uchar i,l=0;
	while (ptr[l] >31){l++;};
	for (i=0;i<l;i++) {
		DispOneChar(x++,y,ptr[i]);
		if ( x == 16 ){
			x = 0; y ^= 1;
		}
	}
}

 void disp1(uchar x,uchar y,const unsigned char ptr) {


		DispOneChar(x++,y,ptr);
		
		}

void lcdreset(void)
{
	LcdWrite_CMD(0x38, 0);		
	delayms(50);
	LcdWrite_CMD(0x38, 0);
	delayms(50);
	LcdWrite_CMD(0x38, 0);
	delayms(50);
	
	LcdWrite_CMD( 0x38, 1);
	LcdWrite_CMD( 0x08, 1);
	LcdWrite_CMD( 0x01, 1);
	LcdWrite_CMD( 0x06, 1);
	LcdWrite_CMD( 0x0f, 1);
	
}
void wait (void)  {                             /* wait function */
  unsigned long i;

  i = timeval;
  while ((i +10 ) != timeval);                  /* wait 100ms */
}

void SPI_Init()
{
	PINSEL0 = PINSEL0 | 0x00001500; /* Select P0.4, P0.5, P0.6, P0.7 as SCK0, MISO0, MOSI0 and GPIO */
	S0SPCR = 0x0020; /* SPI Master mode, 8-bit data, SPI0 mode */
	S0SPCCR = 0x10; /* Even number, minimum value 8, pre scalar for SPI Clock */
}

void SPI_Write(char data)
{
	char flush;
	IO0CLR = (1<<7);  /* SSEL = 0, enable SPI communication with slave */
	S0SPDR = data;  /* Load data to be written into the data register */
	while ( (S0SPSR & 0x80) == 0 );  /* Wait till data transmission is completed */
	flush = S0SPDR;
	IO0SET = (1<<7);  /* SSEL = 1, disable SPI communication with slave */
}

char SPI_Read()
{
	IO0CLR = (1<<7);  /* SSEL = 0, enable SPI communication with slave */
	S0SPDR = 0xFF;  /* Transmit Flush byte */
	while ( (S0SPSR & 0x80) == 0 );  /* Wait till data transmission is completed */
	IO0SET = (1<<7);  /* SSEL = 1, disable SPI communication with slave */
	return S0SPDR;  /* Return the data received */
}

int main(void)
{
	int i,j,kk1;

	unsigned char  transmit[7];
 	IODIR1=0xFFFF0000;	 // P1.16-->P1.26 as o/p used in LCD
	i = 0;
	j = 0;
	kk1=0	;
	memset(transmit,0,7);
 	//IODIR0=0x40FFFF10; 	 // P0.16-->P0.23 as o/p used in LED

 
 //   init_timer();

 
	 delayms(1);
	 lcdreset();		
	 delay1s(1);
	 disp(0,0,mcu123);
	 disp(0,1,mcu124);

	SPI_Init();
	//LCD_String("Master send");
	SPI_Write(0x01);
	for(i=0;i<10;i++)
	{
		//sprintf(transmit,"i = %d",i);	
		if(i>9)
			kk1=i+0x37;	
		else
			kk1=i+0x30;

		disp1(6,1,kk1);
		while(transmit[j] != 0)
		{			
			SPI_Write(transmit[j]);
			delayms(100);
			j++;
		}
		SPI_Write('\0');

		memset(transmit,0,7);
			delayms(100);
		j = 0;
	}
	 	lcdreset();		
	 	delay1s(1);
	 	disp(0,0,mcu125);

	return 0;
}
