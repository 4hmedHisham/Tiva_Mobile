#ifndef Lcd_H_
#define Lcd_H_
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#define rs 0 //pins of rs en rw to be connected to protd 0 , 1 , 2 pins
#define en 1
#define rw 2
//b port is for data kollo 
//d port is for commands
void PORTB_Init(void);
void PORTD_Init(void);
void _delay_ms(uint32_t ui32Ms);
void Lcd_Init(void);
void Lcd_SendCommand(uint8_t data);
void Lcd_SendString(uint8_t *StringPtr);
void Lcd_SendChar(uint8_t data);
void Lcd_printstring(uint8_t *StringPtr1 , uint8_t *StringPtr2);
void Lcd_SendSecondString(uint8_t *StringPtr);

#endif
