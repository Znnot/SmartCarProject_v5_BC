#ifndef _WS2812B_H_
#define _WS2812B_H_

/****************************************
 * 作者：LMX
 * 时间：2024.01.21
 * 功能：RGB指示灯2.0
 * 备注：ws2812b      0码高电平时间0.4us,低电平时间0.85us
                    1码高电平时间0.45us，低电平时间0.8us
                    数据传输时间=1.25us+-600ns，即625ns-1850ns
                    复位时间低电平50us以上
                    全部数据发送完成后要继续发送>24us的低电平作为复位码才能点亮
                    不同厂家可能具体数据有所差异，注意鉴别

                    另一数据：
                    0码高电平220-380ns，低电平580-1600ns
                    1码高电平580-1600ns，低电平220-420ns
                    复位低电平280us以上
                    单个数据的高低电平时间之和不能少于1250ns

                    又另一数据：
                    0码高电平220-380ns，低电平580-1000ns
                    1码高电平580-1000ns，低电平580-1000ns
                    复位低电平280us以上
                    单个数据的高低电平时间之和不能少于1250ns

                    系统滴答是延时中最准的（比定时器准），可以试用一下
                    置高置低直接操作寄存器是最快的，也可以尝试

                    IO口控制直接使用寄存器操作，不要用库函数。库函数浪费时间比NOP多得多，导致延时过大，不能写入准确数据。
                    一个机器周期不是对应12个晶振周期？csdn博主说的是1个机器周期就是一个晶振周期
****************************************/
#define WS2812B_GPIO_Pin P02_6//灯珠数据引脚

//灯珠数据及顺序：G、R、B各8bit
#define rgb_Red     0x00,0xff,0x00
#define rgb_Orange  0x20,0xff,0x00
#define rgb_Yellow  0xff,0xff,0x00
#define rgb_Green   0xff,0x00,0x00
#define rgb_Blue    0x00,0x00,0xff
#define rgb_Purple  0X00,0Xff,0Xff
#define rgb_White   0xff,0xff,0xff

extern uint8 Light_Type;

void Light_Init(void);
void Light_Color(uint8 G,uint8 R,uint8 B);

#endif

