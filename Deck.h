//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 9/18/2018
//****************************************************

#pragma once
#include "Card.h"

class Deck 
{
private:
	vector <Card> deck;
   
public:
	Deck();

	void shuffleDeck();

	Card dealCard();

   void printDeck();

   bool isDeckEmpty();
};