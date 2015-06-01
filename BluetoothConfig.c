#include <avr/io.h>
#include "TC.h"

int _on, _battle;

void USARTInit(uint16_t ubrr_value)
{

    /* Initialize Usart with UBBR as parameter
   
   UBBR = ( (regular microcontroler clock speed) / 16 * baud ) - 1

   */
	
   //Set Baud rate

   UBRRL = ubrr_value;
   UBRRH = (ubrr_value>>8);

   /*Set Frame Format


   >> Asynchronous mode
   >> No Parity
   >> 1 StopBit

   >> char size 8

   */

   UCSRC=(1<<URSEL)|(3<<UCSZ0);


   //Enable The receiver and transmitter. (I don't think that we need the transmitter)

   UCSRB=(1<<RXEN)|(1<<TXEN);


}


char USARTReadChar()
{
   while(!(UCSRA & (1<<RXC)))
   {
      //Do nothing
   }
   return UDR;
}

void USARTWriteChar(char data)
{
   //Wait until the transmitter is ready

   while(!(UCSRA & (1<<UDRE)))
   {
      //Do nothing
   }

   //Now write the data to USART buffer

   UDR=data;
}

void WhichFunction(char commmand)
{
	switch (command)
	{
		case 'B':
		BattleStart();
		break;
		case 'E':
		BattleStop();
		break;
		case 'F':
		FollowLine();
		break;
		case 'S':
		BattleStop();
		break;
	}
}

void main()
{
   char data;
   USARTInit(51);    //Baud = 19200

   while(1)
   {
      //Read data
		data=USARTReadChar();
		WhichFunction(data);
   }
}