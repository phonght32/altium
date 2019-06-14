/*
 * Scan_led.h
 *
 *  Created on: Nov 5, 2017
 *      Author: VuHuyHop
 */

#ifndef GPIO_SCAN_LED_H_
#define GPIO_SCAN_LED_H_
#include <stdio.h>
#include <stdint.h>

#define CTL_COL_PORT        P1OUT
#define CLK_C               BIT2
#define DATA_C              BIT5
#define LATCH_C             BIT4

#define CTL_ROW_PORT        P2OUT
#define CLK_R               BIT5
#define DATA_R              BIT3
#define LATCH_R             BIT4

void push_row(int8_t row);
void push_data(int8_t red,int8_t green);
void scan_frame(int8_t frame_red[8],int8_t frame_green[8], uint8_t redEnable, uint8_t greenEnable);

#endif /* GPIO_SCAN_LED_H_ */
