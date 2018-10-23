//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
//****************************************************

#include "Card.h"

// ****************************************************************
// Function Name: Card
// Purpose: serves as a default constructor
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Card::Card()
{
}

// ****************************************************************
// Function Name: Card
// Purpose: constructor to create a card instance 
// Parameters: 
//			suit, a string to hold the suit value of the card
//			face, a string to hold the value of the face card
// Return value: none
// Assistance Received: none
// ****************************************************************
Card::Card(string suit, string face)
{
	this->suit = suit;
   this->face = face;
}

// ****************************************************************
// Function Name: getFace
// Purpose: return the face value of a card
// Parameters: none
// Return value: face of the card
// Assistance Received: none
// ****************************************************************
string Card::getFace()
{
	return face;
}

// ****************************************************************
// Function Name: getSuit
// Purpose: return the suit value of a card
// Parameters: none
// Return value: suit value of the card
// Assistance Received: none
// ****************************************************************
string Card::getSuit()
{
	return suit;
}

// ****************************************************************
// Function Name: cardToString
// Purpose: get the string value of the card
// Parameters: none
// Return value: the string representation of the card
// Assistance Received: none
// ****************************************************************
string Card::cardToString()
{
   return this->getSuit() + this->getFace();
}

string Card::cardToString() const
{
   const string& suitValue = as_const(suit);
   const string& faceValue = as_const(face);

   return suitValue + faceValue;
}

Card::~Card()
{
}

bool operator==(const Card & card1, const Card & card2)
{
   if (card1.cardToString() == card2.cardToString())
   {
      return true;
   }
   return false;
}
