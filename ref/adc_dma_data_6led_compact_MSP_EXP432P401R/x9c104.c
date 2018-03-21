/*
 * x9c104.c
 *
 *  Created on: Sep 27, 2017
 *      Author: litia
 */

#include <main.h>

void potentiometerstart(){
    GPIO_setAsOutputPin( // CS
            GPIO_PORT_P2,
            GPIO_PIN5
            );
    GPIO_setAsOutputPin( // U/D
            GPIO_PORT_P2,
            GPIO_PIN6
            );
    GPIO_setAsOutputPin( // INC
            GPIO_PORT_P2,
            GPIO_PIN7
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN5
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN6
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN7
            );
}

void store(){
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN7
            );
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN5
            );
    __delay_cycles(24000);
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN5
            );
}

void increment() {
  __delay_cycles(24000);
  GPIO_setOutputLowOnPin(
          GPIO_PORT_P2,
          GPIO_PIN7
          );
  __delay_cycles(24000);
}

void potUp(){
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN5
            );
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN6
            );
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN7
            );
  increment();
}

void potDown(){
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN5
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN6
            );
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN7
            );
  increment();
}

void reset(){
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN5
            );
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P2,
            GPIO_PIN6
            );
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN7
            );
    char i;
    for (i = 0; i < 100; i++){
          GPIO_setOutputHighOnPin(
                    GPIO_PORT_P2,
                    GPIO_PIN7
                    );
          __delay_cycles(24000);
          GPIO_setOutputLowOnPin(
                      GPIO_PORT_P2,
                      GPIO_PIN7
                      );
          __delay_cycles(24000);
    }
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN7
            );
    GPIO_setOutputHighOnPin(
            GPIO_PORT_P2,
            GPIO_PIN5
            );
    __delay_cycles(24000);
}

void setPotValue(int counter){
  reset();
  int i;
  for(i = 0; i < counter; i++){
    potUp();
    store();
  }
}


