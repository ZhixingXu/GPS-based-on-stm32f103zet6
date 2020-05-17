/*
 * @Description: 
 * @Version: 1.0
 * @Autor: shuai-xv
 * @Date: 2020-05-11 21:32:15
 * @LastEditTime: 2020-05-17 15:17:52
 */ 
#ifndef MAIN_H
#define MAIN_H

#include <stm32f10x.h>
#include "gps.h"
#include "lcd.h"
#include "usart.h"
#include "delay.h"

GPS_GPGGA gpgga;//经纬度(海拔)
GPS_GPVTG gpvtg;//航向,(室内测试找不到)
// extern GPS_GPZDA gpzda;//UTC时间
GPS_GPRMC gprmc;

#endif

