/*
 * Menu.h
 *
 *  Created on: 2023脛锚10脭脗18脠脮
 *      Author: 23913
 */

#ifndef MENU_H_
#define MENU_H_
extern int set_flag;
extern uint8 View_Flag;
extern uint8 Podao_Flag;
#define FLASH_PAGE_INDEX          10                              // 存储数据用的页码

typedef struct{
    int16 menu_id;
    char func[30];
    void (*menu_action)(float *param, char func[30]);
    float *param;
}menu_item;
void Parameters_Read(void);         //把Flash中的值读出来
void First_Flash_Write(void);
void Ips_Init(void);
void menu_action(float *param,char func[30]);
void key_read(void);
void Menu_Switch(void);
void Menu_Open(void);
#endif /* MENU_H_ */
