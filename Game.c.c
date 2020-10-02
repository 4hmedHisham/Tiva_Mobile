
// this is a file full of Mobile Games
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <stdint.h>

static int input;
int Space[16][2];
static int NegSpeed;
static int GameOver=0;


struct d2
{
  char x;
  char y;
};
struct d2 food;
struct d2 p1;
//struct d2 p[32];
void timer0int(){
 SYSCTL_RCGCTIMER_R |= 0x01;   
 TIMER0_CTL_R = 0x00000000; 
 TIMER0_CFG_R = 0x00000000;
 TIMER0_TAMR_R = 0x00000002; 
 TIMER0_TAILR_R = 0x7A1200;  
 TIMER0_TAPR_R = 0; 
 TIMER0_ICR_R = 0x00000001;  
 TIMER0_IMR_R = 0x00000001;
 NVIC_EN0_R = 1<<19;    
 TIMER0_CTL_R = 0x00000003;
}
void Timer0IntHandler (){
TIMER0_ICR_R = 1;
}
void startup()
{
  for(int j=0;j<2;j++)
  {
    for(int i=0;i<16;i++)
    {
     Space[i][j]=' '; 
    }
  }
  Space[0][0]='.';

}
void clean()
{
  for(int j=0;j<2;j++)
  {
    for(int i=0;i<16;i++)
    {
     Space[i][j]=' '; 
    }
  }
}

void display()
{
  printf("-------------------------\n");
  for(int j=0;j<2;j++)
  {
    for(int i=0;i<16;i++)
    {
     printf("%c",Space[i][j]);
    }
    printf("\n");
  }
  printf("-------------------------");
   printf("\n");
  
}

int Arrow(char Mov)
{
  int GameOver;
  if(Mov=='8')
  {
    p1.y=1;
  }
  else if(Mov=='2')
  {
    p1.y=0;
  }
  
   if(food.x>0)
  {
  food.x--;
  }
  else 
  {
  food.x=15;
  }
  if(food.y==0)
  {
    food.y=1;
  }
  else if(food.y==1)
  {
    food.y=0;
  }
  
  
  if(p1.x==food.x)
  {
    if(p1.y==food.y)
    {
      GameOver=1;
    }
    if(GameOver==1)
    {
     return 1; 
    }
  }
clean();
Space[0][p1.y]='>';
Space[food.x][food.y]=174;
 return 0;
}
void changeInput(char x)
{
  if((x=='8')||(x=='2'))
  input=x;
}
char startgame()
{
  
  NegSpeed=500;
clean();
p1.x=0;
p1.y=0;
Space[0][0]='>';
food.x=14;
food.y=0;
GameOver=0;

//Space[6][0]='A';

    while(1)
  {
  if(GameOver!=1)
  {
  
  
  GameOver=Arrow(input);
  display();
  if(GameOver==1)
  {
    printf("GameOVER\n");
    return 0;
  }
  delay(NegSpeed);
  NegSpeed--;
  
  }
  
  }

}

  