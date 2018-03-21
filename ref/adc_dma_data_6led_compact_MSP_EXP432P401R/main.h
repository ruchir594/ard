/*
 * main.h
 *
 *  Created on: Sep 26, 2017
 *      Author: litia
 */

#ifndef MAIN_H_
#define MAIN_H_

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define NUM_OF_LEDS 6
#define NUM_OF_SENSORS 12
#define NUM_OF_SENSORS_2 6
#define DELAY_TIME 0
#define DELAY_TIME1 0

void uart_putchar(char c);
void uart_puts(char* text);
void clock_init();
void timer_init();
void pinout_init();
void adc_dma_init();
void potentiometerstart();
void setPotValue(int counter);
void uart_init(eUSCI_UART_Config uartConfig);
void get_gaze_vecter(int xgboost_index[2], int features[NUM_OF_LEDS*NUM_OF_SENSORS]);

/* DMA Control Table */
#ifdef ewarm
#pragma data_alignment=256
#else
#pragma DATA_ALIGN(controlTable, 256)
#endif
uint8_t controlTable[256];

#endif /* MAIN_H_ */
