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


char toggle = 0;
char tim0 = 0;
unsigned char IRLeftOff;
unsigned char IRLeftOn;
unsigned char IRRightOn;
unsigned char IRRightOff;
unsigned char command=0;
unsigned char counter=0;



int main(void)
{

	sei();           // Globale Interrupts aktivieren
	InitDDR();		//hello
	InitPWM();
	InitTIM0();
	InitADC(1,0);
	UARTConfig();
	PORTD |= (1<<PD4);
    char x = 3;
	while(1)
    {
		
			if (leftLineDetector > x)
			{
				Drive(255,0);
			}
			if (rightLineDetector > x)
			{
				Drive(0,255);
			}
		
    }	
}

ISR(TIMER0_OVF_vect)
{	
	tim0++;
	if (tim0 > 1)
	{
		PORTC |= (1<<PC4);
		if (tim0 > 2)
		{
			tim0 = 0;
			
			
			InitADC(1,0);
			IRLeftOn = ADCH;
			InitADC(0,1);
			IRRightOn = ADCH;
			leftLineDetector = IRLeftOff - IRLeftOn;
			rightLineDetector = IRRightOn - IRRightOff;	
			Output(IRLeftOff);
			Output(IRLeftOn);
			Output(leftLineDetector);
			Output(IRRightOn);
			Output(IRRightOff);
			Output(rightLineDetector);
		}
	}
	else
	{
		PORTC &= ~(1<<PC4);
		if (tim0 > 0)
		{
			InitADC(1,0);
			IRLeftOff = ADCH;
			InitADC(0,1);
			IRRightOff = ADCH;
		}
	}

}

ISR(USART_RXC_vect){
	
	command=UDR; //commands in main
	
	if (command == 'b')
	{
		Drive(0,0);
		PORTC &= ~(1<<PC4);
		PORTD |= (1<<PD5);
		PORTD |= (1<<PD4);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
	if (command == 'c')
	{
		Drive(255,255);
		PORTC &= ~(1<<PC4);
		PORTD &= ~(1<<PD5);
		PORTD &= ~(1<<PD4);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
}