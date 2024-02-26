#ifndef EEPROM_H__
#define EEPROM_H__


void NO_aknowledge();
void aknowledge();
void Delay_ms(unsigned int x);          
void Restart();           
void Start_Data();          
void Stop_Data();
void SendByte (unsigned int Value);
unsigned char ReadByte ();
void EEPROM_Write (unsigned char address_W ,unsigned char Data);
unsigned char EEPROM_Read (unsigned char address_R);



#endif