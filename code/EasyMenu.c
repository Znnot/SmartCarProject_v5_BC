// * Menu.c
// *
// *  Created on: 20231018
// *      Author: 23913
// */
#include "zf_common_headfile.h"
#include "pid.h"
#include "menu.h"
#include"Encoder.h"
#define BEEP                (P20_8)
#include"control.h"
    uint8 Flash_Jump = 0;   //结束调参
    int set_flag=0;
    float t=164;
    uint8 loop = 0;
    uint8 count_beep = 0;
    key_index_enum key_index_array[KEY_NUMBER] = {KEY_1,KEY_2,KEY_3,KEY_4,KEY_5};
    uint8 View_Flag=1;      //注意初始化是1，看图像时是0
    uint8 Podao_Flag=1;
    //----------------------------------------------------------------------
    //  函数简介    菜单开启
    //  参数说明    空
    //  返回参数    空
    //  使用示例    Menu_Open();
    //  备注信息    直接调用
    //----------------------------------------------------------------------
void Menu_Open(void){
        menu_flag=1;
        key_init(10);
        pit_ms_init(CCU61_CH1,15);
        Ips_Init();
        Parameters_Read();
        Menu_Switch();
        Parameter_init();
        ips200_clear();

}
//----------------------------------------------------------------------
//  函数简介        第一次写入Flash 或者 添加了变量 或者变量参数修改后需要再次重新写入Flash时 需要开启这个函数
//涉及到清除Flash中的垃圾数据
//第一次写入后务必关闭这个函数再次下载程序（需要进入到调参界面之后再关闭，但是不要动参数）
//以后就可以正常操作Flash了
//如修改后报错或卡死 单独使用 flash_erase_page(0,FLASH_PAGE_INDEX); flash_buffer_clear();
//  参数说明    空
//  返回参数    空
//  使用示例    空
//  备注信息    内部调用
//----------------------------------------------------------------------

// 请注意 数据缓冲区的每个位置只能存储一种类型的数据
  // 例如 flash_data_union_buffer[0] 写入 int8_type 那么只能以 int8_type 读取
  // 同样 flash_data_union_buffer[0] 写入 float_type 那么只能以 float_type 读取
    void First_Flash_Write()
    {
        flash_erase_page(0,FLASH_PAGE_INDEX);                // //管它有没有数据，直接擦除这一页
        flash_buffer_clear();                        // 清空缓冲区
        flash_union_buffer[0].float_type = 0;     //element_data[1].addbasic_speed
        flash_union_buffer[1].float_type = 0;     //element_data[2].addbasic_speed
        flash_union_buffer[2].float_type = 0;     //element_data[3].addbasic_speed
        flash_union_buffer[3].float_type = 0;     //element_data[4].adddynamic_H_speed
        flash_union_buffer[4].float_type = 0;     //element_data[4].adddynamic_L_speed
        flash_union_buffer[5].float_type = 0;     //ring_data[2].addring_exter_speed
        flash_union_buffer[6].float_type = 0;     //ring_data[2].addring_inter_speed
        flash_union_buffer[7].float_type = 0;     //ring_data[1].addring_exter_speed
        flash_union_buffer[8].float_type = 0;     //ring_data[1].addring_inter_speed
        flash_union_buffer[9].float_type = 200;     //ring_data[3].ring_size_threshold
        flash_union_buffer[10].float_type =13;      //ring_data[3].half_wide_offset_big
        flash_union_buffer[11].float_type=30;       //ring_data[3].half_wide_offset_small
        flash_union_buffer[12].float_type=0;       //addLFuya
        flash_union_buffer[13].float_type=0;       //addMFuya
        flash_union_buffer[14].float_type=0;       //addHFuya
        flash_union_buffer[15].float_type=23000;       //element_data[3].integral
        flash_union_buffer[16].float_type=10;       //Cross_white_line
//        flash_union_buffer[17].float_type=512;      //MT9V03X_EXP_TIME_DEF
        flash_write_page_from_buffer(0, FLASH_PAGE_INDEX);     //   // 向指定 Flash 扇区的页码写入缓冲区数据
        flash_buffer_clear();                                                  // 清空缓冲区
    }
    //----------------------------------------------------------------------
    //  函数简介    flash数值赋值给实际使用变量
    //  参数说明    空
    //  返回参数    空
    //  使用示例    空
    //  备注信息    内部调用
    //----------------------------------------------------------------------
    void Parameters_Read()
    {
        flash_buffer_clear();
        flash_read_page_to_buffer(0, FLASH_PAGE_INDEX);      // 灏嗘暟鎹粠 flash 璇诲彇鍒扮紦鍐插尯
        system_delay_ms(200); //鍔″繀寤舵椂
        Parameter_init();
        system_delay_ms(200); //鍔″繀寤舵椂
    }
    //----------------------------------------------------------------------
    //  函数简介    按键响蜂鸣器
       //  参数说明    空
       //  返回参数    空
       //  使用示例     key_read(void);
       //  备注信息    放定时中断，注意定时时长不能太断，容易读不到按键
    //----------------------------------------------------------------------
