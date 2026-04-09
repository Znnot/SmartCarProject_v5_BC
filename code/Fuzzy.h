/*
 * Fuzzy.h
 *
 *  Created on: 2023年11月4日
 *      Author: 23913
 */

#ifndef FUZZY_H_
#define FUZZY_H_
#include "zf_common_headfile.h"
//******************模糊子集******************************
#define NB -3
#define NM -2
#define NS -1
#define ZO  0
#define PS  1
#define PM  2
#define PB  3
extern float MAX_CERR;
extern float MAX_DP;
extern float MAX_DD;
void Fuuzy_pid(void);
extern float min_kp;
extern float max_kp;
extern float min_kd;
extern float max_kd;
#endif /* FUZZY_H_ */
