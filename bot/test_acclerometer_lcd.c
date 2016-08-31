#include<avr/io.h>
#include<util/delay.h>
#include<xslcd.h>
#include <avr/interrupt.h>

/*void InitLCD();
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,unsigned int field_length);
void LCDGotoXY(uint8_t x,uint8_t y);
void LCDWriteStringXY(x,y,msg) 
void LCDWriteIntXY(x,y,val,fl) */

int main(void)
{ 
 int x,y;
 DDRA = 0x00;
 PORTA = 0x00;
 
 InitLCD();
 ADCSRA = 0x85;
 LCDClear();
 LCDWriteString("x = ");
 LCDWriteStringXY(0,1,"y = ");
 while(1)
 {
  ADMUX = 0x60;
  ADCSRA = 0xC5;
  while((ADCSRA & 0x40)!= 0x00);
  _delay_ms(10);
  x = ADCH;
  ADMUX = 0x61;
  ADCSRA = 0xC5;
  while((ADCSRA & 0x40)!= 0x00);
  _delay_ms(10);
  y = ADCH;
  
  LCDWriteIntXY(4,0,x,3);
  LCDWriteIntXY(4,1,y,3);
 }
 return 0;
}
