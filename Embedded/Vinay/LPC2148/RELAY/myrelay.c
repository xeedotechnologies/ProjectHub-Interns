#include <LPC21xx.H>                            /* LPC21xx definitions */


extern long volatile timeval;

#define	uchar unsigned char
#define uint unsigned int

#define RS	24	  
#define RW	25	  
#define Elcm 26	

#define KEY1 20
#define KEY2 21
#define KEY3 22
#define KEY4 23

#define busy	0x0800

unsigned char const mcu123[]="RL1-OFF  RL2-OFF";


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
    if(data&1) {Io_Set(n+8);}	 
   else {Io_Clr(n+8);}
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


  unsigned char Scan_Key(void)
{
	unsigned int k,key,j;
	unsigned char ab1;

//   for (j = 0x00010000; j <= 0x00080000; j <<= 1) { 
//      IOSET0 = j;                             
//		}  	


	ab1=0;
	key=0;
   	
	j=0x00010000;		
	IOSET0=j;	
	j=0x00020000;		
	IOSET0=j;	
	j=0x00040000;		
	IOSET0=j;	
	j=0x00080000;		
	IOCLR0=j;	
	k=IOPIN0;
	if((k&1<<KEY4)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY3)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY2)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY1)==0)key+=1;
	key=key<<1;

	j=0x00010000;		
	IOSET0=j;	
	j=0x00020000;		
	IOSET0=j;	
	j=0x00040000;		
	IOCLR0=j;	
	j=0x00080000;		
	IOSET0=j;	
	k=IOPIN0;
	if((k&1<<KEY4)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY3)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY2)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY1)==0)key+=1;
	key=key<<1;

	j=0x00010000;		
	IOSET0=j;	
	j=0x00020000;		
	IOCLR0=j;	
	j=0x00040000;		
	IOSET0=j;	
	j=0x00080000;		
	IOSET0=j;	
	k=IOPIN0;
	if((k&1<<KEY4)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY3)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY2)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY1)==0)key+=1;
	key=key<<1;

	j=0x00010000;		
	IOCLR0=j;	
	j=0x00020000;		
	IOSET0=j;	
	j=0x00040000;		
	IOSET0=j;	
	j=0x00080000;		
	IOSET0=j;	
	k=IOPIN0;
	if((k&1<<KEY4)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY3)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY2)==0)key+=1;
	key=key<<1;
	if((k&1<<KEY1)==0)key+=1;
	key=key<<1;

	switch(key)
	{	
	
	case 0x10000:	
		ab1=4; 
		break;	
	case 0x8000:	
		ab1=3; 
		break;
	case 0x4000:	
		ab1=2; 
		break;
	case 0x2000:	
		ab1=1; 	
		break;

	case 0x1000:
		ab1=8; 
		break;
	case 0x800:
		ab1=7; 
		break;
	case 0x400:	
		ab1=6; 
		break;	
	case 0x200:
		ab1=5; 
		break;

	case 0x100:
		ab1=0X13; 
		break;
  	case 0x80:
		ab1=0x12; 
		break;
	case 0x40:
		ab1=0x11; 
		break;
	case 0x20:
		ab1=9; 
		break;

	case 0x10:
		ab1=0; 
		break;
  	case 0x8:
		ab1=0x16; 
		break;
	case 0x4:
		ab1=0x15; 
		break;
	case 0x2:
		ab1=0x14; 
		break;



	default:
		ab1=0x0d;
		break;
	}
	return ab1;
}	   


int main (void)  
{
    unsigned char i,ab1;

  		IODIR1 = 0xFFFF0000;   // P1.16-->P1.26 as o/p used in LCD ,P0.24,P0.25,P0.26 CONTROL LINES
  							 
		IODIR0 = 0xFF0FFF01; 	//& P0.29,P0.30 as o/p used in relay  
		 IOSET0=0x80000000;	//make buzzer OFF

  	init_timer();
		delayms(1);
		lcdreset();		
		delay1s(1);
		disp(0,0,mcu123);



while(1)
	{

slf1:	ab1=Scan_Key();				// ab1==0x0d i.e. no key has
		if(ab1==0x0d)  goto slf1;	// been pressed.
			  
		switch(ab1)
		{
			case(1):
				IOSET0=0XA0000000;			  //Keep P0.31 high to make Buzzer OFF
				disp1(4,0,'O');
				disp1(5,0,'N');
				disp1(6,0,' ');
				break;
			case(2):
				IOSET0=0XC0000000;
				disp1(13,0,'O');
				disp1(14,0,'N');
				disp1(15,0,' ');
				break;
			case(3):
				IOCLR0=0X20000000;
				disp1(4,0,'O');
				disp1(5,0,'F');
				disp1(6,0,'F');
				break;
			case(4):
				IOCLR0=0X40000000;
				disp1(13,0,'O');
				disp1(14,0,'F');
				disp1(15,0,'F');
				break;
		}
	}
}
							
							







