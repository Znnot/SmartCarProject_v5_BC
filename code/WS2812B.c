#include "zf_common_headfile.h"
#include "WS2812B.h"

/****************************************
 * 作者：LMX
 * 时间：2024.01.21
 * 功能：RGB指示灯2.0
****************************************/

uint8 Light_Type=0;

void Light_Init(void)
{
//    gpio_init(WS2812B_GPIO_Pin,GPO, 1, GPO_PUSH_PULL);//GPIO初始化
    gpio_set_level(WS2812B_GPIO_Pin,0);//配置低电平
}

//V1封装写1写0，300ns：15个nop；600ns：30个nop
//V2    300ns：8个nop；600ns：15个nop
//这里的300ns、600ns未必就是真实的300ns、600ns（没实测过），只是通过调节nop个数来满足时序 ；
//按1个机器周期=12个晶振周期来算300ns、600ns理论上对应实际的480ns、900ns
void Delay_300ns(void)
{
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
}

void Delay_600ns(void)
{
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
}

void Light_Write_0(void)//写0码
{
    gpio_set_level(WS2812B_GPIO_Pin,1);
    Delay_300ns();
    gpio_set_level(WS2812B_GPIO_Pin,0);
    Delay_600ns();
}

void Light_Write_1(void)//写1码
{
    gpio_set_level(WS2812B_GPIO_Pin,1);
    Delay_600ns();
    gpio_set_level(WS2812B_GPIO_Pin,0);
    Delay_300ns();
}

void Light_Reset(void)
{
    gpio_set_level(WS2812B_GPIO_Pin,0);
}

void Send_8bitData(uint8 data)//发送8bit数据
{
    for(int i=0;i<8;i++)
    {
        if(data&0x80)//0x80=二进制1000 0000
        {
            Light_Write_1();
        }
        else
        {
            Light_Write_0();
        }
        data<<=1;//左移一位
    }
}

void Light_Color(uint8 G,uint8 R,uint8 B)//调用点亮灯珠颜色
{
    Send_8bitData(G);
    Send_8bitData(R);
    Send_8bitData(B);
}
