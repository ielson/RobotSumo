void survive (char mode){
	 if (!mode == null)	
		switch (command)
		{
			case 1:
			dodgeleft();
			break;
			case '2':
			dodgerigth();
			break;
			case '3':
			spinleft();
			break;
			case '4':
			spinright();
			break;
		}
	else{
		//line dodge
	}
}

void dodgeleft(){
	Drive(-50, -100);
	Wait(500);
	spinleft();
}

void spinleft(){
	Drive(100, -100);
	Wait(1500);
	Hunt();
}

void dodgeright(){
	Drive(-100, -50);
	Wait(500);
	spinright();	
}

void spinright(){
	Drive(-100, 100);
	Wait(1500);
	Hunt();
}
