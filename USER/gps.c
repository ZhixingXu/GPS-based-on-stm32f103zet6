/*
 * @Description: some function about GPS
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-11 21:29:10
 * @LastEditTime: 2020-05-24 20:33:19
 */ 


#include "gps.h"
#include "oled.h"
#ifdef TEST 
#include "usart.h"
#endif
/**
 * @brief: get all string from GPS
 * @param {type} void
 * @retval: 
 */
void GPS_GetAll(void){
    int count=0;
	while(USART_GetFlagStatus(USART_GPS,USART_FLAG_RXNE)!=SET){
    }
    while (USART_ReceiveData(USART_GPS)!='$')
    {
        /* code */
    }
    
    for (int i = 0; i < GPS_DATA_SIZE; i++)
    {
		while(USART_GetFlagStatus(USART_GPS,USART_FLAG_RXNE)!=SET){
        }
        GPS_ALL[i]=(char)USART_ReceiveData(USART_GPS);
        if(GPS_ALL[i]=='$')count++;
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
        if(count>8)GPS_ALL[i]='\0';
    }
	#ifdef TEST 
	printf("%s",GPS_ALL);
	#endif
}

void GPS_InfoSort(void){
    char iden[6];
    for (uint16_t i = 0; i < GPS_DATA_SIZE; i++)
    {
        while(GPS_ALL[i]!='$')i++;
        for (uint8_t j = 0; j < 6; j++)
        {
            i++;
            iden[j]=GPS_ALL[i];
        }
        if(!strncmp(iden,"GPGGA,",6))
        {
            for (int k = 0; k < GPS_GPGGA_SIZE; k++)
            {
                i++;
                gpgga.GPS_REC[k]=(GPS_ALL[i]==','?'\0':GPS_ALL[i]);
            }
        }
        else if (!strncmp(iden,"GPRMC,",6))
        {
            for (int k = 0; k < GPS_GPRMC_SIZE; k++)
            {
                i++;
                gprmc.GPS_REC[k]=(GPS_ALL[i]==','?'\0':GPS_ALL[i]);
            }
        }
        else if(!strncmp(iden,"GPVTG,",6))
        {
            for (int k = 0; k < GPS_GPVTG_SIZE; k++)
            {
                i++;
                gpvtg.GPS_REC[k]=(GPS_ALL[i]==','?'\0':GPS_ALL[i]);
            }
        }
    }
    
}

void OLED_ShowLocation(){
    char integer[3];
    char fra[3]="\0";
    if(gpgga.GPS_Data.longitude_dir[0]=="E"[0])
        OLED_ShowChinese(0,16,0,16);//东
    else
        OLED_ShowChinese(0,16,1,16);//西
    OLED_ShowChinese(16,16,2,16);//经
    strncpy(integer,gpgga.GPS_Data.longitudu,3);
    strncpy(fra,gpgga.GPS_Data.longitudu+3,2);
    OLED_ShowString(32,16,(unsigned char*)integer,16);
    OLED_ShowChinese(56,16,6,16);//度
    OLED_ShowString(72,16,(unsigned char*)fra,16);
    OLED_ShowChinese(88,16,7,16);//分

    if(gpgga.GPS_Data.latitude_dir[0]=="N"[0])
        OLED_ShowChinese(0,32,4,16);//北
    else
        OLED_ShowChinese(0,32,3,16);//南
    OLED_ShowChinese(16,32,5,16);//纬
    strncpy(integer,gpgga.GPS_Data.latitude,2);
    strncpy(fra,gpgga.GPS_Data.latitude+2,2);
    fra[2]='\0';
    OLED_ShowString(32,32,(unsigned char*)integer,16);
    OLED_ShowChinese(48,32,6,16);//度
    OLED_ShowString(64,32,(unsigned char*)fra,16);
    OLED_ShowChinese(80,32,7,16);//分
    //OLED_ShowString(32,32,gpgga.GPS_Data.latitude,16);
}
void OLED_ShowTime(){
    char temp[6]="\0";
    //char*t="055909.00,A,3212.48757,N,11440.62194,E,1.603,,240520"
    //month
    strncpy(temp,gprmc.GPS_Data.UTC_Day,6);
    #ifdef TEST
    printf("temp:%s\r\n",temp);
    printf("temp[0]:%c",temp[0]);
    #endif
    if(temp[0]>='0'&&temp[0]<='9'){//ddmm
        OLED_ShowChar(0,0,temp[2],16);
        OLED_ShowChar(8,0,temp[3],16);
        OLED_ShowChar(16,0,'-',16);
        OLED_ShowChar(24,0,temp[0],16);
        OLED_ShowChar(32,0,temp[1],16);
        OLED_ShowChar(40,0,' ',16);
        OLED_ShowChar(48,0,' ',16);
    }
    //////////////////////////
    strncpy(temp,gpgga.GPS_Data.UTC_time,6);//HHMMSS
    unsigned int hour=(temp[0]-'0')*10+temp[1]-'0'+8;
    OLED_ShowNum(56,0,hour,2,16);
    OLED_ShowChar(72,0,':',16);
    //OLED_ShowString(72,0,":",16);
    OLED_ShowChar(80,0,temp[2],16);
    OLED_ShowChar(88,0,temp[3],16);
    OLED_ShowChar(96,0,':',16);
    OLED_ShowChar(104,0,temp[4],16);
    OLED_ShowChar(112,0,temp[5],16);
}
void OLED_ShowHeigt(void){
    //8个\0之后就是
    //char*t="063122.00,3212.49685,N,11440.62246,E,1,08,1.04,34.9,M";//34.9海拔
    char height[7]="\0";
    uint8_t i=0,j=0,len;
    while (i<54)
    {
        if(gpgga.GPS_REC[i]=='\0')
            j++;
        if(j==8){
            for (uint8_t k = 0; k < 7; k++)
            {
                i++;
                if(gpgga.GPS_REC[i]!='\0')
                    height[k]=gpgga.GPS_REC[i];
                else{
                    height[k]='\0';
                    break;
                }
            }
            
            // strcpy(height,gpgga.GPS_REC[i+1]);
            break;
        }
        i++;
    }
    if(height[0]>='0'&&height[0]<='9'){
        len=strlen(height);
        OLED_ShowChinese(0,48,8,16);//海
        OLED_ShowChinese(16,48,9,16);//拔
        OLED_ShowString(32,48,(unsigned char*)height,16);
        OLED_ShowChinese(32+len*8,48,10,16);//米
    }
}


