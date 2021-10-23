#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "clock.h"
#include "gpio.h"
#include "wait.h"
#include "uart0.h"
#include "library.h"
#include <math.h>
//#define MAX_CHARS 80
//#define MAX_FIELDS 5
#define CR "\r\n"


#define PB4 16              //green_wire
#define PB5 32              //yellow_wire
#define PB6 64              //black_wire
#define PB7 128             //white_wire
#define WHITE_WIRE PORTD,1
#define BLACK_WIRE PORTD,2
#define GREEN_WIRE PORTD,3
#define YELLOW_WIRE PORTD,0
#define COLLECTOR PORTB,1
int phase = 0;
int degree = 0;
int waitTime = 8000; //8000



void setPWMDutyCycle(uint8_t id, uint16_t pwmA, uint16_t pwmB)
{
    if(id == 0)
    {
        //PWM0_0_CMPA_R = 500;
        PWM0_0_CMPA_R = pwmA;
        PWM0_0_CMPB_R = pwmB;
    }
    else if(id == 1)
    {
       PWM0_1_CMPA_R = pwmA;
       PWM0_1_CMPB_R = pwmB;
    }

}

void initializePWM()
{
    //Enable Clocks
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    _delay_cycles(3);

    //
    GPIO_PORTB_DIR_R |= PB4 | PB5 | PB6 | PB7;
    GPIO_PORTB_DR2R_R |= PB4 | PB5 | PB6 | PB7;
    GPIO_PORTB_DEN_R |= PB4 | PB5 | PB6 | PB7;
    GPIO_PORTB_AFSEL_R |= PB4 | PB5 | PB6 | PB7;
    GPIO_PORTB_PCTL_R &= ~(GPIO_PCTL_PB4_M | GPIO_PCTL_PB5_M
                        | GPIO_PCTL_PB6_M | GPIO_PCTL_PB7_M);
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB4_M0PWM2 | GPIO_PCTL_PB5_M0PWM3
                       | GPIO_PCTL_PB6_M0PWM0 | GPIO_PCTL_PB7_M0PWM1;

    SYSCTL_SRPWM_R = SYSCTL_SRPWM_R0;
    SYSCTL_SRPWM_R = 0;

    PWM0_1_CTL_R = 0;
    PWM0_2_CTL_R = 0;

    //0A     0B     1A     1B...
    //M0PWM0 M0PWM1 M0PWM2 M0PWM3...
    PWM0_0_GENA_R = PWM_0_GENA_ACTCMPAD_ZERO | PWM_0_GENA_ACTLOAD_ONE;
    PWM0_0_GENB_R = PWM_0_GENB_ACTCMPBD_ZERO | PWM_0_GENB_ACTLOAD_ONE;
    PWM0_1_GENA_R = PWM_0_GENA_ACTCMPAD_ZERO | PWM_0_GENA_ACTLOAD_ONE;
    PWM0_1_GENB_R = PWM_0_GENB_ACTCMPBD_ZERO | PWM_0_GENB_ACTLOAD_ONE;

    PWM0_0_LOAD_R = 1024;
    PWM0_1_LOAD_R = 1024;

    PWM0_INVERT_R = PWM_INVERT_PWM0INV | PWM_INVERT_PWM1INV | PWM_INVERT_PWM2INV | PWM_INVERT_PWM3INV;

    PWM0_0_CMPA_R = 0;
    PWM0_0_CMPB_R = 0;
    PWM0_1_CMPA_R = 0;
    PWM0_1_CMPB_R = 0;

    PWM0_0_CTL_R = PWM_0_CTL_ENABLE;
    PWM0_1_CTL_R = PWM_0_CTL_ENABLE;
    PWM0_ENABLE_R = PWM_ENABLE_PWM0EN | PWM_ENABLE_PWM1EN | PWM_ENABLE_PWM2EN | PWM_ENABLE_PWM3EN;
}

