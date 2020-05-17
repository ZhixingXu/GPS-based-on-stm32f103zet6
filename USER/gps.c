/*
 * @Description: some function about GPS
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-11 21:29:10
 * @LastEditTime: 2020-05-17 14:50:30
 */ 


#include "gps.h"
#ifdef TEST 
#include "usart.h"
#endif

/**
 * @description: 是否接受到了起始符号
 * @param: void 
 * @return: 1表示接收到了
 * @author: shuai-xv
 */
bool IsStartSign(void)
{
	char ch=USART_ReceiveData(USART_GPS);
    //if(USART_ReceiveData(USART1))
	#ifdef TEST 
	printf("system stop at (IsStartSign):%c\r\n",ch);
	//printf("%d\t%c",ch=='$',ch);
	#endif
	while(USART_GetFlagStatus(USART_GPS,USART_FLAG_RXNE)==RESET){
	}
    return (ch==(char)'$');
}

void GPS_GPGGA_Save(){
    for (int i = 0; i < GPS_GPGGA_SIZE; i++)
    {
        gpgga.GPS_REC[i]=USART_ReceiveData(USART_GPS);
    }
}
void GPS_GPRMC_Save(){
    for (int i = 0; i < GPS_GPRMC_SIZE; i++)
    {
        gprmc.GPS_REC[i]=USART_ReceiveData(USART_GPS);
    }
    
}
void GPS_GPVTG_Save(){
    for (int i = 0; i < GPS_GPVTG_SIZE; i++)
    {
        gpvtg.GPS_REC[i]=USART_ReceiveData(USART_GPS);
    }
}
/**
 * @description: 在获得startsign之后,再获取GPS的数据行的头6个字符(比如:GPGGA,),用于每个数据行的唯一标识符
 * @param {type} void
 * @return: void
 * @author: shuai-xv
 */
void GPS_GetData(){
    char iden[6];
    while(!IsStartSign());
    for (int i = 0; i < 6; i++)
    {
        iden[i]=USART_ReceiveData(USART_GPS);
        if(iden[i]==',')
            iden[i]='\0';
    }
    if(~strncmp(iden,"GPGGA,",6))
    {
        GPS_GPGGA_Save();// return ISGPGGA;
    }
    else if (~strncmp(iden,"GPRMC,",6))
    {
        GPS_GPRMC_Save();// return ISGPZDA;
    }
    else if(~strncmp(iden,"GPVTG,",6))
    {
        GPS_GPVTG_Save();// return ISGPVTG;
    }
}
/**
 * @brief: 模块刚工作时许多数据是空的,过一段时间才能平稳工作,本函数用于区分是否平稳工作
 * @param {type} void
 * @retval: 1表明是在平稳工作
 */
bool GPS_IsWorkSteady(){
    if(gpgga.GPS_REC[0]=='\0'&&gpgga.GPS_REC[1]=='\0')
    {
        return 0;
    }
    else if(gpgga.GPS_Data.latitude[0]=='\0'&&gpgga.GPS_Data.latitude[1]=='\0')
    {
        return 0;
    }
    else{
        return 1;
    }
    
    //char _NO_USA_[]="$GPRMC,110911.00,A,3212.49542,N,11440.62004,E,0.018,,";
}

void GPS_Work(){
    for (int i = 0; i < 8; i++)
    {//because the module send 8 sentenses each time
        GPS_GetData();
    }
}
