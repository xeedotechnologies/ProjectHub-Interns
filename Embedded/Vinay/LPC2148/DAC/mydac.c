#include <LPC21xx.H>                            /* LPC21xx definitions */

extern long volatile timeval;

#define	uchar unsigned char
#define uint unsigned int

#define RS	24	  
#define RW	25	  
#define Elcm 26	

#define busy	0x0800

unsigned char const mcu123[]="OBSERVE THE RAMP"	;
unsigned char const mcu124[]="AT DAC O/P      " ;


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

void Sent_Byte1(unsigned char data)
{
unsigned char n;

for(n=0;n<8;n++) 
  {
    if(data&1) {Io_Set(n+16);}	 
   else {Io_Clr(n+16);}
   data=data>>1;
   }
} 

 void Sent_Byte3(unsigned char data)
{
unsigned char n;

for(n=7;n<=0;n--) 
  {
    if(data&1) {Io_Set(n+16);}	 
   else {Io_Clr(n+16);}
   data=data>>1;
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




int main (void)  {
  unsigned char k,i,data;                               /* LED var */

  IODIR1 = 0xFFFF0000;    // P1.16-->P1.26 as o/p used in LCD*/
  IODIR0 = 0xFFFFFF00;    // P0.16-->P0.23 as o/p used in DAC*/
   IOSET0=0x80000000;	//make buzzer OFF
  
   init_timer();
	 delayms(1);
	 lcdreset();		
	 delay1s(1);
	 disp(0,0,mcu123);
	 disp(0,1,mcu124);

  while (1) 
   {                                  
	for(k=0;k<=255;k++)
	{
  		
		//k=0x73;
		//Sent_Byte1(k);
		data=k;
		if(data&1) 
			{Io_Set(23);}	 
   		else 
			{Io_Clr(23);}

   		data=data>>1;
		if(data&1) 
			{Io_Set(22);}	 
   		else 
			{Io_Clr(22);}


   		data=data>>1;
		if(data&1) 
			{Io_Set(21);}	 
   		else 
			{Io_Clr(21);}

   		data=data>>1;
		if(data&1) 
			{Io_Set(20);}	 
   		else 
			{Io_Clr(20);}

   		data=data>>1;
		if(data&1) 
			{Io_Set(19);}	 
   		else 
			{Io_Clr(19);}

   		data=data>>1;
		if(data&1) 
			{Io_Set(18);}	 
   		else 
			{Io_Clr(18);}

   		data=data>>1;
		if(data&1) 
			{Io_Set(17);}	 
   		else 
			{Io_Clr(17);}

   		data=data>>1;
		if(data&1) 
			{Io_Set(16);}	 
   		else 
			{Io_Clr(16);}


  	}
   }
}
