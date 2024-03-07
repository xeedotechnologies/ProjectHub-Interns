#include "stm32f4xx.h"
#define ARM_MATH_CM4

void GPIO_Init(void);
void TIM2_us_Delay(uint32_t delay); //TIM2 for generating 10us pulse for trig pin

uint32_t data;
double time,dist;


void GPIO_Init(){
    RCC->AHB1ENR |= 1; 
    GPIOA->MODER |= 1<<10; 
    GPIOA->MODER &= ~(0x00003000); 
}


void TIM2_us_Delay(uint32_t delay){
    RCC->APB1ENR |=1;    
    TIM2->ARR = (int)(delay/0.0625); 
    TIM2->CNT = 0;
    TIM2->CR1 |= 1;
    while(!(TIM2->SR & TIM_SR_UIF)){} 
    TIM2->SR &= ~(0x0001); 
}


int main(){
    RCC->CFGR |= 0<<10; 
    GPIO_Init();
    GPIOA->BSRR = 0x00000000; 

    while(1){
        GPIOA->BSRR &= 0x00000000; 
        TIM2_us_Delay(2);
        GPIOA->BSRR |= 0x00000020;
        TIM2_us_Delay(10);
        GPIOA->BSRR |= 0x00200000;

        while (GPIOA->IDR & 64){
            data = data+1;
        }

        if (data>0){
            time = data*(0.0625*0.000001);
            dist = ((time*340)/2)*100;
        }

        TIM2_us_Delay(4);
        data = 0;
    }

}
