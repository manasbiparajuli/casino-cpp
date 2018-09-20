//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 9/18/2018
//****************************************************

#include "stdafx.h"
#include "Deck.h"

int main()
{
	cout << "Hello world" << endl;

   Deck deck;

//   deck.printDeck();
   deck.shuffleDeck();

   deck.printDeck();

   for (int i = 0; i < 8; i++)
   {
      Card card = deck.dealCard();
      cout << "\n" + card.cardToString();
   }

   system("pause");
	return 0;
}