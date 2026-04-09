/*
 * test.c
 *
 *  Created on: 2023年10月9日
 *      Author: Administrator
 */
#include "zf_common_headfile.h"
#include "camera.h"

/***********************************************
* @brief :调用函数直接在屏幕上标记出中线
* @param :StartLine-开始行，取值【0，LCDH-1】
*         EndLine-结束行，取值【0，StartLine-1】
*         StartLine>EndLine
* @return:无
* @date  :231009
* @author:ZWF
************************************************/
void Draw_Midline_On_Image(int StartLine,int EndLine)
{
    int i,temp;
    for(i=StartLine;i>=EndLine;i--)
    {
        temp=ImageDeal[i].Center;
//        Image_Pixel[i][temp]=0;
    }
}

//可能会用到*********************************************************************************************************************
//ips114_show_gray_image(0, 30, Image_Pixel[0], LCDW, LCDH, LCDW, LCDH, Get_Threshold(Image_Use,LCDW,LCDH));
//【上面这句——230916给的阈值是固定的100，0917下午换回大津法阈值了，看下是不是还能正常显示】
//        ips114_displayimage03x(Image_Pixel[0], 100, 60);//【注释掉上面的一句，看这一行能不能正常显示——不可以】
//        ips114_show_uint(100,100,Get_Threshold(Image_Use,LCDW,LCDH),4);

////            ips114_show_uint(70,70,Get_Threshold(Image_Use,LCDW,LCDH),4);
////            ips114_show_uint(120,120,ImageDeal[i].Center,4);
////            ips114_show_uint(70,70,Get_Threshold(Image_Use,LCDW,LCDH),4);
//        ips114_show_uint(90,90,ImageDeal[30].LeftBorder,4);//显示这个数据是个定值——3107？why？就是因为3107超过了屏幕范围，所以画点会报错
//        ips114_show_uint(100,100,ImageDeal[30].Center,4);//【为什么值会都是0呀？——因为都没调用Get_BaseLine函数】
//        ips114_show_uint(110,110,ImageDeal[30].RightBorder,4);


//    encoder_quad_init(TIM1_ENCOEDER,TIM1_ENCOEDER_MAP3_CH1_E9,TIM1_ENCOEDER_MAP3_CH2_E11);//带方向编码器初始化
//    encoder_quad_init(TIM8_ENCOEDER,TIM8_ENCOEDER_MAP0_CH1_C6,TIM8_ENCOEDER_MAP0_CH2_C7);
//    pwm_init(TIM8_PWM_MAP1_CH4_C13, 3000, 6000);//令蜂鸣器响，没重新置零就一直响【可】
//    system_delay_ms(1000);//延时
//    set_whole_speed(1200);//设置后轮总速度【可】
//    pwm_init(TIM2_PWM_MAP3_CH1_A15, 50, 780);//舵机pwm
//*****************************************************************************************/

//        pwm_init(TIM2_PWM_MAP3_CH1_A15, 50, steer_pid(5,1));//pid控制舵机

//        ips114_show_rgb565_image(0,0,mt9v03x_image[0],LCDW/2,LCDH/2,LCDW/2,LCDH/2,1);//彩图，想想为什么除以2
//        ips114_show_binary_image(0,0,mt9v03x_image[0],LCDW,LCDH,LCDW,LCDH);//二值化图
//        Image_CompressInit();
//        Get_BinaryImage();
//        ips114_show_binary_image(0,0,Image_Pixel[0],LCDW,LCDH,200,120);
//        ips114_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 150);

//        wireless_uart_send_image(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);

        //读两个编码器值，打印到屏幕上
        //编码器不转是0，为什么屏幕读一个运行方向的轮会一直正负变化？
//        ips114_show_int(30,30,encoder_get_count(TIM1_ENCOEDER),4);
//        ips114_show_int(30,50,encoder_get_count(TIM3_ENCOEDER),4);
//        system_delay_ms(1000);

//        ips114_displayimage03x(*Image_Use[0], 100, 60);
//        ips114_displayimage03x(mt9v03x_image[0], 100, 60);
//        ips114_displayimage03x(Image_True[0],100,60);//显示全黑
//改LCDH*LCDW为60*94并压缩图像后，【ips114_displayimage03x(*Image_Use[0], 100, 60);】可以显示，但【Image_True】就有问题了//只显示顶上一小部分

//        ips114_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,Get_Threshold(Image_Use,100,60));

//        ips114_displayimage03x(Image_Pixel[0], 60, 100);//注意会不会和CompressInit都一直在给Image_Use赋值
//        ips114_displayimage03x(*Image_Use[0], 100, 60);
//        ips114_show_binary_image(0,50,Image_Pixel[0],100,60,100,60);//【显示黑白条纹，会不会是显示函数的问题】
//        system_delay_ms(1000);
//        Get_BaseLine();
//***********************
//        for(int i=1200;i<3200;i+=1000)
//        {
//            system_delay_ms(1000);
//            set_whole_speed(i);//设置后轮总速度【可】
//        }

//        encoder_dir_init(TIM1_ENCOEDER, TIM1_ENCOEDER_MAP3_CH1_E9, TIM1_ENCOEDER_MAP3_CH2_E11);//带方向正交编码器初始化
//        encoder_dir_init(TIM3_ENCOEDER, TIM3_ENCOEDER_MAP3_CH1_C6 , TIM3_ENCOEDER_MAP3_CH2_C7);
//        ips114_show_int(30,30,encoder_get_count(TIM1_ENCOEDER),4);
//        ips114_show_int(30,50,encoder_get_count(TIM3_ENCOEDER),4);
//        printf("%d,%d\n",encoder_get_count(TIM1_ENCOEDER),encoder_get_count(TIM3_ENCOEDER));

//        pwm_init(TIM2_PWM_MAP3_CH1_A15, 50, 820);//PD控制舵机【前提是ImageDeal[20].Center有赛道中线的值】
//        TIM6_IRQHandler();
//        ips114_show_uint(70,70,count,4);

//        interrupt_enable(66);//TIM5
//        TIM2_IRQHandler(66);
//*******************8
//        printf("%d,%d\n",data1,data2);//用WCHLinkE接电脑可以在VOFA+上打印波形
//        Get_BinaryImage();
//        ips114_show_gray_image(0, 30, Image_Pixel[0], LCDW, LCDH, LCDW, LCDH, Get_Threshold(Image_Use,LCDW,LCDH));
//
//        Get_BaseLine();
//******************
//用画点函数把扫描到的图像【左中右】线画成【红绿蓝】出来********************************************************

//
////        system_delay_ms(200);
