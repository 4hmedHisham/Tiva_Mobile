#include "Lcd.h"

void _delay_ms(uint32_t ui32Ms) {

	// 1 clock cycle = 1 / SysCtlClockGet() second
	// 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
	// 1 second = SysCtlClockGet() / 3
	// 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000
	
	SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}

void PORTD_Init(void)
{      
        SYSCTL_RCGCGPIO_R |= 0x08 ; //activate clock for Port D
        while((SYSCTL_PRGPIO_R&0x08) == 0){}; //we next will wait for its status bit in the PRGPIO to be true
        GPIO_PORTD_LOCK_R = 0x4C4F434B ; //Unlock the PORTE lock register 
        GPIO_PORTD_CR_R = 0x0FF ; //Allow changes for *8* pins 
        GPIO_PORTD_DIR_R = 0xFF  ; //  0000 1111   specifies bit for bit whether the corresponding pins are input(0) or output(1)
        GPIO_PORTD_DEN_R |= 0xFF ; //Digital Enable for my Digital pins  
        GPIO_PORTD_DATA_R=0x0;                        // sends 1s to pins PE 0,1,2,3 TO DETECT NEXT INTERRUPT

}
void PORTB_Init(void)
{      
        SYSCTL_RCGCGPIO_R |= 0x02 ; //activate clock for Port B
        while((SYSCTL_PRGPIO_R&0x02) == 0){}; //we next will wait for its status bit in the PRGPIO to be true
        GPIO_PORTB_LOCK_R = 0x4C4F434B ; //Unlock the PORTE lock register 
        GPIO_PORTB_CR_R = 0x0FF ; //Allow changes for *8* pins 
        GPIO_PORTB_DIR_R = 0xFF  ; //  0000 1111   specifies bit for bit whether the corresponding pins are input(0) or output(1)
        GPIO_PORTB_DEN_R |= 0xFF ; //Digital Enable for my Digital pins  
        GPIO_PORTB_DATA_R=0x0;                        // sends 1s to pins PE 0,1,2,3 TO DETECT NEXT INTERRUPT

}
void Lcd_Init(void)
{
  PORTB_Init(); 
  PORTD_Init(); 
  _delay_ms(5);
  
  //Display on ,cursor off , blinking off
  Lcd_SendCommand(0x38); //8 bit
  Lcd_SendCommand(0x0F); //screen on cursor blink
  Lcd_SendCommand(0x01); //clear
  Lcd_SendCommand(0x06); //first line
  }

void Lcd_SendCommand(uint8_t data)
{
  
  GPIO_PORTB_DATA_R = data;
  GPIO_PORTD_DATA_R &= ~((1U<<rw)| (1U<<rs));
  GPIO_PORTD_DATA_R |= (1U<<en) ;
  _delay_ms(6);
  GPIO_PORTD_DATA_R &= ~(1U<<en);
  _delay_ms(6);
  }

void Lcd_SendString(uint8_t *StringPtr)
{
	while(*StringPtr != 0)
	{
		Lcd_SendChar(*StringPtr);
		StringPtr ++ ;
	}

}

void Lcd_SendChar(uint8_t data)
{
  GPIO_PORTB_DATA_R = data;
  GPIO_PORTD_DATA_R &= ~(1U<<rw);
  GPIO_PORTD_DATA_R |= ((1U<<en)| (1U<<rs)) ;
  _delay_ms(6);
  GPIO_PORTD_DATA_R &= ~(1U<<en);
  _delay_ms(6);
}

void Lcd_printstring(uint8_t *StringPtr1 , uint8_t *StringPtr2)
{
  Lcd_SendCommand(0x01); //clear
  Lcd_SendCommand(0x80); //first line
  Lcd_SendString(StringPtr1);
  Lcd_SendCommand(0xC0); //Second line
  Lcd_SendString(StringPtr2);
}

void Lcd_SendSecondString(uint8_t *StringPtr)
{
  Lcd_SendCommand(0xC0); //Second line
  Lcd_SendString(StringPtr);
}