void key_read(void){

    for(loop = 0; loop < 7; loop ++)
    {
        switch(key_get_state(key_index_array[loop]))                        // 鑾峰彇鎸夐敭鐘舵��
        {
            case KEY_SHORT_PRESS:                                           // 鐭寜鐘舵��

                    gpio_set_level(BEEP, GPIO_HIGH);                        // BEEP 鍝�

                break;
            case KEY_LONG_PRESS:                                            // 闀挎寜鐘舵��

                    gpio_set_level(BEEP, GPIO_HIGH);                        // BEEP 鍝�

                break;
            default:
                break;
        }
    }
    if( KEY_RELEASE == key_get_state(KEY_1) && \
        KEY_RELEASE == key_get_state(KEY_2) && \
        KEY_RELEASE == key_get_state(KEY_3) && \
        KEY_RELEASE == key_get_state(KEY_4) && \
        KEY_RELEASE == key_get_state(KEY_5)
       )//如果所有的按键都没有值
    {
        gpio_set_level(BEEP, GPIO_LOW);                                     // BEEP 鍋�

    }

}
//----------------------------------------------------------------------
//  函数简介    IPS屏幕初始化
//  参数说明    空
//  返回参数    空
//  使用示例    Ips_Init();
//  备注信息    空
//----------------------------------------------------------------------
void Ips_Init(void){
       ips200_set_dir(IPS200_PORTAIT_180);
       ips200_set_font(IPS200_8X16_FONT);
       ips200_set_color(RGB565_RED, RGB565_BLACK);
       ips200_init(IPS200_TYPE_PARALLEL8);
       ips200_show_string(0, 0, "Loading...");                     // 鍧愭爣0,0鍐欎竴涓瓧绗
}


menu_item* new_menu=0;

