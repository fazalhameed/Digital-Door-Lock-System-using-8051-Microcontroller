# include <reg52.h>
# include "EEPROM.h"
# include <intrins.h>
# include "LCD.h"
# include "Keypad.h"
sbit SDA= P2^0;
sbit SCL= P2^1;

unsigned char a,b,Data;
bit ack;
void Delay_ms(unsigned int x)       
{	   
	unsigned int y,z;
		for(y=0;y<=x;y++)
	    	for(z=0;z<=113;z++);
}
void Start_Data ()              
{ 
	SDA=1;                          
  _nop_();_nop_();
  SCL=1;
  _nop_();_nop_();
	SDA=0;
  _nop_();_nop_();	
}
void Restart ()                         
{
	SCL=0;
	SDA=1;
	SCL=1;
	SDA=0;
}
void Stop_Data ()                       
{ 
  SCL=0;                                  
	SDA=0;
  SCL=1;
	SDA=1;	
}

void aknowledge()	                   
{
	SCL=0;                        
	SDA=1;
	SCL=1;
	while(SDA);
}
void NO_aknowledge()	             
{
	SCL=0;
	SDA=1;
	SCL=1;
}
void SendByte (unsigned int Value)             
{  
	 for(a=0;a<8;a++)
	{ 	
	  SCL=0;
    SDA=(Value&(0x80>>a))?1:0;                  //Send the MSB first
    SCL=1;
	}	
}

unsigned char ReadByte ()                  
{  
      Data=0;
	for(b=0;b<8;b++)
	{	 
   SCL=0;
   SCL=1;
   if(SDA)
    Data|=(0x80>>b);	                        //Send the MSB first	
	}	  
	 return Data;
}

void EEPROM_Write (unsigned char address_W ,unsigned char Data)    // EEPROM Write Function
{
  Start_Data ();               //Intialize Data Transfer 
  SendByte(0xA0);              // A0=A1=A2=0 Control Byte
	aknowledge();                //Acknowledge
	SendByte(address_W);         // Send Adress of EEPROM location
	aknowledge();                //Acknowledge
  SendByte(Data);              //Send Byte of data
	aknowledge();                //Acknowledge
	Stop_Data () ;               //Stop Data Transfer
	Delay_ms(10);                 // Small Delay
}

unsigned char EEPROM_Read (unsigned char address_R)                 // EEPROM Read fdunction
{  
	unsigned char Data;
  Start_Data ();                                    
	SendByte(0xA0);                       //Send Write Control Byte to write the Address
	aknowledge();                        
  SendByte(address_R);                  //Send the Data from where Data read
	aknowledge();                        
  Restart();                            //Re-intialize data Transfer in Order To read Data 
	SendByte(0xA1);                       //Send Control Byte To Read data 
	aknowledge();                         
  Data= ReadByte ();                    //Pick the Data from EEPROm Register and Store in Temporarry Registers
	NO_aknowledge();                      
	Stop_Data ();                         //Stop Data Transfer   
	
return Data;                            //Return the data stored in Temporary Register
}


