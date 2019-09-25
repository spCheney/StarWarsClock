/*****************************************************************************
*
* Copyright (C) 2013 - 2017 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
* * Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "msp.h"
/* DriverLib Includes */
#include <cs.h>
#include <wdt_a.h>
#include <gpio.h>
#include <pcm.h>
#include <rtc_c.h>
#include <interrupt.h>


/* Initial time is 20.03.2017 Monday 21:10:32 */
const RTC_C_Calendar initalTime = { 00, 00, 10, 0, 20, 3, 2017 };
static volatile RTC_C_Calendar currentTime;
int alarm_time = [21, 12];

const int min1 = 0;                 //7seg 0
const int min2 = 1;                 //7seg 1
const int hr1 = 2;                  //7seg 2
const int hr2 = 3;                  //7seg 3

int time [4] = {0, 0, 0, 1};        //contains the time (min1, min2, hr1, hr2

int main(void)
{
    WDT_A_holdTimer();
        GPIO_setAsOutputPin( GPIO_PORT_P1, GPIO_PIN0);
    //Set Outputs for LEDs indicating a change in sec and min
        GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);

        PCM_setPowerState(PCM_AM_LF_VCORE0);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
        CS_setExternalClockSourceFrequency(32768,48000000);          //Initialize Clock
        CS_startLFXT(CS_LFXT_DRIVE3);
        CS_initClockSignal(CS_BCLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

        RTC_C_initCalendar(&initalTime, RTC_C_FORMAT_BINARY);                                   //set clock conditions
        RTC_C_setCalendarAlarm(alarm_time[1], alarm_time[0], RTC_C_ALARMCONDITION_OFF, RTC_C_ALARMCONDITION_OFF);
        RTC_C_clearInterruptFlag(RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT | RTC_C_CLOCK_ALARM_INTERRUPT);
    //Enable interrupts for sec, min and alarm
        RTC_C_enableInterrupt(RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT | RTC_C_CLOCK_ALARM_INTERRUPT);
        RTC_C_startClock();


        while (PCM->CTL1 & PCM_CTL1_PMR_BUSY);              //Turn on Low Power Mode
        PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL0_CPM_17;     //    ||
        while (PCM->CTL1 & PCM_CTL1_PMR_BUSY);              //    ||

        P1->DIR |= (BIT5 | BIT6 |  BIT7);
    //min1 uses 1.5; hr2 uses 6, 7;
        P2->DIR |= BIT3;
    //hr1 uses 2.3
        P3->DIR |= (BIT0 | BIT3 | BIT5 | BIT6 | BIT7);
    //min1 uses 3.3; hr1 uses 3.5, 3.7; h2 uses 3.0, 3.6;
        P4->DIR |= (BIT1 | BIT3 | BIT6 | BIT0 | BIT2 | BIT4 | BIT5 | BIT7);
    //min1 uses 4.1, 4.3, 4.6; min2 uses 4.0, 4.2, 4.4, 4.5, 4.7;
        P5->DIR |= (BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7);
    //min2 uses 5.4, 5.5; hr1 uses 5.1, 5.6; hr4 uses 5.0, 5.2, 5.7;
        P6->DIR |= (BIT4 | BIT5 | BIT6 | BIT7);
    //min1 uses 6.4, 6.5; hr1 uses 6.6, 6.7;

        //min1 pins: 3.3, 4.1, 4.3, 1.5, 4.6, 6.5, 6.4
        //min2 pins: 4.0, 4.2, 4.4, 4.5, 4.7, 5.4, 5.5
        //hr1 pins: 5.6, 6.6, 6.7, 2.3, 5.1, 3.5, 3.7
        //hr2 pins: 3.0, 5.7, 1.6, 1.7, 5.0, 5.2, 3.6


        int i;
    //loops through the array containing time and turns on the 7seg displays
        for(i = 0; i < 4; i = i + 1)
        {
            turnOnLed(time[i], i);
        }

        Interrupt_enableInterrupt(INT_RTC_C);
    //enables interrupts and sets the device to sleep
        Interrupt_enableSleepOnIsrExit();
        Interrupt_enableMaster();
        __sleep();
}

