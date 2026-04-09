/*
 * camera_tool.c
 *
 *  Created on: 2024年1月12日
 *      Author: 周文烽
 */
#include "Camera_tool.h"

uint8 right_line[LCDH];             //二值化原图的左线
uint8 left_line[LCDH];              //二值化原图的右线
uint8 mid_line[LCDH];               //二值化原图的中线
uint8 right_disline[LCDH][2];       //屏幕左线的坐标点
uint8 left_disline[LCDH][2];        //屏幕右线的左边点
uint8 mid_disline[LCDH][2];         //0-x 1-y

uint32 Time_counter=0;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name
//  @brief         将每行的边界存储到数组方便画点
//  @brief
//  @brief
//  @parameter
//  @return
//  @time
//  @Author
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void put_line_to_array(void)
{
    uint8 i;
    for(i=0;i<LCDH;i++)
    {
        right_line[i]=ImageDeal[i].RightBorder;
        left_line[i]=ImageDeal[i].LeftBorder;
        mid_line[i]=(ImageDeal[i].RightBorder+ImageDeal[i].LeftBorder)/2;
    }
}
void array_to_disarray(void)
{

    uint8 i;
    uint8 dis_height;
    for(i=0;i<LCDH;i++)
    {
        dis_height=(uint8)(i*Dis_y/LCDH);

        right_disline[i][0]=(uint8)(right_line[i]*Dis_x/LCDW);
        left_disline[i][0]=(uint8)(left_line[i]*Dis_x/LCDW);
        mid_disline[i][0]=(uint8)(mid_line[i]*Dis_x/LCDW);

        right_disline[i][1]=dis_height;
        left_disline[i][1]=dis_height;
        mid_disline[i][1]=dis_height;

    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name
//  @brief         将每行的边界存储到数组方便画点
//  @brief          //x——0~239(ips200_width_max) y——0~319(ips200_height_max)
//  @brief          //边界的就画一个点，不是边界的画周围九个
//  @parameter
//  @return
//  @time
//  @Author
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void ips200_draw_rgb_point(uint8 x,uint8 y,uint8 color)
{
    uint8 i,j;
    if(color==RED)
    {
        if(x>0&&x<(ips200_width_max-1)&&y>0&&y<(ips200_height_max-1))
        {
            for(i=x-1;i<=x+1;i++)
            {
                for(j=y-1;j<=y+1;j++)
                {
                    ips200_draw_point(i,j,RGB565_RED);
                }
            }
        }
        else if(x==0||x==ips200_width_max-1||y==0||y==ips200_height_max-1)
        {
            ips200_draw_point(x,y,RGB565_RED);
        }
    }
    else if(color==BLUE)
    {
        if(x>0&&x<(ips200_width_max-1)&&y>0&&y<(ips200_height_max-1))
        {
            for(i=x-1;i<=x+1;i++)
            {
                for(j=y-1;j<=y+1;j++)
                {
                    ips200_draw_point(i,j,RGB565_BLUE);
                }
            }
        }
        else if(x==0||x==ips200_width_max-1||y==0||y==ips200_height_max-1)
        {
            ips200_draw_point(x,y,RGB565_BLUE);
        }
    }
}





//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//  @name
//  @brief         屏幕画左右边线
//  @brief
//  @brief
//  @parameter
//  @return
//  @time
//  @Author
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void ips200_draw_side_line(uint8 line_r[],uint8 line_l[])
{
    uint8 i;
    for(i=0;i<LCDH-1;i++)
    {
        ips200_draw_rgb_point(line_r[i],i,RED);
        ips200_draw_rgb_point(line_l[i],i,RED);
    }
}

void ips200_draw_mid_line(uint8 line_mid[])
{
    uint8 i;
    for(i=0;i<LCDH-1;i++)
    {
        ips200_draw_rgb_point(line_mid[i],i,BLUE);
    }
}

void ips_draw_center(void)
{
    int i;
    for(i=LCDH-1;i>=20;i--)
    {
        ips200_draw_point(ImageDeal[i].Center,i,RGB565_BLUE);
        ips200_draw_point(ImageDeal[i].LeftBoundary,i,RGB565_GREEN);
        ips200_draw_point(ImageDeal[i].RightBorder,i,RGB565_RED);

    }
}

void ips_show_data(void)
{
    ips114_show_int(LCDW+5,0,a,3);
    ips114_show_int(LCDW+5,15,ImageStatus.OFFLine,3);
//    ips114_show_int(LCDW+5,30,ImageStatus.Cross_Miss_Right_lines,3);

}

void draw_tool_process(void)
{
    put_line_to_array();
    array_to_disarray();
    my_ips200_show_gray_image(0,0,Pixle[0],LCDW,LCDH,188,40,255);
//    ips114_show_gray_image (10, 10, (const uint8 *)mt9v03x_image, 188, 120,188, 120,0);
//    ips114_show_gray_image(0,0,Pixle[0],126,70,126,70,0);
//    ips200_show_gray_image (10, 10, (const uint8 *)mt9v03x_image, 188, 120,188, 120,0);
//    ips_draw_center();
//    ips_show_data();
}

