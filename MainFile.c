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


#define ledBackRight PD5
#define ledBackLeft PD4
#define irSender PC4
#define irReceiverLeft PC2 
#define irReceiverRight PC3
#define usTriggerLeft PC0
#define usEchoLeft PD3
#define usTriggerRight PC1 
#define usEchoRight PD2

char state;

int main(void)
{
	fighting = 0;
	sei();           // Globale Interrupts aktivieren
	InitDDR();
	InitPWM();
	InitTIM0();
	InitADC(1,0);
	InitUART();
	while (fighting)
	{
		if (atLeftEdge||atRightEdge){
			state = 0;
		}
		
		switch (state)
		{
			case 0:
				Survive();
			break;
			case 1:
				Hunt();
			break;
			case 2:
				Target();
			break;
			case 3:
				Attack();
			break;
				
		}
	}
}