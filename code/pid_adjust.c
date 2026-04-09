/*
 * pid_adjust.c
 *
 *  Created on: 2024年12月3日
 *      Author: QW RUAN
 */


#include "zf_common_headfile.h"
#include "pid_adjust.h"

uint8_t RxBuffer[1];//缓冲数组
uint16_t RxLine = 0;//数组长度
uint8_t DataBuff[256];//指令内容
char go;


float Get_Data(void)
{
    uint8_t data_Start_Num = 0; // 开始的数字位
    uint8_t data_End_Num = 0; // 结束的数字位
    uint8_t minus_Flag = 0; // 负数标志位
    float data_return = 0; // 解析数据
    int lsb; // 小数部分
    for(uint8_t i=0;i<200;i++)
    {
        if (DataBuff[i] == '=')
        {
            data_Start_Num = i + 1;
        }
        if (DataBuff[i] == '!')
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(DataBuff[data_Start_Num] == '-') // 检查看是不是负数
    {
        data_Start_Num += 1; // 如果是负数往后退一位
        minus_Flag = 1; // 负数标志位置一
    }
    /* 查看小数点位置 */
    uint8_t point_position = 0;
    for(uint8_t i = data_Start_Num; i <= data_End_Num; i++)
    {
        if(DataBuff[i] == '.')
        {
            point_position = i;
            break;
        }
    }
    for(uint8_t i = data_Start_Num; i < point_position; i++ )
    {
        data_return = data_return*10 + DataBuff[i] - 48;
    }
    float divisor = 10.0;
    for(uint8_t i = point_position + 1; i <= data_End_Num; i++)
    {
         data_return += (DataBuff[i] - 48) / divisor;
         divisor *= 10;
    }
    if(minus_Flag == 1)
    {
        data_return = -data_return;
    }
    return data_return;

}

void USART_PID_Adjust(uint8_t motor_n)
{
    float data_Get = Get_Data(); // 接收数据
    printf("data=%.2f\r\n",data_Get);
    if(motor_n ==1)
    {
        /* 速度环 */
//        if(DataBuff[0]=='P' && DataBuff[1]=='1') // 左电机
//            motor1pid.kp = data_Get;
//
//        else if(DataBuff[0]=='I' && DataBuff[1]=='1')
//            motor1pid.ki = data_Get;
//
//        else if(DataBuff[0]=='D' && DataBuff[1]=='1')
//            motor1pid.kd = data_Get;
//
//        else if(DataBuff[0]=='P' && DataBuff[1]=='2') // 右电机
//            motor2pid.kp  = data_Get;
//
//        else if(DataBuff[0]=='I' && DataBuff[1]=='2')
//            motor2pid.ki  = data_Get;
//
//        else if(DataBuff[0]=='D' && DataBuff[1]=='2')
//            motor2pid.kd = data_Get;

             if(DataBuff[0]=='s' && DataBuff[1]=='d')
                 go = data_Get;

             else if(DataBuff[0]=='E' && DataBuff[1]=='L')
                 ENCO_Wish_L= data_Get;

              else if(DataBuff[0]=='E' && DataBuff[1]=='R')
                  ENCO_Wish_R= data_Get;
//                else if(DataBuff[0]=='S' && DataBuff[1]=='t'){
//
//         steer_pid.kp = data_Get;
//
//                }
//                else if(DataBuff[0]=='D' && DataBuff[1]=='F')
//                 diff_xishu = data_Get/1000;
//                else if(DataBuff[0]=='H' && DataBuff[1]=='S')
//                    Hangshu = data_Get;
//                else if(DataBuff[0]=='Y' && DataBuff[1]=='T')
//                    yuanhuan_time = data_Get;
                }


}





