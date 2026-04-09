/*
 * FIliter.h
 *
 *  Created on: 2023Äê10ÔÂ18ÈÕ
 *      Author: 23913
 */

#ifndef FILITER_H_
#define FILITER_H_

typedef struct{
        int16 x;
        float A;
        float H;
        float Q;
        float R;
        float P;
        float gain;
}kalman_filter_1;

extern kalman_filter_1 tof;

float Lag_1(int16 a,float value);
int16 Lag_2(int16 a,int16 value);
int16 SecondOrderLagFilter_L(int16 value);
int16 SecondOrderLagFilter_R(int16 value);
void kalman1_init(kalman_filter_1* state, float q, float r);
int16 kalman1_filter(kalman_filter_1* state, float z_measure);
int16 SecondOrderLagFilter_steer(int16 value);
#endif /* FILITER_H_ */
