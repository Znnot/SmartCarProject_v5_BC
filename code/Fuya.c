/*
 * Fuya.c
 *
 *  Created on: 2024年1月23日
 *      Author: 周文烽
 */
#include "zf_common_headfile.h"

void Fuya_Init(void)
{
    pwm_init(ATOM1_CH7_P00_8,100,0);
    pwm_init(ATOM3_CH0_P33_4,100,0);
}

//speed值在50Hz范围下500-1000，100Hz下1000-2000
void Fuya_Open(uint16 speed)
{
    if(speed>2000)//负压限幅
    {
        speed=2000;
    }
    pwm_set_duty(ATOM1_CH7_P00_8,speed);
    pwm_set_duty(ATOM3_CH0_P33_4,speed);
}

void Fuya_R_Open(uint16 speed)
{
    if(speed>2000)//负压限幅
    {
        speed=2000;
    }
    pwm_set_duty(ATOM3_CH0_P33_4,speed);
}

void Fuya_L_Open(uint16 speed)
{
    if(speed>2000)//负压限幅
    {
        speed=2000;
    }
    pwm_set_duty(ATOM1_CH7_P00_8,speed);
}

void Fuya_Close(void)
{
    pwm_set_duty(ATOM1_CH7_P00_8,0);
    pwm_set_duty(ATOM3_CH0_P33_4,0);
}

uint8 Fuya_offset=0;
uint16 addLFuya=0;
uint16 addMFuya=0;
uint16 addHFuya=0;
void Dynamix_Fuya(void)
{
    if(gpio_get_level(P11_3)==0&&gpio_get_level(P11_6)==0)//拨码23--00低速
       {
           if(ImageFlag.straight_long==1)
           {
               Fuya_Open(1300);//4m--1400
           }
           else if(ImageFlag.Zebra_Counter==1&&ImageFlag.Zebra_Flag==1)
           {
               Fuya_Open(1800);//4m--1800
           }
           else if(ImageFlag.Ramp!=0)
           {
               Fuya_Open(1800);//4m--1500
           }
           else
           {
               Fuya_offset=0.03*ImageStatus.Det_True*ImageStatus.Det_True;
               if(ImageStatus.Det_True>0)//宸﹁浆
               {
                   if(ImageStatus.Det_True>5)
                   {
                       Fuya_R_Open(1800-0*Fuya_offset+addLFuya);//4m--1900
                       Fuya_L_Open(1800+2*Fuya_offset+addLFuya);//4m--1900
                   }
                   else
                   {
                       Fuya_Open(1800);//4m--1900
                   }
               }
               else
               {
                   if(ImageStatus.Det_True<-5)
                   {
                       Fuya_R_Open(1800+2*Fuya_offset+addLFuya);//4m--1900
                       Fuya_L_Open(1800-0*Fuya_offset+addLFuya);//4m--1900
                   }
                   else
                   {
                       Fuya_Open(1800+addLFuya);//4m--1900
                   }
               }
           }
       }
       else if(gpio_get_level(P11_3)==1&&gpio_get_level(P11_6)==0)//01中速
       {
           if(ImageFlag.straight_long==1)
           {
               Fuya_Open(1300);//4m--1400
           }
           else if(ImageFlag.Zebra_Counter==1&&ImageFlag.Zebra_Flag==1)
           {
               Fuya_Open(1900);//4m--1800
           }
           else if(ImageFlag.Ramp!=0)
           {
               Fuya_Open(1850);//4m--1500
           }
           else
           {
               Fuya_offset=0.03*ImageStatus.Det_True*ImageStatus.Det_True;
               if(ImageStatus.Det_True>0)//宸﹁浆
               {
                   if(ImageStatus.Det_True>5)
                   {
                       Fuya_R_Open(1890-0*Fuya_offset+addMFuya);//4m--1900
                       Fuya_L_Open(1890+2*Fuya_offset+addMFuya);//4m--1900
                   }
                   else
                   {
                       Fuya_Open(1890+addMFuya);//4m--1900
                   }
               }
               else
               {
                   if(ImageStatus.Det_True<-5)
                   {
                       Fuya_R_Open(1890+2*Fuya_offset+addMFuya);//4m--1900
                       Fuya_L_Open(1890-0*Fuya_offset+addMFuya);//4m--1900
                   }
                   else
                   {
                       Fuya_Open(1890+addMFuya);//4m--1900
                   }
               }
           }
       }
       else if(gpio_get_level(P11_3)==0&&gpio_get_level(P11_6)==1)//10高速
       {
           if(ImageFlag.straight_long==1)
           {
               Fuya_Open(1300);//4m--1400
           }
           else if(ImageFlag.Zebra_Counter==1&&ImageFlag.Zebra_Flag==1)
           {
               Fuya_Open(1900);//4m--1800
           }
           else if(ImageFlag.Ramp!=0)
           {
               Fuya_Open(1900);//4m--1500
           }
           else
           {
               Fuya_offset=0.03*ImageStatus.Det_True*ImageStatus.Det_True;
               if(ImageStatus.Det_True>0)//宸﹁浆
               {
                   if(ImageStatus.Det_True>5)
                   {
                       Fuya_R_Open(1950-0*Fuya_offset+addHFuya);//4m--1900
                       Fuya_L_Open(1950+2*Fuya_offset+addHFuya);//4m--1900
                   }
                   else
                   {
                       Fuya_Open(1950+addHFuya);//4m--1900
                   }
               }
               else
               {
                   if(ImageStatus.Det_True<-5)
                   {
                       Fuya_R_Open(1950+2*Fuya_offset+addHFuya);//4m--1900
                       Fuya_L_Open(1950-0*Fuya_offset+addHFuya);//4m--1900
                   }
                   else
                   {
                       Fuya_Open(1950+addHFuya);//4m--1900
                   }
               }
           }
       }
       else if(gpio_get_level(P11_3)==1&&gpio_get_level(P11_6)==1)//
       {
           Fuya_Open(1050);
       }


       if(ImageFlag.Stop==1)//优先级最高，放在动态负压后面
       {
           Fuya_Open(1900);
       }
       if(ImageFlag.Zebra_Flag==1&&ImageFlag.Zebra_Counter==1)
       {
           Fuya_Open(1900);
       }
}
