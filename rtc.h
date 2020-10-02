#ifndef rtc
#define  rtc
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "tm4c123gh6pm.h"

#define GPIO_PF0_T0CCP0         0x00050007 //didn't load from pin_map.h even it was defined correctly
#define loadtime                16000000
struct real_time{
  uint32_t hours;
  uint32_t minutes;
  uint32_t seconds;
} ;
extern struct real_time RTC; //real time clock variable

void rtc_adjust(void);
void rtc_input(uint32_t hours,uint32_t minutes,uint32_t seconds);
void timer1flowhandler(void);
void rtctimer1_init(void);
#endif // 