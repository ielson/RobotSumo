char leftLineDetector, rightLineDetector, direction, lineParameter = 3, fighting, atLeftEdge, atRightEdge;
uint16_t findline;
char tim0 = 0;
unsigned char irLeftOff,irLeftOn, irRightOn, irRightOff, command=0;

void BattleStart(void)
{
	fighting = 1;
}
void Drive(unsigned char rightWheel, unsigned char leftWheel){
	OCR1AH = 0x00; //Maybe we need to change this to go to full speed
	OCR1AL = leftWheel;
	
	OCR1BH = 0x00;
	OCR1BL = rightWheel;
	
}

void AtEdge(void){
	if (leftLineDetector<lineParameter)
	{
		atLeftEdge = 1;
	}
	if (rightLineDetector<lineParameter)
	{
		atRightEdge = 1;
	}
}

void FollowLine(void)
{
	char lineParameter = 5;
	if (leftLineDetector > lineParameter && rightLineDetector < lineParameter)	//at the line right
	{
		findline = 900;
		direction = 1;
		Drive(125,0);
		PORTD |= (1<<ledBackRight);
		PORTD |= (1<<ledBackLeft);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
	if (leftLineDetector < lineParameter && rightLineDetector > lineParameter)	//at the line left
	{
		findline = 900;
		direction = 2;
		Drive(0,125);
		PORTD |= (1<<ledBackRight);
		PORTD |= (1<<ledBackLeft);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
	if (leftLineDetector > lineParameter && rightLineDetector > lineParameter)	//on the line
	{
		findline = 900;
		Drive(0,0);
		PORTD |= (1<<ledBackRight);
		PORTD |= (1<<ledBackLeft);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
	if (leftLineDetector < lineParameter && rightLineDetector < lineParameter) //No line
	{
		findline++;
		
		if (findline<=1600)
		{
			if (direction==2)
			{
				Drive(0,255);
				PORTD |= (1<<ledBackRight);
				PORTD &= ~(1<<ledBackLeft);
				PORTD |= (1<<PD7);
				PORTD &= ~(1<<PD6);
			}
			else
			{
				Drive(255,0);
				PORTD |= (1<<ledBackRight);
				PORTD &= ~(1<<ledBackLeft);
				PORTD |= (1<<PD6);
				PORTD &= ~(1<<PD7);
			}
		}
		if (findline>1600)
		{
			Drive(255,100);
			PORTD |= (1<<ledBackRight);
			PORTD &= ~(1<<ledBackLeft);
			PORTD |= (1<<PD6);
			PORTD &= ~(1<<PD7);
		}
		if (findline>6000)
		{
			Drive(0,0);
			PORTD |= (1<<ledBackRight);
			PORTD |= (1<<ledBackLeft);
			PORTD |= (1<<PD6)|(1<<PD7);
		}
		if (findline>8000)
		{
			findline=0;
		}
		
	}
}

void TestFollowLine(void)
{
 
}

void Output(unsigned char temp){
	while(!(UCSRA & (1<<UDRE))){};
	UDR = temp;
	while(!(UCSRA & (1<<TXC))){};
	UCSRA |= (1<<TXC);
}

ISR(TIMER0_OVF_vect)
{
	tim0++;
	if (tim0 > 1)
	{
		PORTC |= (1<<irSender);
		if (tim0 > 2)
		{
			tim0 = 0;
			InitADC(1,0);
			irLeftOn = ADCH;
			InitADC(0,1);
			irRightOn = ADCH;
			leftLineDetector = irLeftOff - irLeftOn;
			rightLineDetector = irRightOn - irRightOff;
			Output(leftLineDetector);
			Output(rightLineDetector);
		}
	}
	else
	{
		PORTC &= ~(1<<irSender);
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
	PORTD ^=(1<<ledBackLeft);
	unsigned char command=UDR; //commands in main
	
	if (command == 'b') //Battle start
	{
		
	}
	if (command == 'e') //Battle Stop
	{
		
	}
	if (command == 'f')//Follow Line
	{
		Output(125);
	}
	if (command == 's')//Switch Off
	{
		
	}
}