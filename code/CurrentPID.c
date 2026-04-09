/*
 * CurrentPID.c
 *
 *  Created on: 2023年11月11日
 *      Author: 23913
 */
#include "zf_common_headfile.h"
#include "CurrentPID.h"
float voltage_l=0,current_l=0,power_l=0;
float voltage_r=0,current_r=0,power_r=0;
float voltage=0;
float idealcurrent=0.6;
uint16_t U_little,I_little,P_little;
//记得做平均值滤波处理
void Current_Init(void){
    adc_init(ADC0_CH0_A0,ADC_12BIT);
    adc_init(ADC0_CH2_A2,ADC_12BIT);
}
int count=0;
int flag=1;
void Current_PIT(void){
    current_l=(float)3.3*adc_mean_filter_convert(ADC0_CH0_A0,5)/4096;
//      tft180_show_uint(0,0,voltage,8);
//      system_delay_ms(100);
}

int16 Current_Pid_L(pid_param_t Current_PID)//增量式PI(左)
{

    static float error=0;
    static int16 last_error=0;
    float pwm_output=0;//pid的输出

    error=(idealcurrent-current_l);
    pwm_output += Current_PID.Kp*(error-last_error) + Current_PID.Ki*error ;


    if(pwm_output>3000)
    {
        pwm_output=3000;
    }
    if(pwm_output<0)
    {
        pwm_output=0;
    }
    last_error=error;
    return (int16)pwm_output;

}
int16 Current_Pid_R(pid_param_t Current_PID)//增量式PI(左)
{

    static float error=0;
    static int16 last_error=0;
    float pwm_output=0;//pid的输出

    error=(idealcurrent-current_r);
    pwm_output += Current_PID.Kp*(error-last_error) + Current_PID.Ki*error ;


    if(pwm_output>2000)
    {

        pwm_output=2000;
    }
    if(pwm_output<0)
    {
        pwm_output=0;
    }
    last_error=error;
    return (int16)pwm_output;

}
