#ifndef USART_H
#define USART_H

#include <stm32f10x.h>

#ifdef TEST
#include<stdio.h>
#endif
//define of usart1
#define USART1_PORT_BUS RCC_APB2Periph_GPIOA
#define USART1_BUS      RCC_APB2Periph_USART1
#define USART1_PORT     GPIOA
#define USART1_PORT_TX  GPIO_Pin_9
#define USART1_PORT_RX  GPIO_Pin_10
//define of usart2
#define USART2_BUS      RCC_APB1Periph_USART2
#define USART2_PORT_BUS RCC_APB2Periph_GPIOA
#define USART2_PORT     GPIOA
#define USART2_PORT_TX  GPIO_Pin_2
#define USART2_PORT_RX  GPIO_Pin_3



#ifdef TEST
int fputc(int ch,File*f);
void USART1_Config(void);
#endif
void USART2_Config(void);
#endif
