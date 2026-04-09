
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"

#define fuya_flag 1

int core0_main(void)
{
    clock_init();
    debug_init();

//751
    pwm_init(ATOM1_CH1_P33_9, 50, 770);                     //舵机中值初始化
    PID_Init();                                             //pid初始化
    ips200_set_dir(IPS200_PORTAIT);                     //屏幕初始化
    ips200_init(IPS200_TYPE_SPI);
//    ips114_init();
    gpio_init(P02_6,GPI,1, GPI_PULL_UP);//按键初始化
    gpio_init(P10_3, GPO, GPIO_LOW, GPO_PUSH_PULL);         //蜂鸣器初始化
    gpio_init(P11_2, GPI, 0, GPI_PULL_DOWN);                //拨码开关1初始化
    mt9v03x_init();                                         //摄像头初始化
    Image_CutInit();                                        //图像指针映射
    /************menu*******************/
//      Menu_Open();
    /************menu*******************/
    PWMInit();                                               //PWM初始化
    uart_init(UART_2,115200,UART2_TX_P10_5,UART2_RX_P10_6);
    uart_rx_interrupt(UART_2, 1);
//    tof_Init();
//    kalman1_init(&tof,0.001,0.005);
    Encoder_init();                                         //编码器初始化
    pit_ms_init(CCU60_CH0,2);                               //编码器中断
    pit_ms_init(CCU60_CH1,10);                              //舵机中断
//    pit_ms_init(CCU61_CH0,4);                               //出界保护
//    pit_ms_init(CCU61_CH1,2);

    cpu_wait_event_ready();
    while (TRUE)
    {
        if(cc60_ch0_flag==1)
        {
            printf("%.2f,%.2f,%.2f,%.2f,%.2f\n",(float)SteerPWM,(float)ENCO_Wish_L,(float)ENCO_Wish_R,(float)encoder_data_1,(float)encoder_data_2);
            if(go!=1){//按下按键才会启动
                     if(gpio_get_level(P20_10)==0){
                         system_delay_ms(5);//延时10MS，消抖滤波
                         if(gpio_get_level(P20_10)==0){
                             go=1;
                         }
                     }
                 }
            if(go==1){
                Motor_control();
            }
            else{//按键没按下不启动
                pwm_set_duty(ATOM0_CH0_P21_2,0);
                pwm_set_duty(ATOM0_CH1_P21_3,0);
                pwm_set_duty(ATOM0_CH2_P21_4,0);
                pwm_set_duty(ATOM0_CH3_P21_5,0);
            }

            cc60_ch0_flag=0;
        }
        else if(cc60_ch1_flag==1)
        {//舵机中断
            cc60_ch1_flag=0;
        }

    }
}

void uart_rx_interrupt_handler (void)
{
//    get_data = uart_read_byte(UART_INDEX);
//    printf("%.2f,%.2f,%.2f,%.2f,%.2f",1,1,0,0,0);
//             printf("\n");// 接收数据 while 等待式 不建议在中断使用
    uart_query_byte(UART_2, &RxBuffer[0]);                                     // 接收数据 查询式 有数据会返回 TRUE 没有数据会返回 FALSE
    RxLine++;
        DataBuff[RxLine - 1] = RxBuffer[0];
//        printf("%.2f,%.2f,%.2f,%.2f,%.2f",RxBuffer[0],RxLine,1,0,0);
//                     printf("\n");
        if (RxBuffer[0] == '!')
             {
                 printf("RXLen=%d\r\n", RxLine);
                for (int i = 0; i < RxLine; i++)
                    printf("UART DataBuff[%d] = %c\r\n", i, DataBuff[i]);

                 USART_PID_Adjust(1);
                 memset(DataBuff, 0, sizeof(DataBuff));
                 RxLine = 0;
             }
}


#pragma section all restore