void RTC_C_IRQHandler (void) {
    uint32_t status;

    status = RTC_C_getEnabledInterruptStatus();
    RTC_C_clearInterruptFlag(status);

    if(status & RTC_C_CLOCK_READ_READY_INTERRUPT)           //goes off each sec
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
//if LED2.0 is off it turn it on if it's off it turn it on
    }

    if(status & RTC_C_TIME_EVENT_INTERRUPT)                 //goes off every min
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
//if LED2.1 is off it turn it on if it's off it turn it on

        time[min1] = time[min1] + 1;                    //increment min1 (0 to 9)
        if(time[min1] == 10)                    //increment min2 (0 to 5)
        {
            time[min2] = time[min2] + 1;
            time[min1] = 0;                     //reset min1 to 0
        }
        if(time[min2] == 6)
//increment hr1 (0 to 9 or 0 to 2 when hr2 = 1)
        {
            time[hr1] = time[hr1] + 1;
            time[min2] = 0;                     //reset min2 to 0
        }
        if(time[hr1] == 3 && time[hr2] == 1)    //at 13 hr2 goes to 0 and hr1 goes to 1
        {
            time[hr1] = 1;
            time[hr2] = 0;
        }
        if(time[hr1] == 10)                     //increment hr2 (0 to 1)
        {
            time[hr2] = time[hr2] + 1;
            time[hr1] = 0;                      //reset hr1 to 0
        }

        int i;
//loops through the array containing time and turns on the 7seg displays
        for(i = 0; i < 4; i = i + 1)
        {
            turnOn7Seg(time[i], i);
        }
    }

    if(status & RTC_C_CLOCK_ALARM_INTERRUPT)                //goes off during alarm
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);   //turn on pi
}

