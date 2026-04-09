/*
 * pid.c
 *
 *  Created on: 2023骞�8鏈�15鏃�
 *      Author: Ming
 */
#include "zf_common_headfile.h"
#include "camera.h"
#include "pid.h"
#include"Encoder.h"
#include "control.h"
#include"Fuzzy.h"

#define speed_pwm_max 1500//璁剧疆鍚庤疆鐢垫満鏈�澶wm浠ラ檺骞�
#define speed_pwm_min -1500//璁剧疆鍚庤疆鐢垫満鏈�灏弍wm浠ラ檺骞�
#define steer_pwm_max 850//舵机打角最大角度//左
#define steer_pwm_min 700//右
int16 SteerPWM=0;
int16 steer_center =775;//中值
float KP2;
int fuzzy_flag=0;
float str=0;
//pid閮ㄥ垎鈥斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺�斺��
void steer_pid(pid_param_t Steer_pid)//浣嶇疆寮廝D锛涘弬鏁帮細PD涓や釜绯绘暟
{
    int error=0;
    static int last_error=0;
    float pid_value=0;//pid鐨勮緭鍑�
    float pwm_steer=steer_center;//鏈�鍚庤缁欒埖鏈虹殑pwm
    float Kp;  //鍔ㄦ�丳
    float Kd;

    error=SecondOrderLagFilter_steer(ImageStatus.Det_True);//图像中线偏差（经过一个简单的滤波，但本质没啥区别）

    Kp=Steer_pid.Kp;
    Kd=Steer_pid.Kd;
//    diff_xishu=0.0013;
 if(error>0)//这里想的是用err的平方和某个系数的组合来代替err可以在误差比较小时让舵机的打角小一些，用来改善路径，防止后车抄近道，系数后期可以尝试更换
        pid_value = Kp*error*error*75/1936.0 + Kd*(error-last_error);//1936=44*44，本意为当偏差大于等于44时舵机有最大打角（kp为1的前提下）
    else
        pid_value = -Kp*error*error*75/1936.0 + Kd*(error-last_error);//75则与舵机的打脚限幅有关，比如我们的700  775    850，750为中值，700为右max，850为左max

    last_error=error;
    pwm_steer = steer_center + pid_value;
    str=pid_value;
    pwm_steer=pwm_steer>steer_pwm_max?steer_pwm_max:pwm_steer;//限幅
    pwm_steer=pwm_steer<steer_pwm_min?steer_pwm_min:pwm_steer;
    SteerPWM=pwm_steer;
    pwm_set_duty(ATOM1_CH1_P33_9, (int16)pwm_steer);//最终输出到舵机
}
/***********************************************
* @brief :bangbang鎺у埗
* @param :expspeed pid璁＄畻鍑虹殑鏈熸湜閫熷害
* *respeed 瀹為檯閫熷害
* *x 寮�鍏抽槇鍊�
* @return:repwm 闃堝�间唬鏇縫wm_L/pwm_R
* @date  :240110
* @author:T
************************************************/
int16 bangbang(int16 error,uint16 x,uint16 y){
    int16 repwm;
    if(error>x){
        repwm=9000;//锟斤拷锟斤拷锟斤拷//9000
    }
    else if(error<(-y)){
        repwm=-6500;//锟斤拷锟斤拷锟斤拷
    }
    else{
        repwm=0;
    }
    return repwm;
}

/***********************************************
* @brief :瀹炵幇閫熷害闂幆
* @param :pid_param_t motorL_pid锛氬瓨鏀綪ID鍊肩殑缁撴瀯浣�
        * int16 enco_true锛氫紶鍏ョ紪鐮佸櫒閲囩殑鑴夊啿鍊�
        * int16 enco_wish锛氭湡鏈涜剦鍐�
* @return:int16 pwm_L 璧嬬粰鐢垫満
* @date  :231008
* @author:T
************************************************/

