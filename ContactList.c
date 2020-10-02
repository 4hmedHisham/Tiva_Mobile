#include "ContactList.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_gpio.h"
#include "driverlib/eeprom.h"
#include "ContactList.h"
#include "tm4c123gh6pm.h"


 static int NumberMost=0;
 //static int NumberRest=0;


int AddContact(char Name, char digit)//we must have an intial value at first time  for the counter=0
{
  int counter=0;
  EEPROMRead(&counter, 0x00, sizeof(counter));
     static int ShallIPASS=0;
   //static int NumberMost=0;
//  static int NumberRest=0;
  static int NumCounter=0; //counts digits
   if(((digit>='0')&&(digit<='9')))//Reads Number from 0 to 9 and put it in number
  {
    if(NumCounter<9)
    {
    NumberMost=NumberMost*10+(digit-48);
    NumCounter++;
    }
   // else
    //{
    //  NumberRest=NumberRest*10+(digit-48);
    //  counter++;
  //  }
    if( NumCounter==4)
    {
      NumCounter=0;
      ShallIPASS= 1;// means i got the whole phone number
   
      
    }
 
  } 

  
if(ShallIPASS)
  {
    ShallIPASS=0;
uint32_t Count[1];
uint32_t WriteNum[2];
uint32_t Read[2];


WriteNum[0]=NumberMost;
WriteNum[1]=Name;
//---------------
EEPROMProgram(WriteNum, (4+(counter*8)), sizeof(WriteNum));

//-------------
int testread2[2];
EEPROMRead(testread2, (4+(counter*8)), sizeof(testread2));
//-----------------
//WriteNum[counter+1]=Number[1];
counter++;;
Count[0]=counter;
EEPROMProgram(Count, 0x00, sizeof(Count));

//*--------------
int testread[1];
EEPROMRead(testread, 0x00, sizeof(testread));


NumberMost=0;
Name=0;
return 1;

  }
}


void ViewContacts(char Move)
{
    
  static int CurrentContact=0;
  static int currentscene=0;

  static int counterSwitch=0;
  int ContactSize=0;
  EEPROMRead(&ContactSize, 0x00, sizeof(ContactSize));
  
  

  if(Move=='8')
  {
    if(CurrentContact<ContactSize)
    CurrentContact++;
    counterSwitch++;
    
  }
   if(Move=='2')
  {
    if(CurrentContact>0)
    {
    CurrentContact--;
    counterSwitch--;
    }
  }
    if(counterSwitch==2)
  {
   
    counterSwitch=0;
    currentscene+=2;
    
  
    
  }
   if(counterSwitch<0)
  {
   
    counterSwitch=1;
    currentscene-=2;
  }
  int NowContact[2];
  EEPROMRead(NowContact, 4+(8*CurrentContact), sizeof(NowContact));
 
   printf("Number is :");   
   printf("%d",NowContact[0]);
   printf("\n");
   printf("Name Is :");
   printf("%c ",NowContact[1]);
   printf("\n");

   
   
  


  
}
void readall()
{
  int pui32Read2[200];
  EEPROMRead(pui32Read2,0, sizeof(pui32Read2));
  int y;
}
void eeprominit()
{

  
uint32_t ui32EEPROMInit;

SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
{
}

ui32EEPROMInit = EEPROMInit();
if(ui32EEPROMInit != EEPROM_INIT_OK)
{
  while(1)
  {
  }
}
}

void clearContacts()
{
  int testread2[200];
  for(int i=0;i<200;i++)
{
  testread2[i]=0;
}
  
  EEPROMProgram(testread2, 0x0, sizeof(testread2));
}