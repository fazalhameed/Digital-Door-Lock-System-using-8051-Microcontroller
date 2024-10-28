# include <reg52.h>
# include "LCD.h"
# include "Keypad.h"
# include "EEPROM.h"

#define Generate_Password 0
#define Enter_Password 1
#define Wrong_Password 2
#define New_Password 3

unsigned char Gent_password[6];
unsigned char i=0,Value,j=0;
unsigned char Password[6];
unsigned char EEPROM[6];
unsigned char EEPROM_Pass;
unsigned char User_Password[6];
unsigned char EEPROM_Password,User_pin;
unsigned char second=10,Flag=0,data_read,flag1=0;
unsigned char  OLD_Password[6];
unsigned char old_PIN,key ;

unsigned int  ON_Period, OFF_Period;
sbit Servomotor_Pin = P2^0;

//Servo Motor Setup
void Timer0_Intilization ()     
{
  TMOD =0x01;
  TH0=0xB7;
  TL0=0xFD;
  IE=0x82;
  TR0=1;
	
}

void Timer0 () interrupt 1       
{ 
  Servomotor_Pin = ~Servomotor_Pin ;	
  if(Servomotor_Pin)
  {
   TH0=ON_Period >> 8;
   TL0=ON_Period;
    }
     else
     {
	TH0=OFF_Period >> 8;
        TL0=OFF_Period;
	}
}
void Set_Duty_Cycle (float angle)            
{ 
	float duty_cycle ;
	unsigned int Period;
	duty_cycle = (angle / 180.0) * 10.0 ; 
        Period =65535 - 0xB7FD ;
	ON_Period =((Period/100.0)*duty_cycle);
	OFF_Period = Period -ON_Period;
	ON_Period =  65535-ON_Period;
	OFF_Period=  65535-OFF_Period;

}
void RandomPassword ()                        
{ 		
	Gent_password[j]= Key_Pressed ();          
	EEPROM_Write(j,Gent_password[j]);                 
	LCD_ShowChar( 2,j,Gent_password[j]);	      
}

void main (void)                              
{  
  	  unsigned char current_state;    
	  LCD_Intialization();                       
	  Timer0_Intilization ();                     
          current_state = Generate_Password;       
	
 // Intially set servo motor to 0 degree
while(1)                                     
  {
    switch (current_state)                        //State Machine
		{
		case  Generate_Password :                 
		Value=EEPROM_Read (0xAA);                   
                                                   
		if(Value==0xAA)                            
		{  
		LCD_ShowString(1,0,"Generate Pin") ;
		if(j<6)                                 
		 { RandomPassword (); j++; }              
		 else
		  {   EEPROM_Write (207,0xAA);           
		      current_state = Enter_Password;    
		      Timmer_Delay(3000);                
		}
	 }
		 else                                       
		{
		current_state = Enter_Password;          //State Change to Enter password state
		 }
			
	         break;
				
         case  Enter_Password :                               //Case 02 Enter Password State			 
	  LCD_Clear();                                     
	  data_read= EEPROM_Read (254);                  //EEPROM memory 254 read in order to check the number of Wrong input
		 
          if(data_read!=6)                                 
	 {     
		      for(i=0;i<6;i++)
		      {   
			  Password[i]=EEPROM_Read (i);              
			}
			  //Extract password
			EEPROM_Password=(Password[5]*100000)+(Password[4]*10000)+(Password[3]*1000)+(Password[2]*100)+(Password[1]*10)+(Password[0]);
			
			LCD_ShowString(1,0,"Enter Password") ;
			//User Enter 6 Digit password
			for(i=0;i<6;i++)
		  {     key=Key_Pressed();          
				
				  if(key=='c')                 //if the Button is press for long time 10 second So it will change the state to New Password State 
				     { 
					current_state = New_Password; break;  
					 }
					 else 
					 {
					   User_Password[i]= key;}           
				       
				LCD_ShowChar( 2,i,User_Password[i]);
			}			
		  Delay(2000);
			
			//Extract User pin
			User_pin=(User_Password[5]*100000)+(User_Password[4]*10000)+(User_Password[3]*1000)+(User_Password[2]*100)+(User_Password[1]*10)+(User_Password[0]);
			
			if (current_state == New_Password)   
    {
      break;
    }
					
			if(EEPROM_Password==User_pin)      
			{ 
				LCD_Clear();                     
				LCD_ShowString(1,0,"Door Unlocked") ;   
				Beep(5);                         
				Delay(1000);
			    Set_Duty_Cycle(0.0);            
				Delay(500);
				for(i=0;i<10;i++)                 
			    { second--;
			      LCD_ShowNum(2,6,second,1) ;
			      Timmer_Delay(160);
					}								
			  Beep(5);                         
			  LCD_ShowString(1,0,"Door Locked");
													
			  Set_Duty_Cycle(180.0);            
				Delay(2000);		  				
		  	LCD_Clear();
        Flag=0;	                        
        second=10;                       					
			  current_state = Enter_Password;  
			}
	     else                                   
			  {current_state = Wrong_Password;}     
	}
		 
	else                            //if number of wrong password is more than 5  
	 {
	   LCD_ShowString(1,0,"System Disabled");      //System Disabled and Beep for long
	   Beep(5000);
	 }
		 
	 break;
			case  Wrong_Password  :                    //Case 03 Wrong password State
			
			if(Flag<5)                           
			{ 
				LCD_Clear();	
			        LCD_ShowString(1,0,"Wrong Password");   
				LCD_ShowNum(2,5,Flag,1);
				Beep(10); 
				Flag++;                            
				current_state = Enter_Password;    
			
			}
			else                             
			{
				EEPROM_Write(250,6);           
				LCD_Clear();
			        LCD_ShowString(1,0,"System Disabled");    
				Beep(5000);
			}
						 			
	       break;
				
				
      case  New_Password :                         //Case 03 Change Password State
	
      LCD_Clear();
      LCD_ShowString(1,0,"Enter Old Pin");      

       for(i=0;i<6;i++)          
		  {   
			  EEPROM[i]=EEPROM_Read (i);
			}
			//Extract the Password
			EEPROM_Pass=(EEPROM[5]*100000)+(EEPROM[4]*10000)+(EEPROM[3]*1000)+(EEPROM[2]*100)+(EEPROM[1]*10)+(EEPROM[0]);
			

			for(i=0;i<6;i++)     
		  { 
			  OLD_Password[i]=  Key_Pressed();    
				LCD_ShowChar( 2,i,OLD_Password[i]);
			}
			Delay(2000);
			//Extract paassword
			old_PIN=(OLD_Password[5]*100000)+(OLD_Password[4]*10000)+(OLD_Password[3]*1000)+(OLD_Password[2]*100)+(OLD_Password[1]*10)+(OLD_Password[0]);
    
			
			if(old_PIN==EEPROM_Pass)
		   	 {  
			   EEPROM_Write (212,0xFF);   //EEPROM Memory back chage to 0xFF 
                           LCD_Clear();	
			   current_state = Generate_Password;
		 break;  
			 }
			 else                 
			 {
				 
				 if(flag1<3)        
			      { 
			      	LCD_Clear();	
			        LCD_ShowString(1,0,"Wrong Password");      
			      	LCD_ShowNum(2,5,flag1,1);
			      	Beep(10); 
			      	flag1++;                                   
			      	current_state = New_Password;              
			
		        	}
		      	else             
			       {
			        EEPROM_Write(250,6);          
           			LCD_Clear();
			        LCD_ShowString(1,0,"System Disabled");      //Show Syatem disabled 
			        Beep(5000);
			       }
				 }
			
			
	       break;		 				
		}
	}
}


