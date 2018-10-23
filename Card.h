//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#pragma once
#include "stdafx.h"

class Card
{
public:
	Card();
	Card(string suit, string face);
	string getFace();
	string getSuit();
   string cardToString();
   string cardToString() const;
   friend bool operator==(const Card& card1, const Card& card2);

   ~Card();

private:
   // holds face value of the card
   string face;

   // holds suit value of the card
   string suit;
};