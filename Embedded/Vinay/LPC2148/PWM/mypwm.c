#include <LPC21xx.h> 

void pwm_init(void)
{
PINSEL0 = 0X8002 ;
PWMPCR= 0X600;
PWMMR0=150000;
PWMTCR=0X09; 
PWMMCR=0X02;
}
int main (void)
{
pwm_init(); 

while(1)
{
PWMMR1=75000; 
PWMMR2=90000;

PWMLER=0x6;
}
}