void turnOn7Seg(int num, int digit) {

        //leds on 7seg: L1  L2    H    M    B    R1   R2
        //pins on 7seg: 9   1     7    10   2    6    4
    //pins for min1 = 3.3, 4.1, 4.3, 1.5, 4.6, 6.5, 6.4
    //pins for min2 = 4.0, 4.2, 4.4, 4.5, 4.7, 5.4, 5.5
    //pins for hr1 =  5.6, 6.6, 6.7, 2.3, 5.1, 3.5, 3.7
    //pins for hr2 =  3.0, 5.7, 1.6, 1.7, 5.0, 5.2, 3.6

    if(digit == min1)
    {
        if(num == 0)            //turn on min1 to 0
        {
            P1->OUT |= BIT5;
            P3->OUT &= ~BIT3;
            P4->OUT &= ~(BIT1 | BIT3 | BIT6);
            P6->OUT &= ~(BIT4 | BIT5);
        }
        else if(num == 1)       //turn on min1 to 1
        {
            P1->OUT |= BIT5;
            P3->OUT |= BIT3;
            P4->OUT |= (BIT1 | BIT3 | BIT6);
            P6->OUT &= ~(BIT4 | BIT5);
        }
        else if(num == 2)       //turn on min1 to 2
        {
            P1->OUT &= ~BIT5;
            P3->OUT |= BIT3;
            P4->OUT &= ~(BIT1 | BIT3 | BIT6);
            P6->OUT &= ~BIT5;
            P6->OUT |= BIT4;
        }
        else if(num == 3)       //turn on min1 to 3
        {
            P1->OUT &= ~BIT5;
            P3->OUT |= BIT3;
            P4->OUT |= (BIT1 | BIT6);
            P4->OUT &= ~(BIT3 | BIT6);
            P6->OUT &= ~(BIT4 | BIT5);
        }
        else if(num == 4)       //turn on min1 to 4
        {
            P3->OUT &= ~BIT3;
            P4->OUT |= (BIT1 | BIT3 | BIT6);
            P6->OUT &= ~BIT5;
        }
        else if(num == 5)       //turn on min1 to 5
        {
            P4->OUT &= ~BIT3;
            P6->OUT |= BIT5;
            P4->OUT &= ~BIT6;
        }
        else if(num == 6)       //turn on min1 to 6
        {
            P4->OUT &= ~BIT1;
        }
        else if(num == 7)       //turn on min1 to 7
        {
            P1->OUT |= BIT5;
            P3->OUT |= BIT3;
            P4->OUT |= (BIT1 | BIT6);
            P4->OUT &= ~BIT3;
            P6->OUT &= ~BIT5;
        }
        else if(num == 8)       //turn on min1 to 8
        {
            P1->OUT &= ~BIT5;
            P3->OUT &= ~BIT3;
            P4->OUT &= ~(BIT1 | BIT6);
        }
        else if(num == 9)       ////turn on min1 to 9
        {
            P4->OUT |= (BIT1 | BIT6);
        }
    }
    else if(digit == min2)
    {
            //led on 7seg: L1  L2    H    M    B    R1   R2
            //pins on 7seg: 9   1     7    10   2    6    4
        //pins for min2 = 4.0, 4.2, 4.4, 4.5, 4.7, 5.4, 5.5

        if(num == 0)            //turn on min2 to 0
        {
            P4->OUT &= ~(BIT0 | BIT2 | BIT4 | BIT7);
            P4->OUT |= BIT5;
            P5->OUT &= ~(BIT4 | BIT5);
        }
        else if(num == 1)       //turn on min2 to 1
        {
            P4->OUT |= (BIT0 | BIT2 | BIT4 | BIT5 | BIT7);
            P5->OUT &= ~(BIT4 | BIT5);
        }
        else if(num == 2)       //turn on min2 to 2
        {
            P4->OUT &= ~(BIT2 | BIT4 | BIT5);
            P4->OUT |= BIT0;
            P4->OUT &= ~BIT7;
            P5->OUT |= BIT5;
            P5->OUT &= ~BIT4;
        }
        else if(num == 3)       //turn on min2 to 3
        {
            P4->OUT |= BIT2;
            P4->OUT &= ~(BIT4 | BIT5 | BIT7);
            P5->OUT &= ~BIT5;
        }
        else if(num == 4)       //turn on min2 to 4
        {
            P4->OUT &= ~BIT0;
            P4->OUT |= (BIT4 | BIT7);
        }
        else if(num == 5)       //turn on min2 to 5
        {
            P4->OUT &= ~(BIT4 | BIT7);
            P4->OUT |= BIT2;
            P5->OUT |= BIT4;
        }
        else if(num == 6)       //turn on min2 to 6
        {
            P4->OUT &= ~BIT2;
        }
        else if(num == 7)       //turn on min2 to 7
        {
            P4->OUT |= (BIT0 | BIT2 | BIT7 | BIT9);
            P5->OUT &= ~BIT4;
        }
        else if(num == 8)       //turn on min2 to 8
        {
            P4->OUT &= ~(BIT0 | BIT2 | BIT5 | BIT7);
        }
        else if(num == 9)       //turn on min2 to 9
        {
            P4->OUT |= (BIT2 | BIT7);
        }
    }
    else if(digit == hr1)
    {
            //led on 7seg: L1  L2    H    M    B    R1   R2
            //pins on 7seg: 9   1     7    10   2    6    4
        //pins for hr1 =  5.6, 6.6, 6.7, 2.3, 5.1, 3.5, 3.7

        if(num == 0)            //turn on hr1 to 0
        {
            P2->OUT |= BIT3;
            P3->OUT &= ~(BIT5 | BIT7);
            P5->OUT &= ~(BIT1 | BIT6);
            P6->OUT &= ~(BIT6 | BIT7);
        }
        else if(num == 1)       //turn on hr1 to 1
        {
            P2->OUT |= BIT3;
            P3->OUT &= ~(BIT5 | BIT7);
            P5->OUT |= (BIT1 | BIT6);
            P6->OUT |= (BIT6 | BIT7);
        }
        else if(num == 2)       //turn on hr1 to 2
        {
            P2->OUT &= ~BIT3;
            P3->OUT &= ~BIT5;
            P3->OUT |= BIT7;
            P5->OUT &= ~BIT1;
            P5->OUT |= BIT6;
            P6->OUT &= ~(BIT6 | BIT7);

        }
        else if(num == 3)       //turn on hr1 to 3
        {
            P2->OUT &= ~BIT3;
            P3->OUT &= ~(BIT5 | BIT7);
            P5->OUT &= ~BIT1;
            P5->OUT |= BIT6;
            P6->OUT |= BIT6;
            P6->OUT & ~BIT7;
        }
        else if(num == 4)       //turn on hr1 to 4
        {
            P5->OUT &= ~BIT6;
            P5->OUT |= BIT1;
            P6->OUT |= BIT7;
        }
        else if(num == 5)       //turn on hr1 to 5
        {
            P3->OUT |= BIT5;
            P5->OUT &= ~BIT1;
            P6->OUT &= ~BIT7;
        }
        else if(num == 6)       //turn on hr1 to 6
        {
            P6->OUT &= ~BIT6;
        }
        else if(num == 7)       //turn on hr1 to 7
        {
            P2->OUT |= BIT3;
            P3->OUT &= ~BIT5;
            P5->OUT |= (BIT1 | BIT6);
            P6->OUT |= BIT6;
        }
        else if(num == 8)       //turn on hr1 to 8
        {
            P2->OUT &= ~BIT3;
            P5->OUT &= ~(BIT1 | BIT6);
            P6->OUT &= ~BIT6;
        }
        else if(num == 9)       //turn on hr1 to 9
        {
            P5->OUT |= BIT1;
            P6->OUT |= BIT6;
        }
    }
    else if(digit == hr2)
    {
           //led on 7seg: L1  L2    H    M    B    R1   R2
           //pins on 7seg: 9   1     7    10   2    6    4
        //pins for hr2 = 3.0, 5.7, 1.6, 1.7, 5.0, 5.2, 3.6

        if(num == 0)            //turn on hr2 to 0
        {
            P1->OUT |= BIT6;
            P1->OUT |= BIT7;
            P3->OUT |= (BIT0 | BIT6);
            P5->OUT |= (BIT0 | BIT2 | BIT7);
        }
        else if(num == 1)       //turn on hr2 to 1
        {
            P1->OUT |= (BIT6 | BIT7);
            P3->OUT |= BIT0;
            P5->OUT |= (BIT0 | BIT7);
            P3->OUT &= ~BIT6;
            P5->OUT &= ~BIT2;
        }
    }
}

