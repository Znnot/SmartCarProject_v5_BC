///*
// * Menu.h
// *
// *  Created on: 2023脛锚10脭脗18脠脮
// *      Author: 23913
// */
//
//#ifndef MENU_H_
//#define MENU_H_
//extern int set_flag;
//#define FLASH_PAGE_INDEX          10                              // 存储数据用的页码
///*先在这里想好那些变量需要写进flash中
// *encoder.c  中的   Steer_PID.Kp   float     flash_data_union_buffer[0].float_type   结构体变量 不需要特殊读取
// *encoder.c  中的   Steer_PID.Kd   float     flash_data_union_buffer[1].float_type   结构体变量 不需要特殊读取
// *encoder.c  中的   Motor_Left_PID.Kp        float     flash_data_union_buffer[2].float_type   结构体变量 不需要特殊读取
// *encoder.c  中的   Motor_Left_PID.Ki        float     flash_data_union_buffer[3].float_type  结构体变量 不需要特殊读取
// *encoder.c  中的   Motor_Right_PID.Kp       float     flash_data_union_buffer[4].float_type   结构体 不需要特殊读取
// *encoder.c  中的   Motor_Right_PID.Kd       float     flash_data_union_buffer[5].float_type   结构体 不需要特殊读取
// *encoder.c
// */
//
//typedef struct{
//    int16 menu_id;
//    char func[30];
//    void (*menu_action)(float *param, char func[30]);
//    float *param;
//}menu_item;
//void Parameters_Read(void);         //把Flash中的值读出来
//void First_Flash_Write(void);
//void Ips_Init(void);
//void menu_action(float *param,char func[30]);
//void key_read(void);
//void Menu_Switch(void);
//void Menu_Open(void);
//#endif /* MENU_H_ */
