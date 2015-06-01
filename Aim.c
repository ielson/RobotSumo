/*
 *  Aim.c
 *
 * Created: 01/06/2015 14:14:54
 *  Author: D. Andrade
 
 * I still need to add the vars in the main program.
 */ 


#include <avr/io.h>
#define inFront 

extern distanceOpponentLeft, distanceOpponentRight; 



int main(void)
{
    while(1)
    {
		if ((distanceOpponentLeft-distanceOpponentRight) < inFront)
		{
			state = "ATTACK";
		} 
		else
		{
			if (distanceOpponentLeft>distanceOpponentRight) //Desse jeito só vai virar se tiver exatamente as mesmas distancias, preciso mudar isso
			{
				Drive(0, 100);
			}
			if (distanceOpponentRight>distanceOpponentLeft)
			{
				Drive(100, 0);
			}
		}
    }
}