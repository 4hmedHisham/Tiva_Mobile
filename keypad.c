#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>

//Keypad connected to PORT E, Pins 0,1,2,3 //OUTPUT from tiva
//connected to PORT F, Pins 1,2,3,4 // INPUT to tiva

void delayMs(int n)
{
    int32_t i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
            {}  /* do nothing for 1 ms */
}

void PORTE_Init(void)
{      
        SYSCTL_RCGCGPIO_R |= 0x10 ; //activate clock for Port B
        while((SYSCTL_PRGPIO_R&0x00000010) == 0){}; //we next will wait for its status bit in the PRGPIO to be true
        GPIO_PORTE_LOCK_R = 0x4C4F434B ; //Unlock the PORTE lock register 
        GPIO_PORTE_CR_R = 0x0FF ; //Allow changes for *8* pins 
        GPIO_PORTE_DIR_R = 0xFF  ; //  0000 1111   specifies bit for bit whether the corresponding pins are input(0) or output(1)
        GPIO_PORTE_PDR_R |= 0xFF ; //Set bits in the PUR register for the switches inputs to have an internal pull-up resistor
        GPIO_PORTE_DEN_R |= 0xFF ; //Digital Enable for my Digital pins  
        
        GPIO_PORTE_DATA_R=0xF;                        // sends 1s to pins PE 0,1,2,3 TO DETECT NEXT INTERRUPT

}

void PORTF_Init(void)
{ 
  SYSCTL_RCGCGPIO_R |= 0x20;
  while((SYSCTL_PRGPIO_R&0x00000020) == 0){}; 
  GPIO_PORTF_LOCK_R = 0x4C4F434B ;               // Unlock the PORTF lock register 
  GPIO_PORTF_DIR_R = 0x00;                       // make PF1,2,3,4 inputs
  GPIO_PORTF_PDR_R |= 0x1F ;                     // PULL UP pins PF1,2,3,4
  GPIO_PORTF_AFSEL_R = 0x1F;                     // disable alt funct on PF1,2,3,4
  GPIO_PORTF_DEN_R |= 0x1F;                      // enable digital I/O on PF1,2,3,4
  GPIO_PORTF_PCTL_R &= ~0xfffff;                 // configure PORT F, PF1,2,3,4 as GPIO
  GPIO_PORTF_AMSEL_R &= ~0xFF;                   // disable analog functionality on PORT F
  
  GPIO_PORTF_IS_R |= 0x1f;                       // PF1,2,3,4 are NOT edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x1f;                     // are not both edges
  GPIO_PORTF_IEV_R |= 0x1f;                      // PF1,2,3,4 HIGH LEVEL event
  
  //NOTE : This keypad uses HIGH level event to make it work like a real keyboard;
  //in case of a long press, the character is printed MANY TIMES. 
  
  GPIO_PORTF_ICR_R = 0x1f;                       // clear flags PF1,2,3,4
  GPIO_PORTF_IM_R |= 0x1f;                       // arm interrupt on PF1,2,3,4
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;   // priority 5
  NVIC_EN0_R = 0x40000000;                       // enable interrupt 30 in NVIC

  __asm("CPSIE  I");                             // Enable interrupts to the processor.
}






char Output (void)
{
  GPIO_PORTF_ICR_R = 0x1E;//1E      // acknowledge flags 4,3,2,1

  GPIO_PORTF_DATA_R=0x00;      //Erasing Data in PORT , to allow NEW BUTTON TO BE PRESSED
  GPIO_PORTE_DATA_R = 0x00;  
  char n;
  
  //JUST ONE SCAN PER INTERRUPT TO KNOW PRESSED BUTTON !!
  char Numbers[4][4] = { {'1', '2', '3', '+'},
                         {'4', '5', '6', '-'},
                         {'7', '8', '9', 'x'},
                         {'*', '0', '=', '/'} };


 
   for (int i=3; i>=0; i--)                 //sends ONES to the 4 Columns; PINS 0, 1, 2, 3 //SPECIFIES the COLUMN in which a BUTTON is PRESSED 
     {
       GPIO_PORTE_DATA_R = (1U<<i);
      
       for (int y=4; y>=1; y--)            //PINS 4, 5, 6, 7    //SPECIFIES the ROW in which a BUTTON is PRESSED
       {    
         if( (GPIO_PORTF_DATA_R & (1U<<(y))) )   // a BUTTON IS PRESSED in a ROW
          {   
            
            n = (Numbers[4-y][3-i]); 
            //printf("%c \n", n);  
          }            
       }     
     }
  
   
   GPIO_PORTE_DATA_R=0x0F;  //REsends 1s to pins PE 0,1,2,3 TO DETECT NEXT INTERRUPT
   
   delayMs (100);   //DEBOUNCING
 return n;   
}

/*
int main(void)
{ 
   PORTF_Init();  
   PORTE_Init(); 
   
   while(1)
   {   
     // Processor enters Sleep Mode to save Power instead of Looping
     // Once Interrupt happens, Processor goes directly into Run mode     
      __asm("      wfi\n");    
   }
} 
*/