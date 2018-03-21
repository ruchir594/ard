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

#define NUM_OF_LEDS 8
#define NUM_OF_SENSORS 16
#define DELAY_TIME 2000

void timer_init();
void pinout_init();
void adc_dma_init();
void potentiometerstart();
void setPotValue(int counter);

static uint32_t resultsBuffer[NUM_OF_LEDS][NUM_OF_SENSORS];

/* DMA Control Table */
#ifdef ewarm
#pragma data_alignment=256
#else
#pragma DATA_ALIGN(controlTable, 256)
#endif
uint8_t controlTable[256];


#endif /* MAIN_H_ */
