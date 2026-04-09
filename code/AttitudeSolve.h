/*
 * AttitudeSolve.h
 *
 *  Created on: 2024Äê1ÔÂ9ÈÕ
 *      Author: ½¶Ì«ÀÇ
 */

#ifndef CODE_ATTITUDESOLVE_H_
#define CODE_ATTITUDESOLVE_H_
#include"zf_common_headfile.h"

typedef struct{
    float gyroOffsetX;
    float gyroOffsetY;
    float gyroOffsetZ;
} GyroOffsetTypeDef;

typedef struct{
    float gyroX;
    float gyroY;
    float gyroZ;
    float accX;
    float accY;
    float accZ;
} IMUDataTypeDef;

typedef struct
{
    float q0;
    float q1;
    float q2;
    float q3;
} QuaterTypedef;

typedef struct
{
    float pitch;    //¸©Ñö½Ç
    float roll;     //Æ«º½½Ç
    float yaw;      //·­¹ö½Ç
} EulerTypedef;

extern EulerTypedef g_eulerAngle;
extern IMUDataTypeDef g_imuData;
extern GyroOffsetTypeDef m_gyroOffset;

void IMU_get_values(void);
void IMU_get_euler(void);
void IMU_gyro_offset_init(void);

extern float Roll,Pitch,Yaw;
extern int16 IMU_Flag;
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);

#endif /* CODE_ATTITUDESOLVE_H_ */



