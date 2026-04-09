/*
 * tof.c
 *
 *  Created on: 2024年1月20日
 *      Author: 周文烽
 */


#include "zf_common_headfile.h"
#include "WS2812B.h"

int16 get_tofdistance=8912;
uint16 refresh_tim=0;
uint8 read_flag=0;

void tof_Init(void)
{
    while(1)
    {
        if(dl1b_init())
        {
//            Light_Color(rgb_Green);
            break;
        }
        else
        {
//            Light_Color(rgb_Green);
//            oled_show_string(6,3,"ok!");
//            ips200_show_string(50,140,"dl1b:");
            break;
        }
    }
}

