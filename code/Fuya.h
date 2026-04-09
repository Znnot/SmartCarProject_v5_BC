/*
 * Fuya.h
 *
 *  Created on: 2024年1月23日
 *      Author: 周文烽
 */

#ifndef CODE_FUYA_H_
#define CODE_FUYA_H_

#include "zf_common_headfile.h"

void Fuya_Init(void);
void Fuya_Open(uint16 speed);
void Fuya_Close(void);
void Fuya_R_Open(uint16 speed);
void Fuya_L_Open(uint16 speed);
void Dynamix_Fuya(void);
extern uint16 addLFuya;
extern uint16 addMFuya;
extern uint16 addHFuya;

#endif /* CODE_FUYA_H_ */
