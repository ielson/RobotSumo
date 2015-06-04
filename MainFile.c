/*
 * robot_project_andreas.c
 *
 * Created: 18.05.2015 22:14:06
 *  Author: Andreas Glatz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "init.h"
#include "BluetoothFunctions.h"
#include "Functions.h"
#include "States.h"

#define backLEDRight 
#define backLEDLeft 
#define unterLED 
#define irReceiverLeft 
#define irReceiverRight 
#define usTriggerLeft 
#define usEchoLeft 
#define usTriggerRight 
#define usEchoRight 

char toggle = 0;
char tim0 = 0;
unsigned char irLeftOff,irLeftOn, irRightOn, irRightOff, command=0, counter=0;


int main(void)
{

	sei();           // Globale Interrupts aktivieren
	InitDDR();
	InitPWM();
	InitTIM0();
	InitADC(1,0);
	InitUART();
	PORTD |= (1<<PD4);
	while(1)
    {
		
			if (leftLineDetector > followLineParameter)
			{
				Drive(255,0);
			}
			if (rightLineDetector > followLineParameter)
			{
				Drive(0,255);
			}
		
    }	
}

ISR(TIMER0_OVF_vect)  // Tenho que mudar para outro arqiuvo que nao o main e preciso ver se usa alguma variavel do ISR no programa principal se nao ele nao é incluido
{	
	tim0++;
	if (tim0 > 1)
	{
		PORTC |= (1<<PC4);
		if (tim0 > 2)
		{
			tim0 = 0;
			InitADC(1,0);
			irLeftOn = ADCH;
			InitADC(0,1);
			irRightOn = ADCH;
			leftLineDetector = irLeftOff - irLeftOn;
			rightLineDetector = irRightOn - irRightOff;	
			Output(irLeftOff);
			Output(irLeftOn);
			Output(leftLineDetector);
			Output(irRightOn);
			Output(irRightOff);
			Output(rightLineDetector);
		}
	}
	else
	{
		PORTC &= ~(1<<PC4);
		if (tim0 > 0)
		{
			InitADC(1,0);
			irLeftOff = ADCH;
			InitADC(0,1);
			irRightOff = ADCH;
		}
	}

}

ISR(USART_RXC_vect){
	
	command=UDR; //commands in main
	
	if (command == 'b')
	{
		Drive(0,0);
		PORTC &= ~(1<<PC4);
		PORTD |=(1<<PD4)|(1<<PD5)|(1<<PD6)|(1<<PD7);
	}
	if (command == 'c')
	{
		Drive(255,255);
		PORTC &= ~((1<<PC4)|(1<<PD5)|(1<<PD4));
		PORTD |= (1<<PD6)|(1<<PD7);
	}
}