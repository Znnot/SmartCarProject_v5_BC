/*
 * tof.h
 *
 *  Created on: 2024年1月20日
 *      Author: 周文烽
 */

#ifndef CODE_TOF_H_
#define CODE_TOF_H_


extern uint16 refresh_tim;
extern uint8 read_flag;
extern int16 get_tofdistance;

void tof_Init(void);


#endif /* CODE_TOF_H_ */
