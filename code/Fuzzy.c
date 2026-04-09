/*
 * Fuzzy.c
 *
 *  Created on: 2023年11月4日
 *      Author: 23913
 */
#include  "Fuzzy.h"
#include  "Encoder.h"
#include   "pid.h"
#include "control.h"
#include "camera.h"
//***************参数信息*****************//
//中线偏差值 一般不需改动
#define MAX_ERR 50
#define MIN_ERR -50
//误差最大变化值 这里作为可调节参数
float MAX_CERR=20;
//一次模糊调节前中后期P的变化：增大-减小-增大
//一次模糊调节前中后期D的变化：增大-减小-减小
//以下参数尽量不去动先
float MAX_DP=2;
float MAX_DD=3;
float min_kp=12;
float max_kp=15;//24.8
float min_kd=58;
float max_kd=62;//63.3
float error;        //误差值
float error_c;      //误差变化值
float last_error;
float Membership[2];
int Index[2];
float CMembership[2];
int CIndex[2];
float KP;
float KD;
//*******************************************************
/*************************模糊规则***********************/
int8 KPFuzzyRule[7][7]={{PB,PB,PM,PM,PS,ZO,ZO},
                         {PB,PB,PM,PS,PS,ZO,NS},
                         {PM,PM,PM,PS,ZO,NS,NS},
                         {PM,PM,PS,ZO,NS,NM,NM},
                         {PS,PS,ZO,NS,NS,NM,NM},
                         {PS,ZO,NS,NM,NM,NM,NB},
                         {ZO,ZO,NM,NM,NM,NB,NB}};//KP参数的模糊规则表
int8 KIFuzzyRule[7][7]={{NB,NB,NM,NM,NS,ZO,ZO},
                         {NB,NB,NM,NS,NS,ZO,ZO},
                         {NB,NM,NS,NS,ZO,PS,PS},
                         {NM,NM,NS,ZO,PS,PM,PM},
                         {NM,NS,ZO,PS,PS,PM,PB},
                         {ZO,ZO,PS,PS,PM,PB,PB},
                         {ZO,ZO,PS,PM,PM,PB,PB}};//KI参数的模糊规则表
int8 KDFuzzyRule[7][7]={{PS,NS,NB,NB,NB,NM,PS},
                         {PS,NS,NB,NM,NM,NS,ZO},
                         {ZO,NS,NM,NM,NS,NS,ZO},
                         {ZO,NS,NS,NS,NS,NS,ZO},
                         {ZO,ZO,ZO,ZO,ZO,ZO,ZO},
                         {PB,NS,PS,PS,PS,PS,PB},
                         {PB,PM,PM,PM,PS,PS,PB}};//KD参数的模糊规则表
//区间映射函数 论域[-3,3],使用两次e/ec
float Fuzzy_Mapping(float maximum,float minimum,float x){
        float qvalues= 6.0 *(x-minimum)/(maximum - minimum)-3;
        return qvalues;
}
//反映射函数
float Inverse_quantization(float maximum, float minimum, float qvalues)
{
    float x = (maximum - minimum) *(qvalues + 3)/6 + minimum;
    return x;
}

void ClacMembership(float E,float Membership[2],int Index[2])
{
    /*三角隶属度函数*/
    if(E>=NB && E<=NM)
    {
        Index[0]=0;//NB
        Index[1]=1;//NM
        Membership[0]=NM-E;//隶属于NB的隶属度(NM-E)/(NM-NB)，因为分母都是1
        Membership[1]=E-NB;//隶属于NM的隶属度(E-NB)/(NM-NB)
    }
    else if(E>=NM && E<=NS)
    {
        Index[0]=1;
        Index[1]=2;
        Membership[0]=NS-E;//隶属于NM的隶属度
        Membership[1]=E-NM;//隶属于NS的隶属度
    }
    else if(E>=NS && E<=ZO)
    {
        Index[0]=2;
        Index[1]=3;
        Membership[0]=ZO-E;//隶属于NS的隶属度
        Membership[1]=E-NS;//隶属于ZO的隶属度
    }
    else if(E>=ZO && E<=PS)
    {
        Index[0]=3;
        Index[1]=4;
        Membership[0]=PS-E;//隶属于ZO的隶属度
        Membership[1]=E-ZO;//隶属于PS的隶属度
    }
    else if(E>=PS && E<=PM)
    {
        Index[0]=4;
        Index[1]=5;
        Membership[0]=PM-E;//隶属于PS的隶属度
        Membership[1]=E-PS;//隶属于PM的隶属度
    }
    else if(E>=PM && E<=PB)
    {
        Index[0]=5;
        Index[1]=6;
        Membership[0]=PB-E;//隶属于PS的隶属度
        Membership[1]=E-PM;//隶属于PM的隶属度
    }
}

