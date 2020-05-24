/*
 * @Description: LCD12864's driver program
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-11 21:29:49
 * @LastEditTime: 2020-05-23 23:12:21
 */ 
#ifndef LCD_H
#define LCD_H

//#include <stm32f10x.h>
#include "delay.h"

#include "stdlib.h"	
#include "delay.h"

//-----------------OLED端口定义---------------- 
// PG12->SCL,PD5->DIN,PD4->RES,PD15->DC.PD1>CS
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_12)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOG,GPIO_Pin_12)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_5)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOD,GPIO_Pin_5)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_4)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOD,GPIO_Pin_4)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_15)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOD,GPIO_Pin_15)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_1)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_1)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define u8 unsigned char
#define u32 unsigned int

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Init(void);

//#define LCD_PORT GPIOD
//#define RST(n)   (GPIO_WriteBit(LCD_PORT,GPIO_Pin_4,(BitAction)n))//GPIO_Pin_4复位
//#define CS(n)    (GPIO_WriteBit(LCD_PORT,GPIO_Pin_3,(BitAction)n))//GPIO_Pin_3片选
//#define RS(n)    (GPIO_WriteBit(LCD_PORT,GPIO_Pin_0,(BitAction)n))//GPIO_Pin_0选择命令,0有效
//#define RD(n)    (GPIO_WriteBit(LCD_PORT,GPIO_Pin_1,(BitAction)n))//GPIO_Pin_1选择读使能
//#define WR(n)    (GPIO_WriteBit(LCD_PORT,GPIO_Pin_2,(BitAction)n))//GPIO_Pin_2选择写使能
//#define DAT_CLR  (LCD_PORT->ODR&=0x00ff)
//#define DAT(n)   (LCD_PORT->ODR |= ((n)<<8))                      //(GPIO_Write(LCD_PORT,(n)<<8))   


//void LCD_GPIO_Config(void);
//void LCD_Init(void);
//void LCD_ClearWin(void);


//#ifdef TEST

//void show(void);
//#endif


#endif
