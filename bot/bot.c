#include<avr/io.h>
#include<util/delay.h>
#include<xslcd.h>
#include <avr/interrupt.h>

void init_pwm(void);
void set_pwm(unsigned char,unsigned char);
void forward_fast(void);
void forward_med(void);
void forward_slow(void);
void back_med(void);
void back_slow(void);
void right_slow(void);
void right_360(void);
void left_slow(void);
void left_360(void);
void stop(void);
void USARTInit(uint16_t);
char USARTReadChar(void);
void USARTWriteChar(char);


void init_pwm(void)
{
 TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0); 
 TCCR1B = _BV(CS11) | _BV(WGM12);
}

void set_pwm(unsigned char data1,unsigned char data2)
{
	OCR1AL=data1;	//left motor
	OCR1BL=data2;	//right motor
}

void forward_fast(void)
{
 set_pwm(5,5);
 PORTD |= 0x04;
 PORTD &= 0xF7;
 PORTB = 0x01;
}

void forward_med(void)
{
 set_pwm(60,60);
 PORTD |= 0x04;
 PORTD &= 0xF7;
 PORTB = 0x01;
}

void forward_slow(void)
{
 set_pwm(90,90);
 PORTD |= 0x04;
 PORTD &= 0xF7;
 PORTB = 0x01;
}

void back_med(void)
{
 set_pwm(40,40);
 PORTD |= 0x08;
 PORTD &= 0xFB;
 PORTB = 0x02;
}

void back_slow(void)
{
 set_pwm(90,90);
 PORTD |= 0x08;
 PORTD &= 0xFB;
 PORTB = 0x02;
}

void right_slow(void)
{
 set_pwm(20,20);
 PORTD |= 0x04;
 PORTD &= 0xF7;
 PORTB = 0x00;
}
 
void right_360(void)
{
 set_pwm(30,30);
 PORTD |= 0x04;
 PORTD &= 0xF7;
 PORTB = 0x02;
}

void left_slow(void)
{
 set_pwm(20,20);
 PORTD |= 0x00;
 PORTD &= 0xF3;
 PORTB = 0x01;
}

void left_360(void)
{
 set_pwm(30,30);
 PORTD |= 0x08;
 PORTD &= 0xFB;
 PORTB = 0x01;
}

void stop(void)
{
 set_pwm(255,255);
 PORTD |= 0x00;
 PORTD &= 0xF3;
 PORTB = 0x00;
}


void USARTInit(uint16_t ubrr_value)
{
 UBRRL = ubrr_value;
 UBRRH = (ubrr_value>>8);
 UCSRC=(1<<URSEL)|(3<<UCSZ0);
 UCSRB=(1<<RXEN)|(1<<TXEN);
}

char USARTReadChar(void)
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
 char data;
 DDRD |= 0xFC;
 DDRB = 0xFF; 
 InitLCD();
 USARTInit(51);
 init_pwm();
 LCDClear();
 LCDWriteStringXY(0,0,"Initialising...");
 _delay_ms(1600);
 while(data!='4')
 {
  LCDWriteStringXY(0,0,"Faulty data...");
  LCDWriteStringXY(0,1,"reception...");
  data = USARTReadChar();
 }
 LCDClear();
 LCDWriteStringXY(0,0,"Rock n Roll...!!!");
 _delay_ms(1600);
 while(1)
 {
  UDR = '4';
  data = USARTReadChar();
  switch (data)
  {
   case '1' :
   forward_fast();
   LCDWriteStringXY(0,0,"  Fast Forward    ");
   break;
   case '2' :
   forward_fast();
   LCDWriteStringXY(0,0,"  Medium Forward   ");
   break;
   case '3' :
   forward_med();
   LCDWriteStringXY(0,0,"  Slow forward    ");
   break;
   case '4' :
   stop();
   LCDWriteStringXY(0,0,">>> STOP <<<   ");
   break;
   case '5' :
   back_slow();
   LCDWriteStringXY(0,0,"  Slow Back    ");
   break;
   case '6' :
   back_med();
   LCDWriteStringXY(0,0,"  Medium Back   ");
   break;
   case '7' :
   right_360();
   LCDWriteStringXY(0,0,"  360 Right      ");
   break;
   case '8' :
   right_slow();
   LCDWriteStringXY(0,0,"   Slow Right     ");
   break;
   case '9' :
   left_slow();
   LCDWriteStringXY(0,0,"  Slow Left      ");
   break;
   case '0' :
   left_360();
   LCDWriteStringXY(0,0,"  Left 360      ");
   break;
   default:
   stop();
  }
 }
 return 0;
}

