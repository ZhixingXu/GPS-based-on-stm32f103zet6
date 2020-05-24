/*
 * @Description: 
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-11 21:30:05
 * @LastEditTime: 2020-05-17 19:01:31
 */ 
#include "usart.h"

#ifdef TEST

int fputc(int ch,File*f){
    USART_SendData(USART1,ch);
    while (USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
    return ch;
}

void USART1_Config(){
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(USART1_PORT_BUS|USART1_BUS,ENABLE);

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=USART1_PORT_TX;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(USART1_PORT,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin=USART1_PORT_RX;
    GPIO_Init(USART1_PORT,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate=115200;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);
    
    USART_Cmd(USART1,ENABLE);
}

#endif

void USART2_Config(){
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    RCC_APB2PeriphClockCmd(USART2_PORT_BUS,ENABLE);
    RCC_APB1PeriphClockCmd(USART2_BUS,ENABLE);

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=USART2_PORT_TX;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(USART2_PORT,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin=USART2_PORT_RX;
    GPIO_Init(USART2_PORT,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate=9600;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART2,&USART_InitStructure);

//    NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2,ENABLE);
//    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
}

