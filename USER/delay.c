/*
 * @Description: 
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-17 14:58:10
 * @LastEditTime: 2020-05-23 11:15:33
 */ 
#include "delay.h"

void Systick_Init(){
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void delayus(int t){
    int temp;
    SysTick->LOAD=9*t;
    SysTick->VAL=0;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp=SysTick->CTRL;
    } while ((temp&0x01)&&!(temp&(1<<16)));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL=0;
}

void delayms(int t){
    int temp;
    SysTick->LOAD=9000*t;
    SysTick->VAL=0;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp=SysTick->CTRL;
    } while ((temp&0x01)&&!(temp&(1<<16)));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL=0;
}
