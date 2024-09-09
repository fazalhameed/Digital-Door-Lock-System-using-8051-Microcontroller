# include <reg52.h>
# include "LCD.h"
# include "Keypad.h"
sbit C1=P1^3;
sbit C2=P1^2;
sbit C3=P1^1;
sbit C4=P1^0;                                                              
sbit R1=P1^7;
sbit R2=P1^6;
sbit R3=P1^5;
sbit R4=P1^4;

unsigned char counter=0;

void Beep(unsigned int duration)         
{
    unsigned char i,j,k;
	
	//To convert passive Buzzer into Active Buzzer we Generate Crystal frequency through coding.
	for(k=1;k<=duration;k++)    
  { 
		for(i=0;i<250;i++)            
	{
	  R3=0;
	  for(j=0;j<50;j++);
		R3=1;
    for(j=0;j<50;j++);

  }Delay(500);
  }
}

char Key_Pressed ()                 //detect  pressed button 
{  
  while(1)     
	{
	R1=0; R2=1; R3=1; R4=1;           
	     if(C1==0)                                        
			 {  Delay(100);
				 while(C1==0)
				   { Beep(1);  return '7';}
			     
			 }  
	      
			 if(C2==0)                                      
			 {     Delay(100);
    				 while(C2==0)
			       { Beep(1);return '8';}  
			 }       
			  
			 if(C3==0)
			 {   Delay(100); while(C3==0)
			    { Beep(1);return '9';}  
			 }
			 
			 if(C4==0)
			 {    Delay(100);
			    while(C4==0)
			    { Beep(1);return '/';} 
			 
			 }
	 
  R1=1; R2=0; R3=1; R4=1;                           
	     if(C1==0)                                    
			 {   Delay(100);
           while(C1==0)
			    { Beep(1);
					return '4';} 


			 } 
			
	      if(C2==0)
			 {  Delay(100);
           while(C2==0)
			    { Beep(1);
					return '5';} 
			 }
			  if(C3==0)
			 {  Delay(100);
         while(C3==0)
			    { Beep(1);
					return '6';} 

			 }
			  if(C4==0)
			 {  Delay(100);
				 while(C4==0)
			    { Beep(1);return '*';}   }
			 
  R1=1; R2=1; R3=0; R4=1;                               // Row 3,and check coloum
	     if(C1==0)
			 {  Delay(100);
         while(C1==0)
			    { Beep(1);return '1';} 

			 } 
	      if(C2==0)
			 {  Delay(100);
				 while(C2==0)
			    { Beep(1);return '2';} 
			 }
			  if(C3==0)
			 {  Delay(100);
				 while(C3==0)
			    { Beep(1);return '3';}   
			 }
			  if(C4==0)
			 {  Delay(100);
				 while(C4==0)
			    { Beep(1);return '-';}   }
			 
			 
	R1=1; R2=1; R3=1; R4=0;                               // Row 4,and check coloum
	     if(C1==0)
			 {   Delay(100);
				 while (C1 == 0 && counter<10) 
				 { Beep(1);  
             counter++;  Timmer_Delay(160);
				 }
				 if(counter>=10)
						{return 'c';}
					else
						{return 'C';}
			 } 
			 
			 
	      if(C2==0)
			 {  
				 Delay(100);
				 while(C2==0)
			    { Beep(1);return '0';}  
			 
		   }  
			  if(C3==0)
			 {  Delay(100);
				  while(C3==0)
			    { Beep(1);return '=';}  
			 }
			  if(C4==0)
			 {   Delay(100);
				   while(C4==0)
			    { Beep(1);return '+';} 
			 }
	 
	 R4=1;
			 
		 }	 
}