void OLED_ShowSearching(){
    static uint8_t i=0;
    uint8_t j=0;
    i++;
    OLED_ShowString(12,16,(unsigned char*)"searching",16);
    for(j=0;j<i;j++){
        OLED_ShowChar(84+j*8,16,'.',16);
    }
    if(i>=3)
        i=0;
}
/**
 * @description: 是否接受到了起始符号
 * @param: void 
 * @return: 1表示接收到了
 * @author: shuai-xv
 */
// bool IsStartSign(char ch)
// {
// 	// char ch=USART_ReceiveData(USART_GPS);
//     //if(USART_ReceiveData(USART1))
// 	// #ifdef TEST 
// 	// printf("system stop at (IsStartSign):%c\r\n",ch);
// 	// //printf("%d\t%c",ch=='$',ch);
// 	// #endif
// 	// while(USART_GetFlagStatus(USART_GPS,USART_FLAG_RXNE)==RESET){
// 	// }
//     return (ch=='$');
// }

// void GPS_GPGGA_Save(){
//     for (int i = 0; i < GPS_GPGGA_SIZE; i++)
//     {
//         gpgga.GPS_REC[i]=USART_ReceiveData(USART_GPS);
//     }
// }
// void GPS_GPRMC_Save(){
//     for (int i = 0; i < GPS_GPRMC_SIZE; i++)
//     {
//         gprmc.GPS_REC[i]=USART_ReceiveData(USART_GPS);
//     }
    
// }
// void GPS_GPVTG_Save(){
//     for (int i = 0; i < GPS_GPVTG_SIZE; i++)
//     {
//         gpvtg.GPS_REC[i]=USART_ReceiveData(USART_GPS);
//     }
// }
// /**
//  * @description: 在获得startsign之后,再获取GPS的数据行的头6个字符(比如:GPGGA,),用于每个数据行的唯一标识符
//  * @param {type} void
//  * @return: void
//  * @author: shuai-xv
//  */
// void GPS_GetData(){
//     char iden[6];
//     while(!IsStartSign());
//     for (int i = 0; i < 6; i++)
//     {
//         iden[i]=USART_ReceiveData(USART_GPS);
//         if(iden[i]==',')
//             iden[i]='\0';
//     }
//     if(~strncmp(iden,"GPGGA,",6))
//     {
//         GPS_GPGGA_Save();// return ISGPGGA;
//     }
//     else if (~strncmp(iden,"GPRMC,",6))
//     {
//         GPS_GPRMC_Save();// return ISGPZDA;
//     }
//     else if(~strncmp(iden,"GPVTG,",6))
//     {
//         GPS_GPVTG_Save();// return ISGPVTG;
//     }
// }
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
bool GPS_hasTime(){
    if(gpgga.GPS_REC[0]=='\0'&&gpgga.GPS_REC[1]=='\0')
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}

// void GPS_Work(){
//     for (int i = 0; i < 8; i++)
//     {//because the module send 8 sentenses each time
//         GPS_GetData();
//     }
// }
