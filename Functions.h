char leftLineDetector, rightLineDetector, direction, followLineParameter = 3;
uint16_t findline;

void Drive(unsigned char rightWheel, unsigned char leftWheel); //Maybe we don't really need it


void Drive(unsigned char rightWheel, unsigned char leftWheel){
	OCR1AH = 0x00; //Maybe we need to change this to go to full speed
	OCR1AL = leftWheel;
	
	OCR1BH = 0x00;
	OCR1BL = rightWheel;
	
}

void FollowLine(void)
{
	char followLineParameter = 25;
	if (leftLineDetector < followLineParameter && rightLineDetector > followLineParameter)	//at the line right
	{
		findline = 900;
		direction = 1;
		Drive(125,0);
		PORTD |= (1<<PD5);
		PORTD |= (1<<PD4);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
	if (leftLineDetector > followLineParameter && rightLineDetector < followLineParameter)	//at the line left
	{
		findline = 900;
		direction = 2;
		Drive(0,125);
		PORTD |= (1<<PD5);
		PORTD |= (1<<PD4);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
	if (leftLineDetector < followLineParameter && rightLineDetector < followLineParameter)	//on the line
	{
		findline = 900;
		Drive(0,0);
		PORTD |= (1<<PD5);
		PORTD |= (1<<PD4);
		PORTD |= (1<<PD6)|(1<<PD7);
	}
	if (leftLineDetector > followLineParameter && rightLineDetector > followLineParameter) //No line
	{
		findline++;
		
		if (findline<=1600)
		{
			if (direction==2)
			{
				Drive(0,255);
				PORTD |= (1<<PD5);
				PORTD &= ~(1<<PD4);
				PORTD |= (1<<PD7);
				PORTD &= ~(1<<PD6);
			}
			else
			{
				Drive(255,0);
				PORTD |= (1<<PD5);
				PORTD &= ~(1<<PD4);
				PORTD |= (1<<PD6);
				PORTD &= ~(1<<PD7);
			}
		}
		if (findline>1600)
		{
			Drive(255,100);
			PORTD |= (1<<PD5);
			PORTD &= ~(1<<PD4);
			PORTD |= (1<<PD6);
			PORTD &= ~(1<<PD7);
		}
		if (findline>6000)
		{
			Drive(0,0);
			PORTD |= (1<<PD5);
			PORTD |= (1<<PD4);
			PORTD |= (1<<PD6)|(1<<PD7);
		}
		if (findline>8000)
		{
			findline=0;
		}
		
	}
}


void Output(unsigned char temp){
	while(!(UCSRA & (1<<UDRE))){};
	UDR = temp;
	while(!(UCSRA & (1<<TXC))){};
	UCSRA |= (1<<TXC);
}