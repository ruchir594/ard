#include <main.h>

/* Statics */
static char tx_buf[NUM_OF_LEDS*NUM_OF_SENSORS*2 + 1];
bool debug = false;
//bool debug = true;
//bool data_collection_start = false;
bool data_collection_start = true;

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

void uart_putchar(char c)
{
    MAP_UART_transmitData(EUSCI_A0_BASE, c);
}

void uart_puts(char* text)
{
    while (*text){
        if (*text == '\n'){
            uart_putchar('\r');
            uart_putchar('\n');
            *text++;
        }else
            uart_putchar(*text++);
    }
}

int main(void)
{
    /* Halting the Watchdog  */
    MAP_WDT_A_holdTimer();

    /* Enabling SRAM Bank Retention. This is done to minimize power consumption
        in LPM3 mode. With only SRAM bank 1 enabled, when the device is in LPM3
         only the first bank of SRAM memory has to be retained (this minimizing
         power consumption. */
    MAP_SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1);

    /* Set the core voltage level to VCORE1 */
    MAP_PCM_setPowerState(PCM_AM_LDO_VCORE1);
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Initializes Clock System: Setting DCO to 48MHz  */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_2);

    /* Zero-filling buffer */
    memset(resultsBuffer, 0x00, NUM_OF_SENSORS*NUM_OF_LEDS);

    pinout_init();
    __delay_cycles(24000);
    potentiometerstart();
    setPotValue(40);
    adc_dma_init();
    timer_init();
//    P3OUT |= BIT5; // high for sync

    //--------- Setting the UART function for P1.1 & P1.2 --------//
    if (!debug){
            /* Selecting P1.2 and P1.3 in UART mode */
            MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                    GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

            /* Setting DCO to 12MHz */
            CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

            /* Configuring UART Module */
            MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

            /* Enable UART module */
            MAP_UART_enableModule(EUSCI_A0_BASE);

            /* Enabling interrupts */
			MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
			MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
    }

    while (1)
    {
    		MAP_PCM_gotoLPM0();
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
/* WDT ISR - This ISR toggles sensor sampling process */
void WDT_A_IRQHandler(void)
{
	if (step_counter == 1){

//		P3OUT |= BIT0;  //high turn on external LEDs
		P3OUT &= ~BIT0; //low turn off external LEDs

		if (data_collection_start){
			P3OUT &= ~BIT5; //low
		}

		counter = 0;
		__delay_cycles(DELAY_TIME);
	    MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
	        UDMA_MODE_AUTO, (void*) &ADC14->MEM[0],
			resultsBuffer[counter], NUM_OF_SENSORS);
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
    if (counter < NUM_OF_LEDS - 1){
		if (counter == 0){
			P2OUT &= ~BIT3; //low
			P3OUT &= ~BIT6; //low
			P3OUT |= BIT7;  //high
		}else if (counter == 1){
			P2OUT &= ~BIT3; //low
			P3OUT |= BIT6; // high
			P3OUT &= ~BIT7;// low
		}else if (counter == 2){
			P2OUT &= ~BIT3; //low
			P3OUT |= BIT6; //high
			P3OUT |= BIT7; //high
		}else if (counter == 3){
			P2OUT |= BIT3; //high
			P3OUT &= ~BIT6; //low
			P3OUT &= ~BIT7; //low
		}else if (counter == 4){
			P2OUT |= BIT3; //high
			P3OUT &= ~BIT6; //low
			P3OUT |= BIT7;  //high
		}else if (counter == 5){
			P2OUT |= BIT3; //high
			P3OUT |= BIT6; // high
			P3OUT &= ~BIT7;// low
		}else if (counter == 6){
			P2OUT |= BIT3; //high
			P3OUT |= BIT6; //high
			P3OUT |= BIT7; //high
		}
		__delay_cycles(DELAY_TIME);
	}else{
		P3OUT |= BIT5; // high
		P2OUT &= ~BIT3; //low
		P3OUT &= ~BIT6; //low
		P3OUT &= ~BIT7; //low

		if (data_collection_start){
			P3OUT |= BIT0;  //high turn on external LEDs
		}
//		MAP_DMA_disableChannel(7);
	}

    if (counter == NUM_OF_LEDS - 1){
        int i,j;
        for (i = 0; i < NUM_OF_LEDS; i++){
            for (j = 0; j < NUM_OF_SENSORS; j++){
                tx_buf[(NUM_OF_SENSORS*i+j)*2] = (resultsBuffer[i][j] & 0x7F) + 32;
                tx_buf[(NUM_OF_SENSORS*i+j)*2+1] = (resultsBuffer[i][j] >> 7) + 32;
                if (tx_buf[(NUM_OF_SENSORS*i+j)*2]>126){
                		tx_buf[(NUM_OF_SENSORS*i+j)*2] = tx_buf[(NUM_OF_SENSORS*i+j)*2] + 1;
                }
                if (tx_buf[(NUM_OF_SENSORS*i+j)*2+1] > 126){
                		tx_buf[(NUM_OF_SENSORS*i+j)*2+1] = tx_buf[(NUM_OF_SENSORS*i+j)*2+1] + 1;
                }
            }
        }

        if (!debug){
			tx_buf[NUM_OF_LEDS*NUM_OF_SENSORS*2] = 10;
			uart_puts(tx_buf);
        }
    }else {
        counter++;
		MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
			UDMA_MODE_AUTO, (void*) &ADC14->MEM[0],
			resultsBuffer[counter], NUM_OF_SENSORS);
		MAP_DMA_enableChannel(7);

        MAP_ADC14_toggleConversionTrigger();
    }
}
