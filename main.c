//#include <stdint.h>
//#include <stdio.h>
//#include <stdbool.h>
//#include "tm4c123gh6pm.h"
//#include "clock.h"
//#include "gpio.h"
//#include "wait.h"
//#include "library.h"
//
//
//#define YELLOW_WIRE PORTD,0
//#define WHITE_WIRE PORTD,1
//#define BLACK_WIRE PORTD,2
//#define GREEN_WIRE PORTD,3
//#define COLLECTOR PORTB,1
//
//int waitTime = 400000;
//int phase = 0;
//
//// Bitband aliases
//#define RED_LED      (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 1*4)))
//#define GREEN_LED    (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 3*4)))
//
//// PortF masks
//#define GREEN_LED_MASK 8
//#define RED_LED_MASK 2
//
//
////-----------------------------------------------------------------------------
//// Subroutines
////-----------------------------------------------------------------------------
//
//// Initialize Hardware
//void initHw()
//{
//    // Initialize system clock to 40 MHz
//    initSystemClockTo40Mhz();
//
//    // Enable clocks
//    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R5;
//    _delay_cycles(3);
//
//    // Configure LED pins
//    GPIO_PORTF_DIR_R |= GREEN_LED_MASK | RED_LED_MASK;  // bits 1 and 3 are outputs
//    GPIO_PORTF_DR2R_R |= GREEN_LED_MASK | RED_LED_MASK; // set drive strength to 2mA (not needed since default configuration -- for clarity)
//    GPIO_PORTF_DEN_R |= GREEN_LED_MASK | RED_LED_MASK;  // enable LEDs
//
//    initSystemClockTo40Mhz();
//    enablePort(PORTD);
//    enablePort(PORTB);
//    selectPinPushPullOutput(WHITE_WIRE);
//    selectPinPushPullOutput(BLACK_WIRE);
//    selectPinPushPullOutput(GREEN_WIRE);
//    selectPinPushPullOutput(YELLOW_WIRE);
//    selectPinDigitalInput(COLLECTOR);
//}
//
////void initHw()
////{
////    initSystemClockTo40Mhz();
////    enablePort(PORTD);
////    enablePort(PORTB);
////    selectPinPushPullOutput(WHITE_WIRE);
////    selectPinPushPullOutput(BLACK_WIRE);
////    selectPinPushPullOutput(GREEN_WIRE);
////    selectPinPushPullOutput(YELLOW_WIRE);
////    selectPinDigitalInput(COLLECTOR);
////}
//void setPhase() {
//    switch(phase) {
//    case 0:
//        setPinValue(WHITE_WIRE, 1);
//        setPinValue(BLACK_WIRE, 0);
//        waitMicrosecond(waitTime);
//        break;
//
//    case 1:
//        setPinValue(GREEN_WIRE, 1);
//        setPinValue(YELLOW_WIRE, 0);
//        waitMicrosecond(waitTime);
//        break;
//
//    case 2:
//        setPinValue(WHITE_WIRE, 0);
//        setPinValue(BLACK_WIRE, 1);
//        waitMicrosecond(waitTime);
//        break;
//
//    case 3:
//        setPinValue(GREEN_WIRE, 0);
//        setPinValue(YELLOW_WIRE, 1);
//        waitMicrosecond(waitTime);
//        break;
//    }
//}
//
////void setPhase() {
//////    int A = abs(cos(degree) * 1024);
//////    int B = abs(sin(degree) * 1024);
////    switch(phase) {
////    case 0:
//////        setPWMDutyCycle(1, B, A);
////        setPinValue(WHITE_WIRE, 1); //A
////        setPinValue(BLACK_WIRE, 0); //B
////        waitMicrosecond(waitTime);
////        break;
////    case 1:
//////        setPWMDutyCycle(1, B, A);
//////        setPWMDutyCycle(0, B, A);
////        setPinValue(WHITE_WIRE, 1); //A
////        setPinValue(BLACK_WIRE, 0); //B
////        setPinValue(GREEN_WIRE, 1); //C
////        setPinValue(YELLOW_WIRE, 0);//D
////        waitMicrosecond(waitTime);
////        break;
////    case 2:
//////        setPWMDutyCycle(0, B, A);
////        setPinValue(GREEN_WIRE, 1); //B
////        setPinValue(YELLOW_WIRE, 0);
////        waitMicrosecond(waitTime);
////        break;
////    case 3:
//////        setPWMDutyCycle(0, B, A);
//////        setPWMDutyCycle(1, A, B);
////        setPinValue(GREEN_WIRE, 1); //A
////        setPinValue(YELLOW_WIRE, 0);//B
////        setPinValue(WHITE_WIRE, 0); //C
////        setPinValue(BLACK_WIRE, 1); //D
////        waitMicrosecond(waitTime);
////        break;
////    case 4:
//////        setPWMDutyCycle(1, A, B);
////        setPinValue(WHITE_WIRE, 0); //C
////        setPinValue(BLACK_WIRE, 1); //D
////        waitMicrosecond(waitTime);
////        break;
////    case 5:
//////        setPWMDutyCycle(1, A, B);
//////        setPWMDutyCycle(0, A, B);
////        setPinValue(WHITE_WIRE, 0); //C
////        setPinValue(BLACK_WIRE, 1); //D
////        setPinValue(GREEN_WIRE, 0); //D
////        setPinValue(YELLOW_WIRE, 1);//
////        waitMicrosecond(waitTime);
////        break;
////    case 6:
//////        setPWMDutyCycle(0, A, B);
////        setPinValue(GREEN_WIRE, 0); //D
////        setPinValue(YELLOW_WIRE, 1);
////        waitMicrosecond(waitTime);
////        break;
////    case 7:
//////        setPWMDutyCycle(0, A, B);
////        setPinValue(WHITE_WIRE, 1); //A
////        setPinValue(BLACK_WIRE, 0); //B
////        setPinValue(GREEN_WIRE, 0); //D
////        setPinValue(YELLOW_WIRE, 1);
////        waitMicrosecond(waitTime);
////        break;
////    }
////
////}
//
//void cw()
//{
//    phase = (phase+1)%8;
//    setPhase();
//}
//
//void ccw()
//{
//
////    phase = (phase-1)%8;
//    phase--;
//    if(phase < 0)
//        phase = 7;
//    setPhase();
//}
//
//#define DEBUG
//
//int main(void)
//{
//    initHw();
//    initUart0();
//    setUart0BaudRate(115200, 40e6);
//
//    USER_DATA data;
//
////    putsUart0("Enter an angle> ");
//
//    // Get the string from the user
////    getsUart0(&data);
//
//    // Echo back to the user of the TTY interface for testing
////    putsUart0(data.buffer);
////    putcUart0('\n');
//
//    // Parse fields
////    parseFields(&data);
////    putcUart0(data.buffer[0]);
////    int x = myAtoi(&data.buffer);
//
////    if(x < 0) {
////        while(true)
////            cw();
////    }
//
////    cw();
////    phase = 0;
////    cw();
////
//    waitMicrosecond(1000000);
//
//    int counter = 75;
//    while(1) {
////        degree = 20;
//        waitTime = 70000;
//        while(counter > -1) {
//            cw();
//            counter--;
//        }
////        degree = 20;
//        waitTime = 70000;
//        while(counter < 76) {
//            ccw();
//            counter++;
//        }
//    }
//
//    while(!getPinValue(COLLECTOR))
//    {
//        cw();
//    }
////    int j = 0;
////    while(j < 22)
////    {
////        ccw();
////        j++;
////    }
////    while(true)
////    {
////        int i = 0;
////        while(i <= 16)
////        {
////            cw();
////            i++;
////        }
////        i = 0;
////        while(i <= 16)
////        {
////            ccw();
////            i++;
////        }
////    }
//    while(true);
//}
