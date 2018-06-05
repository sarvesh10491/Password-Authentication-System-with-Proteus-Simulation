//LCD bits
#define dataport P2
sbit rs=P3^0;
sbit rw=P3^1;
sbit en=P3^2;

void lcd_init(void);
void cmdwrite(unsigned char cmddata);  
void datawrite(unsigned char opdata); 
void lcd_strwrite(unsigned char *str);
void lcd_charwrite(unsigned char ch);
void lcd_clear(void);
void lcd_goto(unsigned int pos,unsigned int line);
void MSDelay(unsigned int);

code unsigned char cmdbyte[5]={0x38,0x0e,0x01,0x06,0x80};
unsigned int i,j;

//LCD initialization function
void lcd_init()
{
for(i=0;i<5;i++)
{
cmdwrite(cmdbyte[i]);
MSDelay(100);
}
}

//Function to send command to LCD
void cmdwrite(unsigned char cmddata)
{
dataport=cmddata;
rs=0;
rw=0;
en=1;
MSDelay(1);
en=0;
MSDelay(1);
}

//Function to send data to LCD
void datawrite(unsigned char opdata)
{
dataport=opdata;
rs=1;
rw=0;
en=1;
MSDelay(1);
en=0;
MSDelay(1);
}

//Function to write string to LCD
void lcd_strwrite(unsigned char *str)
{
 unsigned char len;
 len = strlen(str);               
 for(i=0;i<len;i++)
 {
  datawrite(*str);              
  str++;  
 }
}

//Function to write character to LCD
void lcd_charwrite(unsigned char ch)
{
  datawrite(ch);              
}

//Function to clear LCD
void lcd_clear()
{
cmdwrite(0x01);
MSDelay(1);
}

//Function to select starting matrix in LCD
void lcd_goto(unsigned int pos,unsigned int line)
{
if(line==1)
{
cmdwrite(0x80+pos);
MSDelay(1);
}
else
{
cmdwrite(0xC0+pos);
MSDelay(1);
}
}

//ms delay function
void MSDelay(unsigned int itime)
{
unsigned int it,jt;
for (it=0;it<itime;it++)
for (jt=0;jt<1275;jt++);
}