int  SolutionFuzzy(int IndexE[2],float MSE[2],int IndexEC[2],float MSEC[2],int type)
{
    int temp=0;
    switch(type)
    {
        case 1:
            //重心法求解
            temp=KPFuzzyRule[IndexE[0]][IndexEC[0]]*MSE[0]*MSEC[0]+
                 KPFuzzyRule[IndexE[0]][IndexEC[1]]*MSE[0]*MSEC[1]+
                 KPFuzzyRule[IndexE[1]][IndexEC[0]]*MSE[1]*MSEC[0]+
                 KPFuzzyRule[IndexE[1]][IndexEC[1]]*MSE[1]*MSEC[1];
            break;
        case 2:
            temp=KIFuzzyRule[IndexE[0]][IndexEC[0]]*MSE[0]*MSEC[0]+
                 KIFuzzyRule[IndexE[0]][IndexEC[1]]*MSE[0]*MSEC[1]+
                 KIFuzzyRule[IndexE[1]][IndexEC[0]]*MSE[1]*MSEC[0]+
                 KIFuzzyRule[IndexE[1]][IndexEC[1]]*MSE[1]*MSEC[1];
            break;
        case 3:
            temp=KDFuzzyRule[IndexE[0]][IndexEC[0]]*MSE[0]*MSEC[0]+
                 KDFuzzyRule[IndexE[0]][IndexEC[1]]*MSE[0]*MSEC[1]+
                 KDFuzzyRule[IndexE[1]][IndexEC[0]]*MSE[1]*MSEC[0]+
                 KDFuzzyRule[IndexE[1]][IndexEC[1]]*MSE[1]*MSEC[1];
            break;
        default:
            break;
    }
    return temp;
}
void Fuuzy_pid(void){
    error=(float)ImageStatus.Det_True;
    error_c=error-last_error;
    float MIN_CERR=-1*MAX_CERR;
    float MIN_DP=-1*MAX_DP;
    float MIN_DD=-1*MAX_DD;
    float E=Fuzzy_Mapping(MAX_ERR,MIN_ERR,error);
    float EC=Fuzzy_Mapping(MAX_CERR,MIN_CERR,error_c);
    ClacMembership(E,Membership,Index);
    ClacMembership(EC,CMembership,CIndex);
    int DP=SolutionFuzzy(Index,Membership,CIndex,CMembership,1);//KP
    int DD=SolutionFuzzy(Index,Membership,CIndex,CMembership,3);//KD
    float dp=Inverse_quantization(MAX_DP, MIN_DP,(float)DP);
    float dd=Inverse_quantization(MAX_DD, MIN_DD,(float)DD);
    Steer_PID.Kp+=dp;
    Steer_PID.Kd+=dd;
    //**************调参中最直观的地方：改阈值
    Steer_PID.Kp=Steer_PID.Kp>max_kp?max_kp:Steer_PID.Kp;
    Steer_PID.Kp=Steer_PID.Kp<min_kp?min_kp:Steer_PID.Kp;
    Steer_PID.Kd=Steer_PID.Kd>max_kd?max_kd:Steer_PID.Kd;
    Steer_PID.Kd=Steer_PID.Kd<min_kd?min_kd:Steer_PID.Kd;
    Steer_PID.Kd=59;
//    Steer_PID.Kp=13.5;
    //***************最小值尽量不动（或者提速时最后动）可以改上限值，和普通pd调参一样
    last_error=error;
}