void initHw()
{
    initSystemClockTo40Mhz();
    enablePort(PORTD);
    enablePort(PORTB);
    selectPinPushPullOutput(WHITE_WIRE);
    selectPinPushPullOutput(BLACK_WIRE);
    selectPinPushPullOutput(GREEN_WIRE);
    selectPinPushPullOutput(YELLOW_WIRE);
    selectPinDigitalInput(COLLECTOR);
}
void setPhase() {
    int A = abs(cos(degree) * 1024);
    int B = abs(sin(degree) * 1024);
    switch(phase) {
    case 0:
        setPWMDutyCycle(1, B, A);         //1 B A
//        setPinValue(WHITE_WIRE, 1); A
//        setPinValue(BLACK_WIRE, 0);
        waitMicrosecond(waitTime);
        break;
    case 1:
        setPWMDutyCycle(1, B, A);         //1 BA
        setPWMDutyCycle(0, B, A);         //0 BA
        waitMicrosecond(waitTime);
        break;
    case 2:
        setPWMDutyCycle(0, B, A);         //0 BA
//        setPinValue(GREEN_WIRE, 1); B
//        setPinValue(YELLOW_WIRE, 0);
        waitMicrosecond(waitTime);
        break;
    case 3:
        setPWMDutyCycle(0, B, A);         //0 BA
        setPWMDutyCycle(1, A, B);         //1 AB
        waitMicrosecond(waitTime);
        break;
    case 4:
        setPWMDutyCycle(1, A, B);         //1 AB
//        setPinValue(WHITE_WIRE, 0); C
//        setPinValue(BLACK_WIRE, 1);
        waitMicrosecond(waitTime);
        break;
    case 5:
        setPWMDutyCycle(1, A, B);         //1 AB
        setPWMDutyCycle(0, A, B);         //0 AB
        waitMicrosecond(waitTime);
        break;
    case 6:
        setPWMDutyCycle(0, A, B);         //0 AB
//        setPinValue(GREEN_WIRE, 0); D
//        setPinValue(YELLOW_WIRE, 1);
        waitMicrosecond(waitTime);
        break;
    case 7:
        setPWMDutyCycle(0, A, B);         //0 AB
        waitMicrosecond(waitTime);
        break;
    }
}

//void setPhase() {
//    int A = abs(cos(degree) * 1024);
//    int B = abs(sin(degree) * 1024);
//    switch(phase) {
//    case 0:
////        setPWMDutyCycle(1, 1014, 10); //B A
//        setPWMDutyCycle(1, B, A);
////        setPinValue(WHITE_WIRE, 1); //A
////        setPinValue(BLACK_WIRE, 0); //B
//        waitMicrosecond(waitTime);
//        break;
//    case 1:
////        setPWMDutyCycle(0, 10, 1014); //B A
//        setPWMDutyCycle(0, B, A);
////        setPinValue(GREEN_WIRE, 1); //B
////        setPinValue(YELLOW_WIRE, 0);//A
//        waitMicrosecond(waitTime);
//        break;
//    case 2:
////        setPWMDutyCycle(1, 10, 1014);       //A B
//        setPWMDutyCycle(1, A, B);
////        setPinValue(WHITE_WIRE, 0); C
////        setPinValue(BLACK_WIRE, 1);
//        waitMicrosecond(waitTime);
//        break;
//    case 3:
////        setPWMDutyCycle(0, 1014, 10);       //A B
//        setPWMDutyCycle(0, A, B);
////        setPinValue(GREEN_WIRE, 0); D
////        setPinValue(YELLOW_WIRE, 1);
//        waitMicrosecond(waitTime);
//        break;
//    }
//}

void cw()
{
    phase = (phase+1)%8;
    setPhase();
}

void ccw()
{

//    phase = (phase-1)%8;
    phase--;
    if(phase < 0)
        phase = 7;
    setPhase();
}

int main(void)
{
 /*
  * infinite loop
  *
  */
    USER_DATA userData;
    initHw();
    initUart0();
    initializePWM();
    setUart0BaudRate(115200, 40e6);
    putsUart0("Enter an angle: ");
    getsUart0(&userData);
    parseFields(&userData);
    cw();
    phase = 0;
    cw();


    waitMicrosecond(1000000);
//    while(!getPinValue(COLLECTOR))
//    {
////        if(getPinValue(COLLECTOR) == 1)
//        cw();
//    }
//    int i = 0;
//    while(i < 19)
//    {
//        ccw();
//        i++;
//    }
//    while(true)
//    {
//        int i = 0;
//        while(i <= 16)
//        {
//            cw();
//            i++;
//        }
//        i = 0;
//        while(i <= 16)
//        {
//            ccw();
//            i++;
//        }
//    }
//    degree = 20;
    int angle = 60;
    //90 - 75
    //60 - 49
    double count = (double)angle * 0.9;
    while(1) {
//        degree = 20;
        double counter = count;
        waitTime = 8000;
        while(counter >= 0.0) {
            cw();
            counter--;
        }
        waitMicrosecond(3000000);
//        degree = 20;
        waitTime = 8000;
        while(counter <= count) {
            ccw();
            counter++;
        }
        waitMicrosecond(3000000);
    }

//
//    int angle = myAtoi(userData.buffer);
////    putsUart0("\n");
//    putsUart0(userData.buffer);
//    putsUart0(" degrees\n");
//
//    if(angle > 0)
//    {
//        float angleInc = 0;
//        while(angleInc <= angle)
//        {
//            cw();
//            angleInc+= .9;
//        }
//    }
//    else if(angle < 0)
//    {
//       float angleDec = 0;
//       while(angleDec > angle)
//       {
//           ccw();
//           angleDec -= .9;
//       }
//    }


    while(true);
}
