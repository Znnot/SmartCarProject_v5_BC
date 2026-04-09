//// * Menu.c
//// *
//// *  Created on: 2023骞�10鏈�18鏃�
//// *      Author: 23913
//// */
//#include "zf_common_headfile.h"
//#include "pid.h"
//#include "menu.h"
//#include"Encoder.h"
//#define BEEP                (P20_8)
//#include"control.h"
//    uint8 Flash_Jump = 0;   //缁撴潫璋冨弬
//    int set_flag=0;
//    float t=164;
//    uint8 loop = 0;
//    uint8 count_beep = 0;
//    key_index_enum key_index_array[KEY_NUMBER] = {KEY_1,KEY_2,KEY_3,KEY_4,KEY_5};
//    //----------------------------------------------------------------------
//    //  鍑芥暟绠�浠�    鑿滃崟寮�鍚�
//    //  鍙傛暟璇存槑    绌�
//    //  杩斿洖鍙傛暟    绌�
//    //  浣跨敤绀轰緥    Menu_Open();
//    //  澶囨敞淇℃伅    鐩存帴璋冪敤
//    //----------------------------------------------------------------------
//void Menu_Open(void){
//        menu_flag=1;
//        key_init(10);                      //鑿滃崟
//        pit_ms_init(CCU61_CH1,15);        //鑿滃崟
//        Ips_Init();                        //鑿滃崟
//        Parameters_Read();                     //鑿滃崟
//        Menu_Switch();                     //鑿滃崟
//        Parameter_init();                     //鑿滃崟
//        ips200_clear();                       //鑿滃崟
//}
////----------------------------------------------------------------------
////  鍑芥暟绠�浠�        绗竴娆″啓鍏lash 鎴栬�� 娣诲姞浜嗗彉閲� 鎴栬�呭彉閲忓弬鏁颁慨鏀瑰悗闇�瑕佸啀娆￠噸鏂板啓鍏lash鏃� 闇�瑕佸紑鍚繖涓嚱鏁�
////娑夊強鍒版竻闄lash涓殑鍨冨溇鏁版嵁
////绗竴娆″啓鍏ュ悗鍔″繀鍏抽棴杩欎釜鍑芥暟鍐嶆涓嬭浇绋嬪簭锛堥渶瑕佽繘鍏ュ埌璋冨弬鐣岄潰涔嬪悗鍐嶅叧闂紝浣嗘槸涓嶈鍔ㄥ弬鏁帮級
////浠ュ悗灏卞彲浠ユ甯告搷浣淔lash浜�
////濡備慨鏀瑰悗鎶ラ敊鎴栧崱姝� 鍗曠嫭浣跨敤 flash_erase_page(0,FLASH_PAGE_INDEX); flash_buffer_clear();
////  鍙傛暟璇存槑    绌�
////  杩斿洖鍙傛暟    绌�
////  浣跨敤绀轰緥    绌�
////  澶囨敞淇℃伅    鍐呴儴璋冪敤
////----------------------------------------------------------------------
//
//    // 璇锋敞鎰� 鏁版嵁缂撳啿鍖虹殑姣忎釜浣嶇疆鍙兘瀛樺偍涓�绉嶇被鍨嬬殑鏁版嵁
//    // 渚嬪 flash_data_union_buffer[0] 鍐欏叆 int8_type 閭ｄ箞鍙兘浠� int8_type 璇诲彇
//    // 鍚屾牱 flash_data_union_buffer[0] 鍐欏叆 float_type 閭ｄ箞鍙兘浠� float_type 璇诲彇
//    void First_Flash_Write()
//    {
//        flash_erase_page(0,FLASH_PAGE_INDEX);                //绠″畠鏈夋病鏈夋暟鎹紝鐩存帴鎿﹂櫎杩欎竴椤�
//        flash_buffer_clear();                        // 娓呯┖缂撳啿鍖�
//        flash_union_buffer[0].float_type = 16;     //
//        flash_union_buffer[1].float_type = 0;        //
//        flash_union_buffer[2].float_type = 56;     //
//        flash_union_buffer[3].float_type = 103.0;     //
//        flash_union_buffer[4].float_type = 2.75;     //
//        flash_union_buffer[5].float_type = 0;        //
//        flash_union_buffer[6].float_type = 103.1;
//        flash_union_buffer[7].float_type = 2.72;
//        flash_union_buffer[8].float_type = 0;
//        flash_union_buffer[9].float_type = 0.00032;
//        flash_union_buffer[10].float_type =2.05;
//        flash_union_buffer[11].float_type=3;
//        flash_union_buffer[12].float_type=64;
//        flash_union_buffer[13].float_type=54;
//        flash_union_buffer[14].float_type=20;
//        flash_union_buffer[15].float_type=15;
//        flash_union_buffer[16].float_type=30;
//        flash_union_buffer[17].float_type=37;
//        flash_union_buffer[18].float_type=4000;
//        flash_union_buffer[19].float_type=16.6;
//        flash_union_buffer[20].float_type=8;
//        flash_write_page_from_buffer(0, FLASH_PAGE_INDEX);     // 鍚戞寚瀹� Flash 鎵囧尯鐨勯〉鐮佸啓鍏ョ紦鍐插尯鏁版嵁
//        flash_buffer_clear();                                                  // 娓呯┖缂撳啿鍖�
//    }
//    //----------------------------------------------------------------------
//    //  鍑芥暟绠�浠�    flash鏁板�艰祴鍊肩粰瀹為檯浣跨敤鍙橀噺
//    //  鍙傛暟璇存槑    绌�
//    //  杩斿洖鍙傛暟    绌�
//    //  浣跨敤绀轰緥    绌�
//    //  澶囨敞淇℃伅    鍐呴儴璋冪敤
//    //----------------------------------------------------------------------
//    void Parameters_Read()
//    {
//        flash_buffer_clear();
//        flash_read_page_to_buffer(0, FLASH_PAGE_INDEX);      // 灏嗘暟鎹粠 flash 璇诲彇鍒扮紦鍐插尯
//        system_delay_ms(200); //鍔″繀寤舵椂
//        Parameter_init();
////        Steer_PID.Kp=flash_union_buffer[0].uint16_type;//澶栭儴鍙橀噺浼间箮瑕佽繖鏍峰彇
//        system_delay_ms(200); //鍔″繀寤舵椂
//    }
//    //----------------------------------------------------------------------
//    //  鍑芥暟绠�浠�    鎸夐敭鍝嶈渹楦ｅ櫒
//    //  鍙傛暟璇存槑    绌�
//    //  杩斿洖鍙傛暟    绌�
//    //  浣跨敤绀轰緥     key_read(void);
//    //  澶囨敞淇℃伅    鏀惧畾鏃朵腑鏂紝娉ㄦ剰瀹氭椂鏃堕暱涓嶈兘澶柇锛屽鏄撹涓嶅埌鎸夐敭
//    //----------------------------------------------------------------------
//void key_read(void){
//
//    for(loop = 0; loop < 7; loop ++)
//    {
//        switch(key_get_state(key_index_array[loop]))                        // 鑾峰彇鎸夐敭鐘舵��
//        {
//            case KEY_SHORT_PRESS:                                           // 鐭寜鐘舵��
//
//                    gpio_set_level(BEEP, GPIO_HIGH);                        // BEEP 鍝�
//
//                break;
//            case KEY_LONG_PRESS:                                            // 闀挎寜鐘舵��
//
//                    gpio_set_level(BEEP, GPIO_HIGH);                        // BEEP 鍝�
//
//                break;
//            default:
//                break;
//        }
//    }
//    if( KEY_RELEASE == key_get_state(KEY_1) && \
//        KEY_RELEASE == key_get_state(KEY_2) && \
//        KEY_RELEASE == key_get_state(KEY_3) && \
//        KEY_RELEASE == key_get_state(KEY_4) && \
//        KEY_RELEASE == key_get_state(KEY_5)
//       )//濡傛灉鎵�鏈夌殑鎸夐敭閮芥病鏈夊��
//    {
//        gpio_set_level(BEEP, GPIO_LOW);                                     // BEEP 鍋�
//
//    }
//
//}
////----------------------------------------------------------------------
////  鍑芥暟绠�浠�    IPS灞忓箷鍒濆鍖�
////  鍙傛暟璇存槑    绌�
////  杩斿洖鍙傛暟    绌�
////  浣跨敤绀轰緥    Ips_Init();
////  澶囨敞淇℃伅    绌�
////----------------------------------------------------------------------
//void Ips_Init(void){
//       ips200_set_dir(IPS200_PORTAIT_180);
//       ips200_set_font(IPS200_8X16_FONT);
//       ips200_set_color(RGB565_RED, RGB565_BLACK);
//       ips200_init(IPS200_TYPE_PARALLEL8);
//       ips200_show_string(0, 0, "Loading...");                     // 鍧愭爣0,0鍐欎竴涓瓧绗
//}
//
//
//menu_item* new_menu=0;
//void menu_11(void){
//    ips200_clear();
//    while (key_get_state(KEY_5)!=KEY_SHORT_PRESS)
//    {
//        ips200_show_string(1, 150, "PRESS KEY5 TO QUIT");
//        ips200_show_binary_image(0, 0, ov7725_image_binary[0], OV7725_W, OV7725_H, OV7725_W, OV7725_H);
//    }
//    return;
//    //鎵ц浠诲姟椤�
//}
////----------------------------------------------------------------------
////  鍑芥暟绠�浠�    鑿滃崟璋冨弬鎵ц鍑芥暟
////              璁剧疆KEY4涓鸿皟鑺傚崟浣� KEY5涓鸿繑鍥炰笂绾ц彍鍗� KEY6涓洪��鍑鸿皟鍙�
////  鍙傛暟璇存槑    *param 浼犲叆鐨勫弬鏁� func[30]鎵ц鍑芥暟鐨勫悕绉�
////  杩斿洖鍙傛暟    绌�
////  浣跨敤绀轰緥    绌�
////  澶囨敞淇℃伅    鍐呴儴璋冪敤
////----------------------------------------------------------------------
//void menu_action(float *param,char func[30])
//{
////        First_Flash_Write();      //棣栨鍐欏叆闇�瑕佸紑鍚鍑芥暟锛岀湅鍑芥暟娉ㄩ噴
//         flash_buffer_clear();
//         flash_read_page_to_buffer(0, FLASH_PAGE_INDEX);      // 灏嗘暟鎹粠 flash 璇诲彇鍒扮紦鍐插尯
//         system_delay_ms(50);
//       float last_param;
//       char buf[30]; // 瀛樻斁鍚嶇О
//       char *menu_name = func;
//       static int current_level = 0;
//       float level[4] = {0.01,0.1,0.0001,10};//璋冭妭鎸′綅
//       while (1)
//       {
//           ips200_show_string(0, 16*3, "UseKey4ForSettingLevel");
//           sprintf(buf, "%s: ", menu_name);
//           ips200_show_string(0, 16*1, buf);
//           sprintf(buf, "%5.6f", *param);
//           ips200_show_string(0, 16*2, buf);
//           last_param=*param;
//               if(key_get_state(KEY_4)==KEY_SHORT_PRESS)
//               {
//                   ips200_clear();
//                   key_clear_state(KEY_4);
//                   while(1){
//                       ips200_show_string(0, 16*0, "CHANGING LEVEL");
//                       sprintf(buf, "X%5.2f: ", level[current_level]);
//                      //鎶妉evel[current_level]鎸夋牸寮忓啓鍒板瓧绗︽暟缁刡uf,灏嗕細鏄剧ず鈥淴 LEVEL:鈥�
//                       ips200_show_string(0, 16*1, buf);
//                   if (KEY_SHORT_PRESS==key_get_state(KEY_1))
//                   {
//                       if(current_level<sizeof(level)/sizeof(level[0])-1)current_level++;
//                                  key_clear_state(KEY_1);
//
//                    }
//                   if (KEY_SHORT_PRESS==key_get_state(KEY_2))
//                   {
//                       if(current_level>0)current_level--;
//                                  key_clear_state(KEY_2);
//
//                    }
//                   if(KEY_SHORT_PRESS==key_get_state(KEY_5)){
//                                   return;
//                   }
//                   }
//               }
//
//                                                   if (KEY_SHORT_PRESS==key_get_state(KEY_1))
//                                                   {
//                                                       *param +=level[current_level];
//                                                       key_clear_state(KEY_1);
//                                                   }
//                                                   else if (KEY_SHORT_PRESS==key_get_state(KEY_2))
//                                                   {
//                                                       *param -= level[current_level];
//                                                       key_clear_state(KEY_2);
//                                                   }
//                                                   else if (KEY_SHORT_PRESS==key_get_state(KEY_5)){
//                                                       if(last_param!=*param){
//                                                           Flash_Jump = 1;
//                                                       }
//                                                       return ;
//                                                   }
//       }
//}
//
//
//
//menu_item menus[]={
//        {1,"MODE PID",NULL,NULL},
//        {2,"Set KP2",menu_action,&flash_union_buffer[9].float_type},
//        {3,"Set Pic",NULL,NULL},
//        {4,"Speed Select",NULL,NULL},
//        {11,"Set MotorL_PID",NULL,NULL},
//        {12,"Set_MotorR_PID",NULL,NULL},
//        {13,"Set Servo_PID",NULL,NULL},
//        {14,"Set Min_xishu",menu_action,&flash_union_buffer[19].float_type},
//        {15,"Set Add_xishu",menu_action,&flash_union_buffer[20].float_type},
//        {31,"Set POSITION",menu_action,&flash_union_buffer[17].float_type},
//        {32,"Set RAMP_NUM",menu_action,&flash_union_buffer[18].float_type},
//        {41,"Speed High",NULL,NULL},
//        {42,"Speed Low",NULL,NULL},
//        {131,"Set Servo_P",menu_action,&flash_union_buffer[0].float_type},
//        {132,"Set Servo_I",menu_action,&flash_union_buffer[1].float_type},
//        {133,"Set Servo_D",menu_action,&flash_union_buffer[2].float_type},
//        {133,"Set MAX_DP",menu_action,&flash_union_buffer[10].float_type},
//        {133,"Set MAX_DD",menu_action,&flash_union_buffer[11].float_type},
//        {133,"Set max_kd",menu_action,&flash_union_buffer[12].float_type},
//        {133,"Set min_kd",menu_action,&flash_union_buffer[13].float_type},
//        {133,"Set max_kp",menu_action,&flash_union_buffer[14].float_type},
//        {133,"Set min_kp",menu_action,&flash_union_buffer[15].float_type},
//        {133,"Set MAX_CERR",menu_action,&flash_union_buffer[16].float_type},
//        {121,"Set LMotor_P",menu_action,&flash_union_buffer[3].float_type},
//        {122,"Set LMotor_I",menu_action,&flash_union_buffer[4].float_type},
//        {123,"Set LMotor_D",menu_action,&flash_union_buffer[5].float_type},
//        {111,"Set RMotor_P",menu_action,&flash_union_buffer[6].float_type},
//        {112,"Set RMotor_I",menu_action,&flash_union_buffer[7].float_type},
//        {113,"Set RMotor_D",menu_action,&flash_union_buffer[8].float_type}
//};
//
//bool judge_menu(int menu_id) // 鏌ョ湅鏄惁瀛樺湪瀛愯彍鍗�
//{
//    for (int i = 0; i < sizeof(menus) / sizeof(menus[0]); i++)
//    {
//        if (menus[i].menu_id / 10 == menu_id)
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//int show_sub_menu(int parent_id, int highlight_col) // 鏄剧ず瀛愯彍鍗曪紝浠ュ強褰撳墠楂樹寒鑿滃崟
//{
//    ips200_clear();
//    int item_idx =0;
//    for (int i = 0; i < sizeof(menus) / sizeof(menus[0]); i++)
//    {
//        if (menus[i].menu_id / 10 == parent_id)//濡傛灉鏈夊瓙鑿滃崟
//        {
//            if (item_idx == highlight_col)
//            {
//                new_menu = &menus[i];
//                ips200_set_color(RGB565_RED,RGB565_WHITE);
//                ips200_show_string(0, 16*10, "UseKey3ForEnter");
//            }
//            else
//            {
//                ips200_set_color(RGB565_BLACK,RGB565_WHITE);
//                ips200_show_string(0, 16*11, "UseKey5ForQuit");
//            }
//            ips200_show_string(0, 16*item_idx, menus[i].func);//鏄剧ず瀛愯彍鍗�
//            item_idx++;//鏈夊瓙鑿滃崟锛岃繑鍥�1
//        }
//    }
//    return item_idx;
//}
////----------------------------------------------------------------------
////  鍑芥暟绠�浠�    鑿滃崟涓绘绾у垏鎹㈤�夋嫨
////璁剧疆KEY6閫�鍑鸿彍鍗� KEY5杩斿洖涓婁竴绾� KEY1+ KEY2- KEY3纭畾
////  鍙傛暟璇存槑    绌�
////  杩斿洖鍙傛暟    绌�
////  浣跨敤绀轰緥    绌�
////  澶囨敞淇℃伅    鍐呴儴璋冪敤
////----------------------------------------------------------------------
//void Menu_Switch(void)
//{
//
//   static int parent_menu_id = 0;
//   static int highlight_col = 0; // 璁惧畾楂樹寒琛屽彿
//   int menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
//    while(1)//濡傛灉鎵�鏈夌殑鎸夐敭閮芥病鏈夊��)
//    {
//                            if (KEY_LONG_PRESS==key_get_state(KEY_5)){
//                                    if(Flash_Jump == 1)
//                                    {
//                                        flash_write_page_from_buffer(0, FLASH_PAGE_INDEX);     // 鍚戞寚瀹� Flash 鎵囧尯鐨勯〉鐮佸啓鍏ョ紦鍐插尯鏁版嵁
//                                        system_delay_ms(500);
//                                        flash_buffer_clear();      // 娓呯┖缂撳啿鍖�
//                                    }
//                            Flash_Jump = 0;     //杩欎釜鍙橀噺鐨勭疆0蹇呴』鏀惧湪杩欓噷锛屼笉鑳芥斁鍦╥f涔嬪墠鈫�
//                            system_delay_ms(500); //鍔″繀寤舵椂锛屽惁鍒欎細涓巑ain閲岄潰while涓殑鍏冪礌鍙傛暟鏄剧ず鐣岄潰鍐茬獊
//                            key_clear_all_state();
//                            menu_flag=0;
//                            break;
//                            }
//                            else if (KEY_SHORT_PRESS==key_get_state(KEY_1)) // 鎸変笅鎸夐敭1澧炲姞褰撳墠琛屾暟
//                            {
//                                highlight_col++;
//                                show_sub_menu(parent_menu_id, highlight_col);
//                                key_clear_state(KEY_1);
//                            }
//                            else if (KEY_SHORT_PRESS==key_get_state(KEY_2)) // 鎸変笅鎸夐敭2鍑忓皯褰撳墠琛屾暟
//                            {
//                                if(highlight_col>0)highlight_col--;
//                                show_sub_menu(parent_menu_id, highlight_col);
//                                key_clear_state(KEY_2);
//                            }
//                            else if (KEY_SHORT_PRESS==key_get_state(KEY_3))
//                            {
//                                if (judge_menu(new_menu->menu_id))//濡傛灉鏈夋绾ц彍鍗�
//                                {
//                                    highlight_col = 0;
//                                    parent_menu_id = new_menu->menu_id;
//
//                                }
//                                else if (new_menu->menu_action)
//                                {
//                                    ips200_clear();
//                                    flash_write_page_from_buffer(0, FLASH_PAGE_INDEX);     // 鍚戞寚瀹� Flash 鎵囧尯鐨勯〉鐮佸啓鍏ョ紦鍐插尯鏁版嵁
//                                    flash_buffer_clear();      // 娓呯┖缂撳啿鍖�
//                                    new_menu->menu_action(new_menu->param, new_menu->func);
//                                }
//                                menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
//                                key_clear_all_state();
//                           }
//                            else if (KEY_SHORT_PRESS==key_get_state(KEY_5)){
//                                key_clear_all_state();
//                                highlight_col = 0;
//                                parent_menu_id = 0;
//                                show_sub_menu(parent_menu_id, highlight_col);
//                            }
//
//
//    }
//}
