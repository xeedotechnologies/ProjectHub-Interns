#include <LPC21xx.H>                            /* LPC21xx definitions */

extern long volatile timeval;

#define	uchar unsigned char
#define uint unsigned int

#define RS	24	  
#define RW	25	  
#define Elcm 26	

#define EOC 8

#define p16 16
#define p17 17
#define p18 18
#define p19 19
#define p20 20
#define p21 21
#define p22 22
#define p23 23

#define busy	0x0800

unsigned char const mcu123[]=" ADC VALUE =    "	;
							 


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

unsigned char asc_code(unsigned char j)
        {

           if (j>9)
               j=j+0x37;
           else
               j=j+0x30;

		   return j ;
        }



int main (void)  {
  
  unsigned char i,dat1,dat2,j;
  unsigned int k;
  IODIR1 = 0xFFFF0000;  // P1.16-->P1.26 as o/p used in LCD
						  // P0.16-->P0.23 as i/p & P0.9(SOC),P0.10,P0.11,P0,12(I/P SELECTION) as o/p
	IODIR0 = 0xFF00FE00;	// P0.8 as i/p (EOC)used in ADC					
 	IOSET0=0x80000000;	//make buzzer OFF
  	init_timer();
	delayms(1);
	lcdreset();		
	delay1s(1);
	disp(0,0,mcu123);
  while (1) 
   {                                  
	
					//P0.8       -EOC
					//P0.9       -SOC
					//P0.10,P0.11,P.12 -SLC0,SLCT1,SLCT2
					
		dat2=0x02;
		Sent_Byte1(dat2);		//WR 1-0-1 ,Select channel-0
		wait();
		dat2=dat2 & 0xFD;
		Sent_Byte1(dat2);
		wait();
		dat2=dat2 | 0x02;
		Sent_Byte1(dat2);


	wait();
	wait();
	wait();
	wait();

//up1:		k=IOPIN0;
//		if((k&1<<EOC)==0x00000100) goto dwn1;//data1=data1 || 0x02;	
//	 	goto up1;
	

dwn1:		//dat2=dat2 & 0xFE;
		//Sent_Byte1(dat2);		   //RD low

								//Here Data Lines are Ulta connected
								//READ THE DATA 

		k=IOPIN0;
		if((k&1<<p16)==0x010000) 
		{
			dat1=0X80;
		}
		else
		{
			dat1=0;
		}				   
		
		k=IOPIN0;
		if((k&1<<p17)==0x020000) 
		{
			dat1=dat1 | 0x40;
		}
		else
		{
			dat1=dat1 | 0x00;
		}				   

		
		k=IOPIN0;
		if((k&1<<p18)==0x040000) 
		{
			dat1=dat1 | 0x20;
		}
		else
		{
			dat1=dat1 | 0x00;
		}				   

		k=IOPIN0;	
		if((k&1<<p19)==0x080000)
		{
			dat1=dat1 | 0x10;
		}
		else
		{
			dat1=dat1 | 0x00;
		}				   

		
		k=IOPIN0;		
		if((k&1<<p20)==0x100000)
		{
			dat1=dat1 | 0x08;
		}
		else
		{
			dat1=dat1 | 0x00;
		}				   

		

		k=IOPIN0;
		if((k&1<<p21)==0x200000)
		{
			dat1=dat1 | 0x04;
		}
		else
		{
			dat1=dat1 | 0x00;
		}				   

		
		k=IOPIN0;		
		if((k&1<<p22)==0x400000)
		{
			dat1=dat1 | 0x02;
		}
		else
		{
			dat1=dat1 | 0x00;
		}				   

		
		k=IOPIN0;		
		if((k&1<<p23)==0x800000)
		{
			dat1=dat1 | 0x01;
		}
		else
		{
			dat1=dat1 | 0x00;
		}				   
	
	//dat2=dat2 | 0x01;
	//Sent_Byte1(dat2);			 //RD HIGH

		 //dat1=0x76;
		j=dat1 & 0xf0;
		j=j>>4;
		j=asc_code(j);
		disp1(13,0,j);

		j=dat1 & 0x0f;
		j=asc_code(j);
		disp1(14,0,j);

		

   }
}
