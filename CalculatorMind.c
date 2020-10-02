
#include "CalculatorMind.h"
#include "LCD.h"
 static int flag = 0;

unsigned char   Aresult[8];
void clearArray(char*p)
{
  for(int i=0;i<8;i++)
  {

    
    
  }
}

 unsigned char * GimmeDataGiveUResult(unsigned char singledigit)
{
 
    
static int Numbers1=0;//first set of numbers
static int Numbers2=0;//second set of numbers
static char Num1or2=0;//Writing in the first or second set of numebrs a+b for ex a is nums1 b is nums2
static int operation=0;//+ - * /   1 2 3 4
static int result=0;
  if(((singledigit>='0')&&(singledigit<='9'))&&(!Num1or2))//num1
  {
    Numbers1=Numbers1*10+(singledigit-48);
  }
  else if(singledigit=='+')
  {
    operation=1;
    Num1or2=1;
  }
 else  if(singledigit=='-')
  {
    operation=2;
    Num1or2=1;
  }
  else if(singledigit=='x')
  {
    operation=3;
    Num1or2=1;
  }
 else  if(singledigit=='/')
  {
    operation=4;
    Num1or2=1;
  }
 
  else if(((singledigit>='0')&&(singledigit<='9'))&&(Num1or2))//num2
    
  {
     Numbers2=Numbers2*10+(singledigit-48);
  }
   else if(singledigit=='=')
  {
      Num1or2=0;
      Aresult[0]='\0';
      switch(operation)
      {
      case 0 :
       result= Numbers1;
       Numbers1=0;
       Numbers2=0;
         break;
         
      case 1 :
      operation=0;//Resets Operation
       result= Numbers1+Numbers2;
        Numbers1=0;//ResetNums1
       Numbers2=0;//ResetNums2
         break;
      case 2 :
        operation=0;
       result=Numbers1-Numbers2;
        Numbers1=0;
       Numbers2=0;
         break;
      case 3 :
        operation=0;
        result= Numbers1*Numbers2;
         Numbers1=0;
       Numbers2=0;
         break;
      case 4 :
        operation=0;
        result= Numbers1/Numbers2;
         Numbers1=0;
       Numbers2=0;
         break;
      }
       int i=0;
      
  for(i=0;result!=0;i++)
  { 
  Aresult[i]=(result%10+48);//cause i wanna send back characters
  
  result=result/10;
  }
  Aresult[i]='=';
  Aresult[++i]='\0';
  for(int j=0;j<(i)/2;j++)
  {
    int temp=Aresult[i-j-1];
    Aresult[i-j-1]=Aresult[j];
    Aresult[j]=temp;

  }
  flag = 1;
  return Aresult;//bear with me 
  }
  else{
    //result= 0; //9000 means a wrong input
     //Numbers1=0;
    //   Numbers2=0;
         
    
  }
 
  
}