void ADC_init(){
	
	ADCSRA=(1<<ADEN)  | (1 << ADPS2) | (1 << ADPS1);
	//ADC on    //Takt CK/64
	ADMUX=(1 << REFS0) | (1 << ADLAR);
	//Referenzspannung //Ergebnis linksbündig

}

#define motorRight1
#define motorRight2  
#define motorRight3 
#define motorLeft1
#define motorLeft2  
#define motorLeft3 

void Drive(unsigned short leftWheel, unsigned short rightWheel){
	OCR1A=leftWheel;
	OCR1B=rightWheel;
	}	
}

int main(){

	//Colocar os motores como saída
	DDRD|=(1<<PD6)|(1<<motorRight1)|(1<<motorRight2);    //Why do we need pd6?
	DDRB|=(1<<motorLeft3)|(1<<motorRight3)|(1<<motorLeft1)|(1<<motorLeft2);
	ADC_init();
	Drive(100, 100);