/*
 * Time.c
 *
 *  Created on: 2024Äê3ÔÂ14ÈÕ
 *      Author: ½¶Ì«ÀÇ
 */

#ifndef __TIME__H
#define __TIME__H

extern unsigned int taskTickCNT;

#define TaskTick_Base(ms)     taskTickCNT += ms

#define TaskTick_Get(void)    taskTickCNT

#define TaskTick_Block(ms, task)                        \
{                                                       \
    static unsigned int lastTaskTick = 0;               \
    unsigned int curTaskTick = TaskTick_Get();          \
                                                        \
    if (curTaskTick >= (lastTaskTick + ms))             \
    {                                                   \
        task;                                           \
        lastTaskTick = curTaskTick;                     \
    }                                                   \
}

#endif