//瑕佺敤KD鍙傛暟鍚楋紵锛堝闀夸唬鐮佺敤鐨勬槸PI锛�

int16 motorL_pid(pid_param_t motorL_pid,int16 enco_true,int16 enco_wish)//澧為噺寮廝I
{

    static int16 error=0;
    static int16 last_error=0;
    static int16 pwm_L=0;
    error=enco_wish-enco_true;
    pwm_L += motorL_pid.Kp*(error-last_error) + motorL_pid.Ki*error ;
               if(pwm_L>6000){
                  pwm_L=6000;}
               else if(pwm_L<=-6000){
                   pwm_L=-6000;}
    last_error=error;
    return pwm_L;
}

int16 motorR_pid(pid_param_t motorR_pid,int16 enco_true,int16 enco_wish)//澧為噺寮廝I
{

    static int16 error=0;
    static int16 last_error=0;
    static int16 pwm_R=0;
    error=enco_wish-enco_true;
    pwm_R += motorR_pid.Kp*(error-last_error) + motorR_pid.Ki*error ;
               if(pwm_R>6000){
                  pwm_R=6000;}
               else if(pwm_R<=-6000){
                   pwm_R=-6000;}
    last_error=error;
    return pwm_R;
}


/***********************************************
* @brief :浣嶇疆寮弍id瀹炵幇浣嶇疆鐜�
* @param :pid_param_t Posit_pid锛歅ID鍙傛暟,enco_true锛氬疄闄呭�硷紙缂栫爜鍣ㄧ疮鍔犲�硷級锛宔nco_wish锛氱洰鏍囧�硷紙鐩爣浣嶇疆锛�
* @return:int16 output浣滀负鍐呯幆閫熷害鐜緭鍏�
* @date  :231008
* @author:T
************************************************/
int16 position_pid(pid_param_t Posit_pid,int16 enco_true,int16 enco_wish)
{
        static int16 error,sum_error,last_error=0;
        static int16 output=0;
        error = enco_wish-enco_true;
        sum_error+=error;
        output = Posit_pid.Kp*error+Posit_pid.Ki*sum_error+Posit_pid.Kd*(error-last_error);
        if(output>2000){
            output=2000;}
        else if(output<0){
            output=0;}
        last_error=error;
        return output;
}

///***********************************************
//* @brief :鍓嶉PID锛屼粎妯℃澘锛孴e=0.0005*n+B*w
//                            I=Te/Kt/蠁
//                            U=I*R+Ke*蠁*w,鍏朵腑w=n*pi/30
//*
//* @param :
//* @return:
//* @date  :231008
//* @author:T
//************************************************/

//void FFCInit(FFC* ffc,float conf_1,float conf_2,float conf_3)
//{
//    ffc->conf_1 = conf_1;
//    ffc->conf_2 = conf_2;
//    ffc->conf_3 = conf_3;
//    ffc->iuput = 0;
//    ffc->last_input = 0;
//    ffc->pre_input = 0;
//    ffc->output = 0;
//}
///***********************************************
//* @brief : 鍓嶉PID
//* @param : target:鍓嶉鎺у埗杈撳叆
//*          ffc:鍓嶉鎺у埗缁撴瀯浣�
//* @return: ffc->output:鍓嶉鎺у埗杈撳嚭閲�
//* @date  : 2023.6.7
//* @author: L
//************************************************/
//int FeedForwardCtrl(int target,FFC* ffc)
//{
//    ffc->iuput = target;
//
//    ffc->output = (int)(ffc->conf_1*(ffc->iuput-ffc->last_input)+ffc->conf_2*(ffc->iuput-2*ffc->last_input+ffc->pre_input))+ffc->conf_3;
//
//    ffc->pre_input = ffc->last_input;
//    ffc->last_input = ffc->iuput;
//
//    if(ffc->output>5000) ffc->output=5000;
//    else if(ffc->output<-5000) ffc->output=-5000;
//    return ffc->output;
//}


