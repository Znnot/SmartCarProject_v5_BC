#include "zf_common_headfile.h"
#include"Encoder.h"
#include"pid.h"
#include"Fuzzy.h"
#include"camera.h"
/***********************************************
* @brief :pwm初始化函数，不解释
* @param :
* @return:无
* @date  :
* @author:T
************************************************/
void PWMInit(void){
//    pwm_init(ATOM1_CH1_P33_9, 50, 766);
    gpio_init(P21_2, GPO, 1, GPO_PUSH_PULL);
    gpio_init(P21_4, GPO, 1, GPO_PUSH_PULL);
    pwm_init(ATOM0_CH0_P21_2,17000,0);
    pwm_init(ATOM0_CH1_P21_3,17000,1200);
    pwm_init(ATOM0_CH2_P21_4,17000,0);
    pwm_init(ATOM0_CH3_P21_5,17000,1200);
}
/***********************************************
* @brief :电机赋值函数，全轮/左轮/右轮
* @param :int16 speed_pwm：调节占空比
* @return:无
* @date  :
* @author:LMX
************************************************/

//void set_whole_speed(int16 speed_pwm_hope)///根据正负来控制来做加减速、正反转
//{
//    pwm_set_duty(ATOM1_CH2_P21_4,0);
//    pwm_set_duty(ATOM1_CH3_P21_5,speed_pwm_hope);
//    pwm_set_duty(ATOM1_CH0_P21_2,0);
//    pwm_set_duty(ATOM1_CH1_P21_3,speed_pwm_hope);
//
//}
//
//void set_whole_fan_speed(int16 speed_pwm_hope)///根据正负来控制来做加减速、正反转
//{
//    pwm_set_duty(ATOM1_CH2_P21_4,speed_pwm_hope);
//    pwm_set_duty(ATOM1_CH3_P21_5,0);
//    pwm_set_duty(ATOM1_CH0_P21_2,speed_pwm_hope);
//    pwm_set_duty(ATOM1_CH1_P21_3,0);
//
//}

void set_right_speed(int16 speed_pwm_right){
    if(speed_pwm_right>=0)   //正转
       {
        pwm_set_duty(ATOM0_CH2_P21_4,0);
        pwm_set_duty(ATOM0_CH3_P21_5,speed_pwm_right);

       }
       else                //反转
       {
           pwm_set_duty(ATOM0_CH2_P21_4,-speed_pwm_right);
           pwm_set_duty(ATOM0_CH3_P21_5,0);

       }

}
void set_left_speed(int16 speed_pwm_left){
    if(speed_pwm_left>=0)  //正转
    {
        pwm_set_duty(ATOM0_CH0_P21_2,0);
        pwm_set_duty(ATOM0_CH1_P21_3,speed_pwm_left);
    }
    else                //反转
    {
        pwm_set_duty(ATOM0_CH0_P21_2,-speed_pwm_left);
        pwm_set_duty(ATOM0_CH1_P21_3,0);

    }
}

/***********************************************
* @brief :差速（减不变带限幅版）
* @param :radian（舵机pwm和打角的对应系数）ENCO_WISH_L（阿克曼差速公式推出）
* @return:无
* @date  :
* @author:T
************************************************/
double diff_xishu=0.00025;
float Add_xishu,Min_xishu;

void difspeed(void){
    int diff_steerpwm=SteerPWM-steer_center;//找舵机输出与中值的差值，区分左右转弯，绝对值越大则左右轮差速越大
    double radian;
    if(diff_steerpwm>0) //左转
    {
        radian=diff_xishu*(diff_steerpwm*diff_steerpwm)*0.25*0.1*3.5;    //左轮与竖直线实际夹角 /   //若舵机阈值与实际最大打角改变，则需要修改此处（*需理解串级，电机+舵机）0.0139794
        ENCO_Wish_L=(1-radian)*Basic_Speed;   //左转左轮减速    //此处由前轮轮距和前后轮轴距决定，一般不需要改动
        ENCO_Wish_R=Basic_Speed;
    }
    else               //右转
    {
        diff_steerpwm=-diff_steerpwm;
        radian=diff_xishu*(diff_steerpwm*diff_steerpwm)*0.25*0.1*3.5;
        ENCO_Wish_R=(1-radian)*Basic_Speed;
        ENCO_Wish_L=Basic_Speed;
    }
//    ips200_show_int(40,100,ENCO_Wish_L,4);
//    ips200_show_int(40,150,ENCO_Wish_R,4);
//    ips200_show_float(40,200,radian,4,1);
}
/***********************************************
* @brief :缓冲区数组赋值给控制参数，开菜单时调节值完之后使用该函数，注意用菜单时注释PID_Init函数
* @param :无
* @return:无
* @date  :
* @author:T
************************************************/
void Parameter_init(void)
{
        flash_buffer_clear();
        flash_read_page_to_buffer(0, 10);      // 鐏忓棙鏆熼幑顔荤矤 flash 鐠囪褰囬崚鎵处閸愭彃灏�
        system_delay_ms(50);

        element_data[1].addbasic_speed=flash_union_buffer[0].float_type;
        element_data[2].addbasic_speed=flash_union_buffer[1].float_type;
        element_data[3].addbasic_speed=flash_union_buffer[2].float_type;
        element_data[4].adddynamic_H_speed=flash_union_buffer[3].float_type;
        element_data[4].adddynamic_L_speed=flash_union_buffer[4].float_type;
        ring_data[2].addring_exter_speed=flash_union_buffer[5].float_type;
        ring_data[2].addring_inter_speed=flash_union_buffer[6].float_type;
        ring_data[1].addring_exter_speed=flash_union_buffer[7].float_type;
        ring_data[1].addring_inter_speed=flash_union_buffer[8].float_type;
        ring_data[3].ring_size_threshold=flash_union_buffer[9].float_type;
        ring_data[3].half_wide_offset_big=flash_union_buffer[10].float_type;
        ring_data[3].half_wide_offset_small=flash_union_buffer[11].float_type;
        addLFuya=flash_union_buffer[12].float_type;
        addMFuya=flash_union_buffer[13].float_type;
        addHFuya=flash_union_buffer[14].float_type;
        element_data[3].integral=flash_union_buffer[15].float_type;//有问题：是不是会被覆盖？
        Ramp_num=element_data[3].integral;
        Cross_white_line=flash_union_buffer[16].float_type;
//        MT9V03X_EXP_TIME_DEF=flash_union_buffer[17].float_type;
}
/***********************************************
* @brief :PID初始化函数
* @param :无
* @return:无
* @date  :231008
* @author:T
************************************************/
void PID_Init(void){//这里初始化舵机和电机的PID参数
     Steer_PID.Kp=1.2;//2.5;
     Steer_PID.Kd=11;//7
//    Steer_PID.Kp=4;//2.10;
//    Steer_PID.Kd=9;
     KP2=0.00025;

     Motor_Left_PID.Kp=70;
     Motor_Left_PID.Ki=2;
     Motor_Left_PID.Kd=0;

     Motor_Right_PID.Kp=70;
     Motor_Right_PID.Ki=2;
     Motor_Right_PID.Kd=0;
}
/***********************************************
* @brief :中断处理舵机控制，为了方便使用结构体，取出来
* @param :无
* @return:无
* @date  :231008
* @author:T
************************************************/
void steer_control(void){
    steer_pid(Steer_PID);
}