//----------------------------------------------------------------------
//  函数简介    菜单调参执行函数
//              设置KEY4为调节单位 KEY5为返回上级菜单 KEY6为退出调参
//  参数说明    *param 传入的参数 func[30]执行函数的名称
//  返回参数    空
//  使用示例    空
//  备注信息    内部调用
//----------------------------------------------------------------------
void menu_action(float *param,char func[30])
{
     //   First_Flash_Write();
        ///首次写入需要开启此函数，看函数注释
         flash_buffer_clear();
         flash_read_page_to_buffer(0, FLASH_PAGE_INDEX);      // 将数据从 flash 读取到缓冲区
         system_delay_ms(50);
       float last_param;
       char buf[30]; // 存放名称
       char *menu_name = func;
       static int current_level = 0;
       float level[4] = {1,10,1000,0.01};//调节挡位
       while (1)
       {
           ips200_show_string(0, 16*3, "UseKey4ForSettingLevel");
           sprintf(buf, "%s: ", menu_name);
           ips200_show_string(0, 16*1, buf);
           sprintf(buf, "%5.6f", *param);
           ips200_show_string(0, 16*2, buf);
           last_param=*param;
               if(key_get_state(KEY_4)==KEY_SHORT_PRESS)
               {
                   ips200_clear();
                   key_clear_state(KEY_4);
                   while(1){
                       ips200_show_string(0, 16*0, "CHANGING LEVEL");
                       sprintf(buf, "X%5.2f: ", level[current_level]);
                       //把level[current_level]按格式写到字符数组buf,将会显示“X LEVEL:”
                       ips200_show_string(0, 16*1, buf);
                   if (KEY_SHORT_PRESS==key_get_state(KEY_1))
                   {
                       if(current_level<sizeof(level)/sizeof(level[0])-1)current_level++;
                                  key_clear_state(KEY_1);

                    }
                   if (KEY_SHORT_PRESS==key_get_state(KEY_2))
                   {
                       if(current_level>0)current_level--;
                                  key_clear_state(KEY_2);

                    }
                   if(KEY_SHORT_PRESS==key_get_state(KEY_5)){
                                   return;
                   }
                   }
               }

                                                   if (KEY_SHORT_PRESS==key_get_state(KEY_1))
                                                   {
                                                       *param +=level[current_level];
                                                       key_clear_state(KEY_1);
                                                   }
                                                   else if (KEY_SHORT_PRESS==key_get_state(KEY_2))
                                                   {
                                                       *param -= level[current_level];
                                                       key_clear_state(KEY_2);
                                                   }
                                                   else if (KEY_SHORT_PRESS==key_get_state(KEY_5)){
                                                       if(last_param!=*param){
                                                           Flash_Jump = 1;
                                                       }
                                                       return ;
                                                   }
       }
}
void menu_11(void){
    ips200_clear();
     View_Flag=0;
      return;
    //执行任务项
}
void menu_12(void){
    ips200_clear();
    Podao_Flag=!Podao_Flag;
    while(1){
    ips200_show_int(0,0,Podao_Flag,3);
    ips200_show_string(0, 30, "Now Podao_Flag");
    if(KEY_SHORT_PRESS==key_get_state(KEY_5))  return ;
    }
    //执行任务项
}

menu_item menus[]={
        {1,"Control",NULL,NULL},
        {2,"Picture",NULL,NULL},
        {3,"FuYa",NULL,NULL},
        {4,"Integral",menu_action,&flash_union_buffer[15].float_type},
        {5,"View",menu_11,NULL},
        {6,"Podao",menu_12,NULL},
        {11,"AddZhidao",menu_action,&flash_union_buffer[0].float_type},
        {12,"AddWandao",menu_action,&flash_union_buffer[1].float_type},
        {13,"AddPodao",menu_action,&flash_union_buffer[2].float_type},
        {14,"adddynamic_H_speed",menu_action,&flash_union_buffer[3].float_type},
        {15,"adddynamic_L_speed",menu_action,&flash_union_buffer[4].float_type},
        {17,"SetRing",NULL,NULL},
        {171,"BigAddring_exter_speed",menu_action,&flash_union_buffer[5].float_type},
        {172,"BigAddring_inter_speed",menu_action,&flash_union_buffer[6].float_type},
        {173,"SmallAddring_inter_speed",menu_action,&flash_union_buffer[7].float_type},
        {174,"SmallAddring_inter_speed",menu_action,&flash_union_buffer[8].float_type},
        {21,"ring_size_threshold",menu_action,&flash_union_buffer[9].float_type},
        {22,"half_wide_offset_big",menu_action,&flash_union_buffer[10].float_type},
        {23,"half_wide_offset_small",menu_action,&flash_union_buffer[11].float_type},
        {24,"Cross_white_line",menu_action,&flash_union_buffer[16].float_type},
//        {25,"MT9V03X_EXP_TIME_DEF",menu_action,&flash_union_buffer[17].float_type},
        {31,"addLFuya",menu_action,&flash_union_buffer[12].float_type},
        {32,"addHFuya",menu_action,&flash_union_buffer[13].float_type},
        {33,"addMFuya",menu_action,&flash_union_buffer[14].float_type},
};

