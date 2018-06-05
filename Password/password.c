#include <reg52.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <lcd.h>

//Keypad bits
sbit C1=P1^0;
sbit C2=P1^1;
sbit C3=P1^2;
sbit R1=P1^3;
sbit R2=P1^4;
sbit R3=P1^5;
sbit R4=P1^6;

sbit subbit=P1^7;	  //Input

char read_keypad();

unsigned char keydata;
unsigned int var,ib,jb;
unsigned char count;
unsigned char passdata[16];
unsigned char password[16]={"123#"};	 //Password

void main(void)
{
lcd_init();
MSDelay(1);
subbit=1;  //Input

while(1)
{
  count='3';  //Attempts

  loop:
  for(jb=0;jb<16;jb++)
  {
  passdata[jb]=0;
  }
  var=1;
  ib=0;
  lcd_init();
  MSDelay(1);
  lcd_strwrite("Enter Password");
  lcd_goto(0,2);
  while(1)
  {
      while((!(keydata = read_keypad()))&&(var=subbit));	//wait for key press

	  if(var==0)	   //post submit check
	  {
	   lcd_clear();
	   lcd_goto(0,1);
	   for(jb=0;jb<16;jb++)
       {
	    if(passdata[jb]!=password[jb])
		{
		 count--;
		 if(count=='0')
		 {
		  lcd_clear();
		  lcd_goto(0,1);
		  lcd_strwrite("Unauthorized");
		  lcd_goto(0,2);
		  lcd_strwrite("Access");
		  while(1);
		 }
		 lcd_strwrite("Wrong Password");
		 lcd_goto(0,2);
		 lcd_strwrite("Attempts left:");
		 lcd_goto(15,2);
		 lcd_charwrite(count);
		 goto loop;
		}       
       }
	   lcd_strwrite("Correct Password");
	   while(1);
	  }

	  passdata[ib]=keydata;	    //Storing valid data
	  ib++;
      lcd_charwrite('*');
      MSDelay(10);
  }
}
}

//Function to scan keypad
char read_keypad()
{
  C1=1;
  C2=1;
  C3=1;

  R1=0;
  R2=1;
  R3=1;
  R4=1;
  if(C1==0){MSDelay(100);while(C1==0);return '1';}
  if(C2==0){MSDelay(100);while(C2==0);return '2';}
  if(C3==0){MSDelay(100);while(C3==0);return '3';}

  R1=1;
  R2=0;
  R3=1;
  R4=1;
  if(C1==0){MSDelay(100);while(C1==0);return '4';}
  if(C2==0){MSDelay(100);while(C2==0);return '5';}
  if(C3==0){MSDelay(100);while(C3==0);return '6';}

  R1=1;
  R2=1;
  R3=0;
  R4=1;
  if(C1==0){MSDelay(100);while(C1==0);return '7';}
  if(C2==0){MSDelay(100);while(C2==0);return '8';}
  if(C3==0){MSDelay(100);while(C3==0);return '9';}

  R1=1;
  R2=1;
  R3=1;
  R4=0;
  if(C1==0){MSDelay(100);while(C1==0);return '*';}
  if(C2==0){MSDelay(100);while(C2==0);return '0';}
  if(C3==0){MSDelay(100);while(C3==0);return '#';}

  return 0;
}