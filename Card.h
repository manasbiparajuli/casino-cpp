//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 9/18/2018
//****************************************************

#pragma once
#include "stdafx.h"

class Card
{
private:
	// holds face value of the card
	string face;

	// holds suit value of the card
	string suit;

public:
	Card();

	Card(string suit, string face);

	string getFace();

	string getSuit();

   string cardToString();
};