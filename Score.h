//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
//****************************************************

#pragma once
#include "Deck.h"

class Score
{
public:
   Score();

   Score(vector<Card> playerOnePile, vector<Card> playerTwoPile);
  
   void setPlayerOneScore(int score);

   void setPlayerTwoScore(int score);

   int getPlayerOneScore() const;

   int getPlayerTwoScore() const;

   void calculateMostCards();
   
   void calculateMostSpades();

   void calculate10OfDiamonds();
      
   void calculate2OfSpades();

   void calculatePerAce();

   void calculateTotalScore();

private:
   int playerOneScore;
   int playerTwoScore;

   vector<Card> playerOnePile, playerTwoPile;
};