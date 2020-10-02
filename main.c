#include "Setup.h"
#include "CalculatorMind.h"
#include "Lcd.h"
#include "keypad.h"
#include "Game.h"
#include "ContactList.h"
#include "rtc.h"

struct real_time RTC;
void CalculatorMode();
char RTCMode();
void playing();
int AddContact(char ,char );
void ViewContacts(char );
void viewmenu(char );
char In;//input
 
int counter=0 ;
int hours=0;
int minutes=0;
int seconds=0;
int settingTime=0;

void FirstRTCMode()
{
 Lcd_SendString("Press 1 to ShowTime and 2 to adustime\n");    
}

//FE HENA print m3rft4 eh lazmtha
char RTCTimeAdjust(char digit)
{
  if((In>='0')&&(In<='9'))
  {
   if (counter<2)
    {
      printf("%c ",In);
      hours=In-48+hours*10;
      counter++;
    }
   else if (counter<4)
   {
     printf("%c ",In);
     minutes=In-48+minutes*10;
     counter++;
   }
   else if (counter<6)
   {
     printf("%c ",In);
     seconds=seconds*10+In-48;
     counter++;
   }
   if(counter==6)
   {
     
     rtc_input(hours,minutes,seconds);
     counter=0;
     settingTime=0;
     hours=0;
     minutes=0;
     seconds=0;
   }
  }     
}

// hena kan feh /n enter time /n so i guessed it was printed in line2
// fe bardo 7eta httb3t send char bs me4 faye2 el sara7a xD
char RTCMode(In)
{
   if((In>='0')&&(In<='9'))
  {
  if(settingTime==1)
  {
    RTCTimeAdjust(In) ;
  }
  else if(In=='1')
  {
    
    printf("%d : ",RTC.hours);
    printf("%d : ",RTC.minutes);
    printf("%d \n ",RTC.seconds);
  }
 
  else if(In=='2')
  {
   settingTime=1;
   Lcd_SendSecondString("Enter Time :");
  }
  }
  
}

char NameIn=0;//bool to enter name
char Name=0;//adds name here
char ContactDone=0;
char firsttimein=1;
 
char StartGame=0;//starts the game and leaves sleep mode;
int Layer=0;//defines if im in a sub menu or a main menu
char menu [6][16]={"menu","Calculator","Game","Time","AddContact","ViewContact"};//array that have the meny
 
void CalulatorInit()
{
   Lcd_SendString("Enter The Numbers and Operation :");
 } 
void StartAddContact()
{
  Lcd_SendString("Enter The Name U want to add\n");
  
}
//fe hena prints bardo me4 fahmha
void AddContactP()
{
  if((In<='9'&&In>='0')||(In=='+')||(In=='-')||(In=='*')||(In=='/'))
  {
  if(ContactDone==1)
  {
    ContactDone=0;
    NameIn==0;
    firsttimein=1;
    
  }
  else{ printf("%c",In);
  if(NameIn==0)
  {
    Name=In;
    NameIn++;
    printf("Enter Number : \n");
     
  }
  else{
    if(firsttimein==1)
    {
      firsttimein=0;
       
    
    }
  ContactDone=AddContact( Name,In);
  }
  }
  }
}

int menunumber=0; //where im in the menu
int counterSwtich=0;// this is what will sweep the screen
int currentscene=0;//this number is the current 2 slectives in scene

void resetLayer0()
{
 counterSwtich=0;
 currentscene=0;
 menunumber=0;
}
void addingCurrentCursor(int cursor)
{ 
}
void viewmenu(char Move)//this function moves and displays the main menu
{
  if(Move=='8')
  {
    if(menunumber<5)
    {
    menunumber++;
    counterSwtich++;
    }
  }
  if(Move=='2')
  {
    if(menunumber>0)
    {
      menunumber--;
      counterSwtich--;
    }
  }
  if(counterSwtich==2)
  {
   
    counterSwtich=0;
    currentscene+=2;
    
  
    
  }
  if(counterSwtich<0)
  {
    counterSwtich=1;
    currentscene-=2;
  }
 for (int i=currentscene;i<(currentscene+2);i++)
 {
   for(int j=0;menu[i][j]!='\0';j++)
   {
     printf("%c",menu[i][j]);
     
   }
   if(i==menunumber)
   {
     printf("<");
   }
   printf("\n");
   
 }

  
}
//hena bardo prints m4 la2etha
void CalculatorMode()//this function activates the calculator
{
  char *y;
 
 //In=Output();
    
   
    if(In=='=')
    {y=GimmeDataGiveUResult(In);
    //WriteNum(y);
    
    for(int i=0;y[i]!=0;i++)
    {
     printf("%c",*(y+i)); 
    }
    printf("\n");
    }
    else if(In=='#')
    {
      
      LCDClear();
      printf("\n");
      
    }
    else
    {
      //WriteC(In);
      printf("%c",In);
      GimmeDataGiveUResult(In);
    } 
  
}
void GPIOPortF_Handler(void)//this function moves the whole project based in interrupts
{  
 In=Output();
 if(Layer==1)//layer1 is the subprogram wether it is the game, the clock or anything else
 {
   if(In=='*')//press *gets us back to layer 0
   {
     Layer=0;
   }
   else{
   switch(menunumber)
     {
     case 1:
       CalculatorMode();
       break;
     case 2:
       changeInput(In);//this controls the player inside the game
       break;
     case 3:
       RTCMode(In);
       break;
     case 4:
       AddContactP();
       break;
     case 5:
       ViewContacts(In);
       break;
   
 }
 
   }
 }
 if(Layer==0)//checks where im in the program
 {
  
   if((In=='8')||(In=='2'))
   {
   viewmenu(In);//choosing menu
   }
   if(In=='5')//when i press 5 i enter a submenu
   {
     //resetLayer0();//reset the variables for layer 0
     Layer=1;
     switch(menunumber)
     {
     case 1:
      // CalculatorMode();
       CalulatorInit();
       break;
     case 2:
       StartGame=1;
       break;
     case 3:
       FirstRTCMode();
       break;
     case 4:
       StartAddContact();
       break;
     case 5:
       ViewContacts(In);
       break;
     }
     
   }
   else if (In=='*'){ viewmenu(0);}
   
  }      
 
  }
 
int main(void)
{ 
   PORTF_Init();  
   PORTE_Init(); 
   eeprominit();
   rtctimer1_init(); 
   viewmenu('0');

   RTC.seconds = 0;
   RTC.minutes = 0;
   RTC.hours   = 0;
   
   while(1);
}