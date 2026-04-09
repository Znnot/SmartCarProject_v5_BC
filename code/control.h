#ifndef CONTROL_H_
#define CONTROL_H_
#include "zf_common_headfile.h"
void set_left_speed(int16 speed_pwm_left);
void set_right_speed(int16 speed_pwm_right);
void set_whole_speed(int16 speed_pwm_hope);
void set_whole_fan_speed(int16 speed_pwm_hope);
void PWMInit(void);
void difspeed(void);
void steer_control(void);
void PID_Init(void);
void Parameter_init(void);
extern float Min_xishu;
extern float Add_xishu;
extern double diff_xishu;

#endif /* CONTROL_H_ */
