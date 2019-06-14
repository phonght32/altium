/*
 * Scan_led.c
 *
 *  Created on: Nov 5, 2017
 *      Author: VuHuyHop
 */
#include "Scan_led.h"
#include <MSP430G2553.h>

void push_row(int8_t row) //0->7
{
    int i;
    for (i=0;i<8;i++)
    {
        if ((1<<row)&(1<<i))                //quet hang neu row = 1 thi day vao chan DATA_ROW = 0 0 0 0 0 0 0 1
            CTL_ROW_PORT|=DATA_R;         //row = 2 thi day vao chan DATA_ROW = 0 0 0 0 0 0 1 0
        else CTL_ROW_PORT&=~DATA_R;

        CTL_ROW_PORT&=~CLK_R;           // tao 1 xung clock sau moi lan day bit vao data
        CTL_ROW_PORT|=CLK_R;
    }
    CTL_ROW_PORT&=~LATCH_R;             //xuat cac bit ra ngoai
    CTL_ROW_PORT|=LATCH_R;
}

void push_data(int8_t red,int8_t green)
{
    int i;
    for (i=0;i<8;i++)                       //push column
    {
        if (green&(1<<i))
            CTL_COL_PORT|=DATA_C;
        else CTL_COL_PORT&=~DATA_C;

        CTL_COL_PORT&=~CLK_C;
        CTL_COL_PORT|=CLK_C;
    }
    for (i=0;i<8;i++)
    {
        if (red&(1<<i))
            CTL_COL_PORT|=DATA_C;
        else CTL_COL_PORT&=~DATA_C;

        CTL_COL_PORT&=~CLK_C;
        CTL_COL_PORT|=CLK_C;
    }
    CTL_COL_PORT&=~LATCH_C;
    CTL_COL_PORT|=LATCH_C;
}

void scan_frame(int8_t frame_red[8],int8_t frame_green[8], uint8_t redEnable, uint8_t greenEnable)
{
    int i;
    for (i=0;i<8;i++)
    {
        push_row(8);                 // turn off all led
        if (redEnable)
        {
            if (greenEnable)
                push_data(frame_red[i],frame_green[i]);
            else push_data(frame_red[i],0xff);
        }
        else {
            push_data(0xff,frame_green[i]);
        }
        push_row(i);                // scan row 0->7
        __delay_cycles(100);
    }
}


