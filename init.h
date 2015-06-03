void InitDDR(void); // I don't know if we really need this
void InitPWM(void);

void UARTConfig(){
	UBRRH = 0;
	UBRRL = 51; 					//Baudrate 9600, Asynchronous Normal mode
	UCSRC =(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); 	//Frameformat 8Bit, 1 Stopbit, no Parity
	UCSRB =(1<<RXEN)| (1<<RXCIE)|(1<<TXEN);			//receive enabled, rx interrupt enabled
}

void InitADC(unsigned char links,unsigned char rechts){
	ADCSRA |= (1<<ADEN);	//|(1<<ADPS2)|(1<<ADPS1)AD-Enable|Prescaler CLK/128
	if ((links == 0 && rechts == 0)|(links == 1 && rechts == 1))
	{
		ADMUX = (1<<REFS0)|(1<<ADLAR);		//ADC0 Select AVCC as Vref, left justify data registers and select ADC0 as input channel
	}
	
	if (links == 1 && rechts == 0)
	{
		ADMUX = (1<<REFS0)|(1<<MUX0)|(1<<MUX1)|(1<<ADLAR);		//ADC3 Select AVCC as Vref, left justify data registers and select ADC0 as input channel
	}
	
	if (links == 0 && rechts == 1)
	{
		ADMUX = (1<<REFS0)|(1<<MUX1)|(1<<ADLAR);		//ADC2 Select AVCC as Vref, left justify data registers and select ADC0 as input channel
	}
	ADCSRA |= (1<<ADSC);				// Start Conversion
}

void InitPWM(void){
	
	TCCR1A |= (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1);
	TCCR1B |= (1<<CS11); //Prescaler
	
	ICR1H = 0x00;	//Startwert (Bottom)
	ICR1L = 0x00;
	
	OCR1AH = 0x00;	//Endwert (Top)
	OCR1AL = 0x00;
	
	OCR1BH = 0x00;	//Endwert (Top)
	OCR1BL = 0x00;
	
	
}

void InitDDR(void){			//DDR-config
	//OUTPUT
	DDRB |= (1<<PB1)|(1<<PB2);	//PWM
	DDRC |= (1<<PC4);			//LED
	DDRD |= (1<<PD6)|(1<<PD7);	//motor enable
	DDRD |= (1<<PD4)|(1<<PD5);	//back led
}

void InitTIM0(void){
	TIMSK |= (1<<TOIE0);         //Overflow Interrupt aktivieren
	TCCR0 |= (1<<CS02)|(1<<CS00);       // Prescaler auf 1 setzen, Takt = 8MHz
}