#ifndef __KEYPAD_H__
#define __KEYPAD_H__

void delayMs(int);
void PORTE_Init(void);
void PORTF_Init(void);
void GPIOPortF_Handler(void);  
char Output (void);
  
#endif // __KEYPAD_H__