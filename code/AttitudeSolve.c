/*
 * AttitudeSolve.c
 *
 *  Created on: 2024年1月9日
 *      Author: 蕉太狼
 */
#include "AttitudeSolve.h"
#include"zf_common_headfile.h"
#include "Filiter.h"
#include"VO.h"
#define GyroOffsetCaculate 1
#define IMUMode 0
int16 IMU_Flag=0;
GyroOffsetTypeDef m_gyroOffset;
IMUDataTypeDef g_imuData;
QuaterTypedef m_Q = {1, 0, 0, 0};  // 全局四元数
EulerTypedef g_eulerAngle; //欧拉角

float fast_sqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *) &i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

void IMU_gyro_offset_init(void)      //陀螺仪零飘初始化
{
#if GyroOffsetCaculate

    m_gyroOffset.gyroOffsetX = 0;
    m_gyroOffset.gyroOffsetY = 0;
    m_gyroOffset.gyroOffsetZ = 0;

    for(uint16 i = 0; i < 200; i++)
    {
        imu660ra_get_gyro();
        m_gyroOffset.gyroOffsetX += imu660ra_gyro_x;
        m_gyroOffset.gyroOffsetY += imu660ra_gyro_y;
        m_gyroOffset.gyroOffsetZ += imu660ra_gyro_z;
        system_delay_ms(5);
    }

    m_gyroOffset.gyroOffsetX /= 200;
    m_gyroOffset.gyroOffsetY /= 200;
    m_gyroOffset.gyroOffsetZ /= 200;

#else

    m_gyroOffset.gyroOffsetX = -0.7739;
    m_gyroOffset.gyroOffsetY = -3.5755;
    m_gyroOffset.gyroOffsetZ = 2.2170;

#endif
}

void IMU_get_values(void)
{
#if IMUMode           //陀螺仪放车尾

    imu660ra_get_acc();

    //一阶低通滤波，单位g/s
    g_imuData.accX = -Lag_1(0.3, imu660ra_acc_z) * 0.001953125f;
    g_imuData.accY = Lag_1(0.3, imu660ra_acc_y) * 0.001953125f;
    g_imuData.accZ = Lag_1(0.3, imu660ra_acc_x) * 0.001953125f;

    imu660ra_get_gyro();
    //陀螺仪角度转弧度
    g_imuData.gyroZ = ((float) imu660ra_gyro_x - m_gyroOffset.gyroOffsetX) * 0.0010642251536f;
    g_imuData.gyroY = ((float) imu660ra_gyro_y - m_gyroOffset.gyroOffsetY) * 0.0010642251536f;
    g_imuData.gyroX = -((float) imu660ra_gyro_z - m_gyroOffset.gyroOffsetZ) * 0.0010642251536f;

#else                  //陀螺仪放车底

    imu660ra_get_acc();
    //一阶低通滤波，单位g/s
    g_imuData.accZ = Lag_1(0.3, imu660ra_acc_z) * 0.001953125f;
    g_imuData.accY = Lag_1(0.3, imu660ra_acc_y) * 0.001953125f;
    g_imuData.accX = Lag_1(0.3, imu660ra_acc_x) * 0.001953125f;

    imu660ra_get_gyro();
    //陀螺仪角度转弧度
    g_imuData.gyroX = ((float) imu660ra_gyro_x - m_gyroOffset.gyroOffsetX) * 0.0010642251536f;
    g_imuData.gyroY = ((float) imu660ra_gyro_y - m_gyroOffset.gyroOffsetY) * 0.0010642251536f;
    g_imuData.gyroZ = ((float) imu660ra_gyro_z - m_gyroOffset.gyroOffsetZ) * 0.0010642251536f;

#endif
}

#define HalfT     0.002f  //4ms计算一次

float m_integralErrorX, m_integralErrorY, m_integralErrorZ;  // 误差积分
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
float AHRS_Kp = 0.7;   // 加速度计的收敛速率比例增益
float AHRS_Ki = 0.006;  //陀螺仪收敛速率的积分增益 0.004

//互补滤波
void IMU_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az) {
    float vx, vy, vz;    //当前的机体坐标系上的重力单位向量
    float ex, ey, ez;    //四元数计算值与加速度计测量值的误差

    //对加速度数据进行归一化 得到单位加速度
    float norm = fast_sqrt(ax * ax + ay * ay + az * az);
    ax *= norm;
    ay *= norm;
    az *= norm;

    //根据当前四元数的姿态值来估算出各重力分量。用于和加速计实际测量出来的各重力分量进行对比，从而实现对四轴姿态的修正
    vx = 2 * (q1 * q3 - q0 * q2);
    vy = 2 * (q0 * q1 + q2 * q3);
    vz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;

    //叉积来计算估算的重力和实际测量的重力这两个重力向量之间的误差。
    ex = ay * vz - az * vy;
    ey = az * vx - ax * vz;
    ez = ax * vy - ay * vx;

    //用叉乘误差来做PI修正陀螺零偏，
    m_integralErrorX += HalfT * ex;
    m_integralErrorY += HalfT * ey;
    m_integralErrorZ += HalfT * ez;

    gx += (AHRS_Kp * ex + AHRS_Ki * m_integralErrorX);
    gy += (AHRS_Kp * ey + AHRS_Ki * m_integralErrorY);
    gz += (AHRS_Kp * ez + AHRS_Ki * m_integralErrorZ);

    /*数据修正完成，下面是四元数微分方程*/

    //四元数微分方程，其中halfT为测量周期的1/2，gx gy gz为陀螺仪角速度，以下都是已知量，这里使用了一阶龙哥库塔求解四元数微分方程
    q0 += (-q1 * gx - q2 * gy - q3 * gz) * HalfT;
    q1 += ( q0 * gx + q2 * gz - q3 * gy) * HalfT;
    q2 += ( q0 * gy - q1 * gz + q3 * gx) * HalfT;
    q3 += ( q0 * gz + q1 * gy - q2 * gx) * HalfT;

    //normalise quaternion
    norm = fast_sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 *= norm;
    q1 *= norm;
    q2 *= norm;
    q3 *= norm;

    g_eulerAngle.pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.295779513082f; // pitch
    g_eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.295779513082f; // roll
    g_eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 57.295779513082f; // yaw


}

void IMU_get_euler(void)
{
    IMU_get_values();
    IMU_AHRSupdate(g_imuData.gyroX, g_imuData.gyroY, g_imuData.gyroZ, g_imuData.accX, g_imuData.accY, g_imuData.accZ);
    ips200_show_float(0,32,imu660ra_acc_z,4,4);
    ips200_show_float(0,64,g_imuData.accZ,4,4);
    IMU_Flag=0;

}
