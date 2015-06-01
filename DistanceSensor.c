#include <avr/io.h>
#include "BluetoothConfig.h"

#define EmissorFrontBig 
#define EmissorFrontSmall 
#define SensorFrontLeft 
#define SensorFrontRight 

unsigned short distanceOpponentLeft;
unsigned short distanceOpponentRight;

void TIMER_init(){

	TCCR1A=(1 << WGM10) | (1 << COM1A1)| (1 << COM1B1);
	//PWM, Phase Correct, 8-bit    //???

	TCCR1B=(1<<CS11);    //Prescaling CLK/8

}

void ADCInit(){
	
	ADCSRA=(1<<ADEN)  | (1 << ADPS2) | (1 << ADPS1);
	//ADC on    //Takt CK/64
	ADMUX=(1 << REFS0) | (1 << ADLAR);
	//Referenzspannung //Ergebnis linksbündig
}

//Shows the distance measured by the left PT
unsigned short DistancePTLeft(){
	ADMUX=(1 << REFS0)|(1 << ADLAR)|(1 << MUX0);    //ADC1 as input
	ADCSRA|=(1<<ADSC); //starts conversion, ADSC wird gelöscht wenn AD Wandlung fertig ist
	while(ADCSRA&(1<<ADSC));    //true solange ADSC=1 //wartet bis AD Wandlung abgeschlossen ist
	return ADCH;
}

//Shows the distance measured by the right PT
unsigned short  DistancePTLeft(){
	ADMUX=(1 << REFS0) | (1 << ADLAR);    //ADC0 as input
	ADCSRA|=(1<<ADSC); //starts conversion, ADSC wird gelöscht wenn AD Wandlung fertig ist
	while(ADCSRA&(1<<ADSC));    //true solange ADSC=1 //wartet bis AD Wandlung abgeschlossen ist
	return ADCH;
}


int main(){

	DDRC|=(1<<EmissorFrontBig)|(1<<EmissorFrontSmall);
	DDRB&=~((1<<SensorFrontLeft)|(1<<SensorFrontRight));

	PORTC|=(1<<EmissorFrontBig)|(1<<EmissorFrontSmall);

	unsigned volatile short valueL,valueR;
	ADCInit();
	TIMER_init();
	USARTInit(51); //Just for testing
	
	while(1){
		distanceOpponentLeft=DistancePTLeft();
		USARTWriteChar(distanceOpponentLeft); //Just for testing
		distanceOpponentRight=DistanceRight();
		USARTWriteChar(distanceOpponentRight); // Just for testing
	}

	return 0;
}