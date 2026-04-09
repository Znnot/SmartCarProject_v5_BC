/*
 * pid_adjust.h
 *
 *  Created on: 2024Äê12ÔÂ3ÈÕ
 *      Author: QW RUAN
 */

#ifndef CODE_PID_ADJUST_H_
#define CODE_PID_ADJUST_H_

float Get_Data(void);
void USART_PID_Adjust(uint8_t motor_n);
extern uint8_t RxBuffer[1];
extern uint16_t RxLine;
extern uint8_t DataBuff[256];
extern char go;



#endif /* CODE_PID_ADJUST_H_ */
