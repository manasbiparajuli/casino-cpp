//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
//****************************************************

#include "stdafx.h"
#include "Tournament.h"

int main()
{
   //Tournament tournament;

   Round round;
   //round.printDeckConfigChoices();
   round.startGame();
   round.printCardsOnHand();

   round.buildOption();

   system("pause");
	return 0;
}