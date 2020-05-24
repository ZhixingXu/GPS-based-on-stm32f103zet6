/*
 * @Description: 
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-16 19:08:46
 * @LastEditTime: 2020-05-24 14:56:05
 */ 
#include "main.h"

int main()
{
    OLED_Init();
	USART2_Config();
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	#ifdef TEST
	USART1_Config();
	USART_ClearFlag(USART1,USART_FLAG_TC);
	printf("hello,world\r\n");
	#endif
    while (1)
    {
//		printf("%c",USART_ReceiveData(USART2));
//		while(USART_GetFlagStatus(USART_GPS,USART_FLAG_RXNE)==RESET){
//		}
        GPS_GetAll();
        GPS_InfoSort();
        if(GPS_hasTime())
        {
            //show时间
            OLED_ShowTime();
        }
        if(GPS_IsWorkSteady()){
            //
            #ifdef TEST
            printf("%s\t%s\r\n",strncmp(gpgga.GPS_Data.latitude_dir,"N",2)?"北":"南",gpgga.GPS_Data.latitude);
            #endif
            //GPS has get almost complete info
            OLED_ShowLocation();
            OLED_ShowHeigt();
        }
        else
        {//searching GPS signal
			OLED_Clear();
            OLED_ShowString(20,16,(unsigned char*)"searching...",16);
            #ifdef TEST
            printf("Searching...\r\n");
            #endif
        }
        OLED_Refresh();//每次写入数据后必须refresh一下
        delayus(18000);
    }
    
}
