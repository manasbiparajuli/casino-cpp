//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/16/2018
//****************************************************

#include "stdafx.h"
#include "Tournament.h"

int main()
{
   //Tournament tournament;

   Round round;
   //round.loadGame();
   ////round.printDeckConfigChoices();
   round.startGame();
   round.printCardsOnHand();

   round.buildOption();

   system("pause");
	return 0;
}