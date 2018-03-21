/*
 * adc_settings.c
 *
 *  Created on: Sep 26, 2017
 *      Author: litia
 */

#include <main.h>

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

void clock_init(){
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
}

void timer_init(){
    /* Configuring WDT in interval mode to trigger every 32K clock iterations.
     * This comes out to roughly every 8ms */
    MAP_WDT_A_initIntervalTimer(WDT_A_CLOCKSOURCE_VLOCLK,
                                WDT_A_CLOCKITERATIONS_64);

//    /* Configuring WDT in interval mode to trigger every 32K clock iterations.
//     * This comes out to roughly every 8*8ms */
//    MAP_WDT_A_initIntervalTimer(WDT_A_CLOCKSOURCE_VLOCLK,
//                                WDT_A_CLOCKITERATIONS_512);

    /* Enabling interrupts and starting the watchdog timer */
    MAP_Interrupt_enableInterrupt(INT_WDT_A);
    MAP_Interrupt_enableMaster();
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_WDT_A_startTimer();

    MAP_Interrupt_enableMaster();
}

void pinout_init(){
    /* Terminating all pins to minimize power consumption */
    P1->OUT = 0x00;
    P1->DIR = 0xFF;
    P2->OUT = 0x00;
    P2->DIR = 0xFF;
    P3->OUT = 0x00;
    P3->DIR = 0xFF;
    P4->OUT = 0x00;
    P4->DIR = 0xFF;
    P5->OUT = 0x00;
    P5->DIR = 0xFF;
    P6->OUT = 0x00;
    P6->DIR = 0xFF;
    P7->OUT = 0x00;
    P7->DIR = 0xFF;
    P8->OUT = 0x00;
    P8->DIR = 0xFF;
    P9->OUT = 0x00;
    P9->DIR = 0xFF;
    P10->OUT = 0x00;
    P10->DIR = 0xFF;
    PJ->OUT = 0x00;
    PJ->DIR = 0xFF;

    //init switch pins
    GPIO_setAsOutputPin( // OFF/ON
            GPIO_PORT_P3,
            GPIO_PIN4
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P3,
            GPIO_PIN4
            );

    // for camera
    GPIO_setOutputLowOnPin(
			GPIO_PORT_P3,
			GPIO_PIN0
			);
    GPIO_setOutputHighOnPin(
    			GPIO_PORT_P3,
    			GPIO_PIN0
    			);

    GPIO_setAsOutputPin( // C
			GPIO_PORT_P5,
			GPIO_PIN6
			);
    GPIO_setAsOutputPin( // B
            GPIO_PORT_P5,
            GPIO_PIN7
            );
    GPIO_setAsOutputPin( // A
            GPIO_PORT_P3,
            GPIO_PIN5
            );
    GPIO_setAsOutputPin( // IN1
			GPIO_PORT_P8,
			GPIO_PIN0
			);
    GPIO_setAsOutputPin( // IN2
			GPIO_PORT_P8,
			GPIO_PIN1
			);
    P5OUT &= ~BIT6; //low
	P5OUT |= BIT7; //high
	P3OUT &= ~BIT5; //low
	P8OUT &= ~BIT0; //low
	P8OUT &= ~BIT1; //low
}

void adc_dma_init(){
    /* Setting Highest Power Mode*/
    MAP_ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);

    //![Single Sample Mode Configure]
    /* Initializing ADC (MCLK/1/1) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    /* Configuring GPIOs for Analog In */
//    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
//                GPIO_PIN1 | GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN5 | GPIO_PIN4 | GPIO_PIN3 | GPIO_PIN2 | GPIO_PIN1
                    | GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
//    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
//            GPIO_PIN7 | GPIO_PIN6| GPIO_PIN5| GPIO_PIN4| GPIO_PIN3
//            | GPIO_PIN2| GPIO_PIN1| GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);

    /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM11 (A0 - A5)  with no repeat)
     * with internal 2.5v reference */
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM5, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM0,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM1,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM2,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A2, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM3,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A3, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM4,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A4, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM5,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A5, false);

    MAP_ADC14_enableReferenceBurst();

    /* Configuring DMA module */
    MAP_DMA_enableModule();
    MAP_DMA_setControlBase(controlTable);

    /*
     * Primary DMA Channel, ADC14
     * Size = 16bits
     * Source Increment = 32bits
     * Destination Increment = 32bits
     * Arbitration = 1 , no other sources
     */

    MAP_DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14,
        UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_1);

    /* Assigning/Enabling Interrupts */
    MAP_DMA_assignInterrupt(DMA_INT1, 7);
    MAP_Interrupt_enableInterrupt(INT_DMA_INT1);
    MAP_DMA_assignChannel(DMA_CH7_ADC14);
    MAP_DMA_clearInterruptFlag(7);

    /* Now that the DMA is primed and setup, enabling the channels. The ADC14
     * hardware should take over and transfer/receive all bytes.The DMA is
     * triggered after the conversion in single-channel conversion mode or
     * after the completion of a sequence of channel conversions in
     * sequence-ofchannels conversion mode. */
    MAP_DMA_enableChannel(7);

    /* Configuring Sample Timer */
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Enabling the start of the sample */
    MAP_ADC14_enableConversion();
}

void uart_init(eUSCI_UART_Config uartConfig){
	//--------- Setting the UART function for P1.1 & P1.2 --------//
	/* Selecting P1.2 and P1.3 in UART mode */
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
			GPIO_PIN1 |	GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

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

