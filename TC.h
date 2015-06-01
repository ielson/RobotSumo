#include <avr/io.h>
#include "Drive.h"

extern int _on, _battle;

void Battle_Stop()
{
	Drive(0,0);
	_battle = 0;
}

void Standby()
{
	Battle_Stop();
	_on = 0;
}

