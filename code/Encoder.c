/*
 * Encoder.c
 *
 *  Created on: 2023骞�9鏈�24鏃�
 *      Author: 23913
 */
#include "zf_common_headfile.h"
#include "pid.h"
#include "VO.h"
#include "FIliter.h"
#include "CurrentPID.h"
#include "camera.h"
#include "WS2812B.H"
#include"control.h"
#include"Fuzzy.h"
#define ENCODER_2                   (TIM6_ENCODER)
#define ENCODER_2_DIR               (TIM6_ENCODER_CH2_P20_0)
#define ENCODER_2_LSB               (TIM6_ENCODER_CH1_P20_3)

#define ENCODER_1                   (TIM2_ENCODER)
#define ENCODER_1_DIR               (TIM2_ENCODER_CH2_P33_6)
#define ENCODER_1_LSB               (TIM2_ENCODER_CH1_P33_7)
//int16 ENCO_Wish_L=70;
//int16 ENCO_Wish_R=70;

int16 ENCO_Wish_L=110;
int16 ENCO_Wish_R=110;

int16 Basic_Speed=80;//400
int16 encoder_data_1 = 0;
int16 encoder_data_2 = 0;
int16 encoder_sum_1 =0;
int16 encoder_sum_2 =0;
float encofloat_1;
float encofloat_2;
int16* point1=0;
int16* point2=0;
float speed1=0;
float speed2=0;
pid_param_t Steer_PID;
pid_param_t Motor_Left_PID;
pid_param_t Motor_Right_PID;
pid_param_t Current_PID_L;
pid_param_t Current_PID_R;


/**********************************************
* @brief :缂栫爜鍣ㄥ垵濮嬪寲锛屽紑鍚畾鏃跺櫒5涓柇
* @param :鏃�
* @return:鏃�
* @date  :231008
* @author:T
************************************************/
void Encoder_init(void){
//    encoder_dir_init(ENCODER_1, ENCODER_1_DIR, ENCODER_1_LSB);                  // 鍒濆鍖栫紪鐮佸櫒妯″潡涓庡紩鑴� 鏂瑰悜瑙ｇ爜缂栫爜鍣ㄦā寮�
//    encoder_dir_init(ENCODER_2, ENCODER_2_DIR, ENCODER_2_LSB);
    encoder_quad_init(TIM2_ENCODER,TIM2_ENCODER_CH1_P33_7,TIM2_ENCODER_CH2_P33_6);//右轮
    encoder_quad_init(TIM4_ENCODER,TIM4_ENCODER_CH1_P02_8,TIM4_ENCODER_CH2_P00_9 );//左轮

}

/***********************************************
* @brief :鏍规嵁缂栫爜鍣ㄨ鍊艰绠楅�熷害锛岃皟鑺侾ID涓嶉渶瑕侊紝鐩存帴鐢ㄨ剦鍐叉暟
* @param :int16 encoder_data锛氱紪鐮佸櫒璇诲埌鐨勫��
* @return:float v锛氶�熷害锛坢/s锛�
* @date  :231008
* @author:T
************************************************/

float speedcau(int16 encoder_data){
    float coe=11279.8;
    float enco_per_m=encoder_data/coe;
    float v=enco_per_m/10*0.001;//10ms
    return v;
}
float fdata[6]={0};
uint8 tail[4]={0x00, 0x00, 0x80, 0x7f};
void uart_read_buffer(uint8* buff, uint32 len) {
    while (len)
    {
        static uint8_t i = 0;
        if (uart_query_byte(UART_2, buff)) {
            len--;
            buff++;
            i++;
        }
        else { break; }
    }
}



float R_speed=0;
float L_speed=0;
float Distance=0;
//float xishu=0;
void Motor_control(void)
{
    int16 pwm_l;
    int16 pwm_r;

    Basic_Speed=120;//这里设置期望速度

    encoder_data_1 = SecondOrderLagFilter_L(encoder_get_count(TIM4_ENCODER));//二阶滞后滤波
    encoder_data_2 = SecondOrderLagFilter_R(encoder_get_count(TIM2_ENCODER));
//    if (ImageFlag.Ramp == 1 ||ImageFlag.Ramp_Flag==1) {
//        encoder_sum_1 += encoder_data_1;
//        encoder_sum_2 += encoder_data_2;
//    }
    encoder_clear_count (TIM2_ENCODER);
    encoder_clear_count (TIM4_ENCODER);
    R_speed=(((float)encoder_data_2/1024)*0.4412*0.2011)/0.002;//左右轮速度
    L_speed=(((float)encoder_data_1/1024)*0.4412*0.2011)/0.002;
//    Distance=Distance+((R_speed+L_speed)/2)*100*0.002;//总距离
//    ips200_show_float(40,50,Distance,5,3);
//    ips200_show_float(40,100,L_speed,2,3);
    Basic_Speed=Basic_Speed*sqrt(ImageStatus.Det_True*ImageStatus.Det_True*0.1+Err_y*Err_y)/25;//简单控距，改变系数25可以设置前后车的基准距离，这里比较关键，难用语言描述，这里是第一次完赛的转折点
    difspeed();//四轮差速辅助转弯
    if(ImageFlag.Stop==1)//出界保护或斑马线停车
       {
           ENCO_Wish_L=0;
           ENCO_Wish_R=0;
       }

    pwm_l = motorL_pid(Motor_Left_PID, encoder_data_1, ENCO_Wish_L);
    pwm_r = motorR_pid(Motor_Right_PID, encoder_data_2, ENCO_Wish_R);
//    uart_read_buffer(UART_RX_Buffer, UART_RX_LEN);
//    fdata[0] = (float)encoder_data_1;
//    fdata[1] = (float)encoder_data_2;
//    fdata[2] = (float)ENCO_Wish_L;
//    fdata[3] = (float)ENCO_Wish_R;
//    fdata[4] = (float)pwm_l;
//    fdata[5] = (float)pwm_r;
//    uart_write_buffer(UART_2, (uint8*)fdata, sizeof(float) * 6);
//    uart_write_buffer(UART_2, (uint8*)tail, 4);
    set_left_speed(pwm_l);//最终输出到左右电机
    set_right_speed(pwm_r);
//    wireless_uart_read_buffer(UART_RX_Buffer, UART_RX_LEN);
//    VofaInteract();
}