bool judge_menu(int menu_id) // 查看是否存在子菜单
{
    for (int i = 0; i < sizeof(menus) / sizeof(menus[0]); i++)
    {
        if (menus[i].menu_id / 10 == menu_id)
        {
            return true;
        }
    }
    return false;
}

int show_sub_menu(int parent_id, int highlight_col) // 显示子菜单，以及当前高亮菜单
{
    ips200_clear();
    int item_idx =0;
    for (int i = 0; i < sizeof(menus) / sizeof(menus[0]); i++)
    {
        if (menus[i].menu_id / 10 == parent_id)//如果有子菜单
        {
            if (item_idx == highlight_col)
            {
                new_menu = &menus[i];
                ips200_set_color(RGB565_RED,RGB565_WHITE);
                ips200_show_string(0, 16*10, "UseKey3ForEnter");
            }
            else
            {
                ips200_set_color(RGB565_BLACK,RGB565_WHITE);
                ips200_show_string(0, 16*11, "UseKey5ForQuit");
            }
            ips200_show_string(0, 16*item_idx, menus[i].func);//显示子菜单
            item_idx++;//有子菜单，返回1
        }
    }
    return item_idx;
}
//----------------------------------------------------------------------
//  函数简介    菜单主次级切换选择
//设置KEY6退出菜单 KEY5返回上一级 KEY1+ KEY2- KEY3确定
//  参数说明    空
//  返回参数    空
//  使用示例    空
//  备注信息    内部调用
//----------------------------------------------------------------------
void Menu_Switch(void)
{

   static int parent_menu_id = 0;
   static int highlight_col = 0; // 设定高亮行号
   int menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
    while(1)//如果所有的按键都没有值
    {
                            if (KEY_LONG_PRESS==key_get_state(KEY_5)){
                                    if(Flash_Jump == 1)
                                    {
                                        flash_write_page_from_buffer(0, FLASH_PAGE_INDEX);      // 向指定 Flash 扇区的页码写入缓冲区数据
                                        system_delay_ms(500);
                                        flash_buffer_clear();      // // 清空缓冲区
                                    }
                            Flash_Jump = 0;     //这个变量的置0必须放在这里，不能放在if之前↑
                            system_delay_ms(500); //务必延时，否则会与main里面while中的元素参数显示界面冲突
                            key_clear_all_state();
                            menu_flag=0;
                           break;
                            }
                            else if (KEY_SHORT_PRESS==key_get_state(KEY_1)) //// 按下按键1增加当前行数
                            {
                                highlight_col++;
                                show_sub_menu(parent_menu_id, highlight_col);
                                key_clear_state(KEY_1);
                            }
                            else if (KEY_SHORT_PRESS==key_get_state(KEY_2)) // // 按下按键2减少当前行数
                            {
                                if(highlight_col>0)highlight_col--;
                                show_sub_menu(parent_menu_id, highlight_col);
                                key_clear_state(KEY_2);
                            }
                            else if (KEY_SHORT_PRESS==key_get_state(KEY_3))
                            {
                                if (judge_menu(new_menu->menu_id))////如果有次级菜单
                                {
                                    highlight_col = 0;
                                    parent_menu_id = new_menu->menu_id;

                                }
                                else if (new_menu->menu_action)
                                {
                                    ips200_clear();
                                    flash_write_page_from_buffer(0, FLASH_PAGE_INDEX);      // 向指定 Flash 扇区的页码写入缓冲区数据
                                    flash_buffer_clear();       // 清空缓冲区
                                    new_menu->menu_action(new_menu->param, new_menu->func);
                                }
                                menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
                                key_clear_all_state();
                           }
                            else if (KEY_SHORT_PRESS==key_get_state(KEY_5)){
                                key_clear_all_state();
                                highlight_col = 0;
                                parent_menu_id = 0;
                                show_sub_menu(parent_menu_id, highlight_col);
                            }


    }
}
