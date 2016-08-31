#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<xslcd.h>

int readX(void);
int readY(void);
void USARTInit(uint16_t);
char USARTReadChar(void);
void USARTWriteChar(char);

int readX(void)
{
  ADMUX = 0x60;
  ADCSRA = 0xC5;
  while((ADCSRA & 0x40)!= 0x00);
  _delay_ms(10);
  return(ADCH);
}

int readY(void)
{
  ADMUX = 0x61;
  ADCSRA = 0xC5;
  while((ADCSRA & 0x40)!= 0x00);
  _delay_ms(10);
  return(ADCH);
}


void USARTInit(uint16_t ubrr_value)
{
 UBRRL = ubrr_value;
 UBRRH = (ubrr_value>>8);
 UCSRC=(1<<URSEL)|(3<<UCSZ0);
 UCSRB=(1<<RXEN)|(1<<TXEN);
}

char USARTReadChar()
{
 while(!(UCSRA & (1<<RXC)));
 return UDR;
}

void USARTWriteChar(char data)
{
 while(!(UCSRA & (1<<UDRE)));
 UDR=data;
}

int main(void)
{
 int x,y;
 unsigned int data;
 USARTInit(51);
 InitLCD();
 DDRB = 0xff;
 PORTB = 0x00;
 DDRA = 0x00;
 PORTA = 0x00;
 //ADCSRA = 0x8D;
 while(1)
 {
   data = USARTReadChar();
   LCDWriteIntXY(0,0,data,3);
  /*x = readX();
  y = readY();
  while ( x >= 87 && x <=109)
  {
   x = readX();
   y = readY();
   if(y <= 85)
   {
    data = '1'; // fast forward
    USARTWriteChar(data);
    PORTB = 0xC0;
    PORTC = 0x00;
   }
   else if (y >85  && y <=88)
   {
	data = '2'; // med forward
	USARTWriteChar(data);
	PORTB = 0x40;
	PORTB = 0x00;
   }
   else if (y >88  && y <=91)
   {
	data = '3'; //slow forward
	USARTWriteChar(data);
	PORTB = 0x80;
	PORTC = 0x00;
   }
   else if (y > 91 && y <=110)
   {
    data = '4'; // stop
    USARTWriteChar(data);
    PORTB = 0x00;
    PORTC = 0xff;
   }
   else if (y > 110 && y <=115)
   {
    data = '5'; // slow back
    USARTWriteChar(data);
    PORTB = 0x04;
    PORTC = 0x00;
   } 
   else if (y > 115)
   {
    data = '6'; // med back
    USARTWriteChar(data);
    PORTB = 0x20;
    PORTC = 0x00;
   } 
   else
   {
    data = '4'; // stop
    USARTWriteChar(data);
    PORTB = 0x00;
    PORTC = 0xff;
   }
  }
  if(x <= 82)
  {
   data = '7'; // 360 right
   USARTWriteChar(data);
   PORTB = 0x01;
   PORTC = 0x00;
  }  
  else if (x >82  && x <87)
  {
   data = '8'; // slow right
   USARTWriteChar(data);
   PORTB = 0x02;
   PORTC = 0x00;
  } 
  else if (x > 109 && x <=115)
  {
   data = '9'; // slow left
   USARTWriteChar(data);
   PORTB = 0x00;
   PORTC = 0x00;
  } 
  else if (x >115)
  {
   data = '0'; // left 360
   USARTWriteChar(data);
   PORTB = 0x20;
   PORTC = 0x00;
  }   
  else 
  {
   data = '4'; // stop
   USARTWriteChar(data);
   PORTB = 0x00;
   PORTC = 0xff;
  }*/
 }
 return 0;
}


/*int main(void)

{ 	char data;
	USARTInit(51);

	while(1)
	{ data = '1';
	  USARTWriteChar(data);
    }
}*/

	
