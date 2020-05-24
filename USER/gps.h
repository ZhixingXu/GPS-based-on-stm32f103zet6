/*
 * @Description: 
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-11 21:29:20
 * @LastEditTime: 2020-05-24 20:24:30
 */ 
#ifndef GPS_H
#define GPS_H

#include<stm32f10x.h>
#include<string.h>
/***********************经纬度相关**************************/
typedef struct
{
    //char GUIDE[7];//固定为$GPGGA
    char UTC_time[10];//HHMMSS.00
    char latitude[11];//纬度ddmm.mmmm,即dd度,mm.mmmm分
    char latitude_dir[2];//N/S
    char longitudu[12];//dddmm.mmmm即ddd度,mm.mmmm分
    char longitude_dir[2];//E/W
    char quality_factor[2];//0:没有定位,1=实施GPS,2=差分GPS
    char satellite_num[3];
    //char accuracy_factor [4];//水平精度因子(1.0-99.9)这个麻烦可以是4位或5位,暂定4位
    //char antenna_height[]//这个海拔高度我挺想使用的
    //后面这些其实也没用
}GPGGA_Data;
typedef union
{
    char GPS_REC[55];//40个字节
    GPGGA_Data GPS_Data;
}GPS_GPGGA;
static const int GPS_GPGGA_SIZE=55;//40已经足够了,我还想用一下那个海拔高度,不过有点麻反

// /******************************时间相关**************************/
// typedef struct {
//     char UTC_Time[10];//HHMMSS.00
//     char day[3];
//     char month[3];
//     char year[5];
// }GPZDA_Data;
// typedef union {
//     char GPS_REC[21];
//     GPZDA_Data GPS_Data;
// }GPS_GPZDA;
// const int GPS_GPZDA_SIZE=21;

/*************************航向相关,以我目前室内测试来看,这个方向搜不到*****************/
typedef struct {
    char Geography_Dir[4];//以真北为参考基准的地面航向
    char _Iden_1[2];
    char Magnet_Dir[4];//以磁北为参考基准的地面航向
    char _Iden_2[2];
}GPVTG_Data;
typedef union
{//
    char GPS_REC[12];
    GPVTG_Data GPS_Data;
}GPS_GPVTG;
static const int GPS_GPVTG_SIZE=12;

typedef struct {
    char _NO_USE_[46];
    char UTC_Day[6];
}GPRMC_Data;
typedef union {
    char GPS_REC[65];
    GPRMC_Data GPS_Data;
}GPS_GPRMC;
static const int GPS_GPRMC_SIZE=65;



#define bool _Bool
#define ISGPGGA 1
// #define ISGPZDA 2
#define ISGPVTG 3
#define ISGPRMC 4    //GPZDA is about tiom,but this gps module doesn't have gpzda
#define USART_GPS USART2

extern GPS_GPGGA gpgga;//经纬度(海拔)
extern GPS_GPVTG gpvtg;//航向,(室内测试找不到)
// extern GPS_GPZDA gpzda;//UTC时间
extern GPS_GPRMC gprmc;

//extern char TEMP;

#define GPS_DATA_SIZE 500
static char GPS_ALL[GPS_DATA_SIZE];

// void GPS_GetData(void);
bool GPS_IsWorkSteady(void);
bool GPS_hasTime(void);
// void GPS_Work(void);
void GPS_InfoSort(void);
void GPS_GetAll(void);
void OLED_ShowLocation(void);
void OLED_ShowTime(void);
void OLED_ShowHeigt(void);
void OLED_ShowSearching(void);

#endif