//Right now this function toggles the led every second
void tone(void) {

    int LED1 = BIT0;
    int TIMER_PERIOD = 3000000;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;         //stops watchdog reset signal and timer

    P1->DIR = LED1;         //p1.0 is an output

    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE |     //32 bit counter is used
            TIMER32_CONTROL_MODE |          //free-running mode is selected
            TIMER32_CONTROL_PRESCALE_1;     //used to divide the clock frequency, now it is divide by 16
    TIMER32_1->LOAD = TIMER_PERIOD;         //counts down from the TIMER_PERIOD

    while(PCM->CTL1 & PCM_CTL1_PMR_BUSY);       //wait until it an LPM request is finished being processed
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;      //some AM power request
    while (PCM->CTL1 & PCM_CTL1_PMR_BUSY);

    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_CANK0_RDCTL_WAIT_MASK)) |
            FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) |
            FLCTL_BANK1_RDCTL_WAIT_1;

    PJ->SEL0 |= BIT2 | BIT3;
    PJ->SEL1 &= ~(BIT2 | BIT3);

    CS->KEY = CS_KEY_VAL;       //all cs registers are available for configuration
    CS->CTL2 |= CS_CTL_HFXT_EN | CS_CTL2_HFXTFREQ_6;        //HFXT is enable for frequency ranges 40-48 MHZ
    while(CS->IFG & CS_IFG_HFXTIFG)             //while there is a CS or HFXT interrupt
        CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;    //clear the interrupt
    CS->CTL1 &= ~(CS_CTL1_SEL_MASK | CS_CTL1_DIVM_MASK);
    CS->CTL1 |= CS_CTL1_SELM_5;     //use HFXT as clock source DCO if unavailable
    CS->KEY = 0;        //registers can no longer be accessed

    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE |      //timer is enabled
            TIMER32_CONTROL_IE;         //interrupt is enabled

    __enable_irq();
    NVIC->ISER[0] = 1 << ((T32_INT1_IRQn) & 31);

    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    __sleep();
}

void T32_INT1_IRQHandler(void) {
    TIMER32_1->INTCLR = 0;      //clears interrupt
    P1->OUT ^= LED1;
}



