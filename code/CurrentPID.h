/*
 * CurrentPID.h
 *
 *  Created on: 2023Äê11ÔÂ11ÈÕ
 *      Author: 23913
 */

#ifndef CURRENTPID_H_
#define CURRENTPID_H_
#include "pid.h"
extern float current_l;
extern float voltage;
extern float current_r;
extern float idealcurrent;
void Current_Init();
void Current_PIT(void);
int16 Current_Pid_L(pid_param_t Current_PID);
int16 Current_Pid_R(pid_param_t Current_PID);
#endif /* CURRENTPID_H_ */
