#include "rtc.h"




void rtc_adjust(void){
  if(RTC.seconds>=60){RTC.seconds=0;RTC.minutes++;}
  if(RTC.minutes>=60){RTC.minutes=0;RTC.hours++;  }
  if(RTC.hours>=24){RTC.hours=0;                  }
}

void rtc_input(uint32_t hours,uint32_t minutes,uint32_t seconds){
RTC.hours=hours;
RTC.minutes=minutes;
RTC.seconds=seconds;
}

void timer1flowhandler(void){    //when timer1 overflows it increment counter because one timeout happened
      TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
      RTC.seconds++;
      rtc_adjust();
}

void rtctimer1_init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);                                 // Enable the Timer1 peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1));                          // Wait for the Timer1 module to be ready.
    TimerDisable(TIMER1_BASE, TIMER_A);                                           // Enable the timer.
    TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC_UP);                            // Configure TimerA as a up edge time capture timer
    TimerLoadSet(TIMER1_BASE, TIMER_A, loadtime);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT );
    TimerIntRegister(TIMER1_BASE, TIMER_A, timer1flowhandler);
    TimerControlEvent(TIMER1_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);              // Configure the counter (TimerA) to count pos edges.
    TimerEnable(TIMER1_BASE, TIMER_A);                                          // Enable the timer.
}

