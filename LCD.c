# include <reg52.h>
# include "LCD.h"
# include "Keypad.h"
#define LCD_DATAPORT P0

sbit RW=P2^5;                                    
sbit RS=P2^6;                                    
sbit EN=P2^7;                                   
sbit DB4=P0^4;                               
sbit DB5=P0^5;
sbit DB6=P0^6;
sbit DB7=P0^7;

void Delay (unsigned int value)        
{
 unsigned int j;
	   
	for (j=0; j<value ;j++)
	{  
		
		TH0=0xFC;
		TL0=0x64;
		TF0=0;
		TR0=1;
		while(TF0==0);
		TF0=0;
		TR0=0;
	}
}

void Timmer_Delay (unsigned char k )       
{
 unsigned int j;
	   
	for (j=0; j<k ;j++)
	{  
		
		TH1=0x4B;
		TL1=0xFD;
		TF1=0;
		TR1=1;
		while(TF1==0);
		TF1=0;
		TR1=0;
	}
}


//LCD Write Function

void LCD4_write ( unsigned char Value)
  {  
		//In this Case Byte are divide into two Nibbles,First low nibble is passed and then Highly Nibble is transfred
		//Nibble are Anded(Gate) with pins with below mentioned Value(By making each pin High) One by one
		
		DB4=0x10 & Value;            //Value (Command Or Data are and with 0x10) first Pin          
		DB5=0x20 & Value;            //Value (Command Or Data are and with 0x20) second Pin  
		DB6=0x40 & Value;            //Value (Command Or Data are and with 0x40) Third Pin  
		DB7=0x80 & Value;            //Value (Command Or Data are and with 0x80) Fourth Pin  
		              
		EN=1;
	  Delay(4);                   
	  EN=0;                      
	 
	}
	

	
// LCD Command Function
void LCD_Command (unsigned char cmd)
{ 
	RS=0;                           
	RW=0;                          
	LCD4_write(cmd & 0xF0);         
	LCD4_write( cmd <<4 );         
}


// LCD Data Function
void LCD_Data (unsigned char Data)
{ 
	RS=1;                          
	RW=0;                         
	LCD4_write ( Data & 0xF0);
	LCD4_write (Data <<4 );
	
}


// Intilization OF LCD
void LCD_Intialization(void)
{  
	                                         
	 Delay(100);
    LCD_Command(0x02);  //initilize the LCD in 4bit Mode
   LCD_Command(0x28);
   LCD_Command(0x0C); 
   LCD_Command(0x01);  
   LCD_Command(0x80); 
}


// Set Cursor function (Enter the coloum ond Row, the Cursor position is on that point)

 void Set_cursor(int row, int coloum)
 {      
	 if(row==1)                                         
	    { 	LCD_Command(0x80+coloum); }                  
			else if(row==2)                                  
	    { 	LCD_Command(0xC0+coloum); }                
 
 
 }


 
//LCD Erasing
 
void LCD_Clear()
 { 
      LCD_Command(0x01);
 }
 int lcd_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

//Set Cursor, Passing Number and its Length,
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	Set_cursor(Line,Column);                    
	for(i=Length;i>0;i--)                        
	{
		LCD_Data(Number/lcd_Pow(10,i-1)%10+'0');   
	}
}

void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	Set_cursor(Line,Column);
	LCD_Data(Char);
}

void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	Set_cursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_Data(String[i]);
	}
}

