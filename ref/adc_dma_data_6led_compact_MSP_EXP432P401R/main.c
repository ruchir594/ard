#include <main.h>

/* Statics */
static char tx_buf[NUM_OF_LEDS*NUM_OF_SENSORS*2 + 1];
int features[NUM_OF_LEDS*NUM_OF_SENSORS];
bool debug = false;
//bool debug = true;
bool data_collection_start = false;
//bool data_collection_start = true;
int gaze_vector[2];
static uint32_t resultsBuffer[NUM_OF_LEDS*2][NUM_OF_SENSORS/2];

const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        1,                                     // BRDIV = 78 for 9600, 6 for 115200, 3 for 230400, 1 for 460800
        10,                                       // UCxBRF = 2 for 9600, 8 for 115200, 4 for 230400, 10 for 460800
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

int main(void)
{
    /* Halting the Watchdog  */
    MAP_WDT_A_holdTimer();

    /* Zero-filling buffer */
	memset(resultsBuffer, 0x00, NUM_OF_SENSORS*NUM_OF_LEDS);

    clock_init();
    pinout_init();
//    __delay_cycles(DELAY_TIME);
//    potentiometerstart();
//    setPotValue(27);
    adc_dma_init();
    timer_init();
    if (!debug){
    		uart_init(uartConfig);
    }

    while (1)
    {
    		MAP_PCM_gotoLPM3();
    }
}

void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT)
    {
    		uint8_t command = MAP_UART_receiveData(EUSCI_A0_BASE);
		if (command == 48){
			data_collection_start = true;
		}else if(command == 49){
			data_collection_start = false;
		}
    }

}

int counter = 0;
int step_counter = 0;
int int_counter = 0;

/* WDT ISR - This ISR toggles sensor sampling process */
void WDT_A_IRQHandler(void)
{
	if (step_counter == 0){
		P3OUT &= ~BIT0; //low turn off external LEDs

		if (data_collection_start){
			P3OUT &= ~BIT4; //low
		}

		counter = 0;
		int_counter = 0;
		__delay_cycles(DELAY_TIME);
	    MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
	        UDMA_MODE_AUTO, (void*) &ADC14->MEM[0],
			resultsBuffer[counter], NUM_OF_SENSORS_2);
		MAP_DMA_enableChannel(7);

		MAP_ADC14_toggleConversionTrigger();
		step_counter = 0;
	}else{
		step_counter++;
	}

}

/* Completion interrupt for DMA */
void DMA_INT1_IRQHandler(void)
{
    if (counter < 2*NUM_OF_LEDS-1){
    		if (int_counter == 0){
    			P8OUT |= BIT0; //high
    			P8OUT |= BIT1; //high
    			int_counter = 1;
//    			__delay_cycles(DELAY_TIME1);
    		}else{
    			P8OUT &= ~BIT0; //low
    			P8OUT &= ~BIT1; //low
    			int_counter = 0;
    			if (counter == 1){
				P5OUT &= ~BIT6; //low
				P5OUT |= BIT7; //high
				P3OUT |= BIT5; //high
			}else if (counter == 3){
				P5OUT |= BIT6; //high
				P5OUT &= ~BIT7; //low
				P3OUT &= ~BIT5; //low
			}else if (counter == 5){
				P5OUT |= BIT6; //high
				P5OUT &= ~BIT7; //low
				P3OUT |= BIT5;  //high
			}else if (counter == 7){
				P5OUT |= BIT6; //high
				P5OUT |= BIT7; // high
				P3OUT &= ~BIT5;// low
			}else if (counter == 9){
				P5OUT |= BIT6; //high
				P5OUT |= BIT7; //high
				P3OUT |= BIT5; //high
			}
			__delay_cycles(DELAY_TIME);
    		}

	}else{
		P3OUT |= BIT4; // high
	    P5OUT &= ~BIT6; //low
		P5OUT |= BIT7;  //high
		P3OUT &= ~BIT5; //low
		P8OUT &= ~BIT0; //low
		P8OUT &= ~BIT1; //low

		if (data_collection_start){
			P3OUT |= BIT0;  //high turn on external LEDs
		}
//		MAP_DMA_disableChannel(7);
	}

    if (counter == 2*NUM_OF_LEDS-1){
        int i,j;

        if (!debug){
        		for (i = 0; i < NUM_OF_LEDS*2; i++){
				for (j = 0; j < NUM_OF_SENSORS_2; j++){
					tx_buf[(NUM_OF_SENSORS_2*i+j)*2] = (resultsBuffer[i][j] & 0x7F) + 32;
					tx_buf[(NUM_OF_SENSORS_2*i+j)*2+1] = (resultsBuffer[i][j] >> 7) + 32;
					if (tx_buf[(NUM_OF_SENSORS_2*i+j)*2]>126){
							tx_buf[(NUM_OF_SENSORS_2*i+j)*2] = tx_buf[(NUM_OF_SENSORS_2*i+j)*2] + 1;
					}
					if (tx_buf[(NUM_OF_SENSORS_2*i+j)*2+1] > 126){
							tx_buf[(NUM_OF_SENSORS_2*i+j)*2+1] = tx_buf[(NUM_OF_SENSORS_2*i+j)*2+1] + 1;
					}
				}
			}
			tx_buf[NUM_OF_LEDS*NUM_OF_SENSORS*2] = 10;
			uart_puts(tx_buf);
        }else{
//        		for (i = 0; i < NUM_OF_LEDS*2; i++){
//				for (j = 0; j < NUM_OF_SENSORS_2; j++){
//					features[NUM_OF_SENSORS_2*i+j] = resultsBuffer[i][j];
//				}
//			}
//        		get_gaze_vecter(gaze_vector, features);
        }
    }else {
        counter++;
		MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
			UDMA_MODE_AUTO, (void*) &ADC14->MEM[0],
			resultsBuffer[counter], NUM_OF_SENSORS_2);
		MAP_DMA_enableChannel(7);

        MAP_ADC14_toggleConversionTrigger();
    }
}
