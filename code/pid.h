/*
 * pid.h
 *
 *  Created on: 2023年8月15日
 *      Author: Ming
 */

#ifndef PID_H_
#define PID_H_
typedef struct//定义kp、ki、kd
{
  float Kp;         //P
  float Ki;         //I
  float Kd;         //D
}pid_param_t;
extern pid_param_t Steer_PID;
extern float KP2;
extern pid_param_t Motor_Left_PID;
extern pid_param_t Motor_Right_PID;
extern pid_param_t Current_PID_L;
extern pid_param_t Current_PID_R;
extern int16 SteerPWM;
extern int16 pwm_min;
extern int16 steer_center;
extern float str;
void steer_pid(pid_param_t Steer_pid);
int16 motorL_pid(pid_param_t motorL_pid,int16 enco_true,int16 enco_wish);
int16 motorR_pid(pid_param_t motorR_pid,int16 enco_true,int16 enco_wish);
int16 position_pid(pid_param_t Posit_pid,int16 enco_true,int16 enco_wish);

#endif /* PID_H_ */
