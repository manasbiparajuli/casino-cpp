//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#pragma once
#include "Card.h"

class Deck 
{   
public:
	Deck();

   void createShuffledDeck();
	void shuffleDeck();
	Card dealCard();
   void printDeck();
   bool isDeckEmpty() const;
   vector<Card> getDeck();
   void setDeck(vector<Card> tempDeck);

   ~Deck();

private:
   vector <Card> deck;
};