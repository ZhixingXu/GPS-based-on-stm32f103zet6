/*
 * @Description: 
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-16 19:08:46
 * @LastEditTime: 2020-05-17 15:48:01
 */ 
#include "main.h"

int main()
{
	USART2_Config();
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
        GPS_Work();
        if(GPS_IsWorkSteady()){
            #ifdef TEST
            printf("%s\t%s\r\n",gpgga.GPS_Data.latitude_dir,gpgga.GPS_Data.latitude);
            #endif
            //GPS has get almost complete info
        }
        else
        {//searching GPS signal
            #ifdef TEST
            printf("Searching...\r\n");
            #endif
        }
        
        delayus(100000);
    }
    
}
