//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 9/25/2018
//****************************************************

#include "Score.h"

Score::Score()
{
   this-> playerOneScore = 0;
   this-> playerTwoScore = 0;
}

Score::Score(vector<Card> playerOnePile, vector<Card> playerTwoPile)
{
   this->playerOneScore = 0;
   this->playerTwoScore = 0;
   this->playerOnePile = playerOnePile;
   this->playerTwoPile = playerTwoPile;
}

void Score::setPlayerOneScore(int score)
{
   playerOneScore += score;
}

void Score::setPlayerTwoScore(int score)
{
   playerTwoScore += score;
}

int Score::getPlayerOneScore() const
{
   return playerOneScore;
}

int Score::getPlayerTwoScore() const
{
   return playerTwoScore;
}

void Score::calculateMostCards()
{
   int plOneTotal = static_cast<int> (playerOnePile.size());
   int plTwoTotal = static_cast<int> (playerTwoPile.size());

   cout << "Human has    " << plOneTotal << " cards." << endl;
   cout << "Computer has " << plTwoTotal << " cards." << endl;

   if (plOneTotal > plTwoTotal) { setPlayerOneScore(3); }
   else if (plOneTotal < plTwoTotal) { setPlayerTwoScore(3); }
}

void Score::calculateMostSpades()
{
   int plOneTotal = 0;
   int plTwoTotal = 0;

   for (auto card : playerOnePile)
   {
      if (card.getSuit() == "S") { plOneTotal++; }
   }

   for (auto card : playerTwoPile)
   {
      if (card.getSuit() == "S") { plTwoTotal++; }
   }

   cout << "Human has    " << plOneTotal << " spades." << endl;
   cout << "Computer has " << plTwoTotal << " spades." << endl;

   if (plOneTotal > plTwoTotal) { setPlayerOneScore(1); }
   else if (plOneTotal < plTwoTotal) { setPlayerTwoScore(1); }
}

void Score::calculate10OfDiamonds()
{
   bool plOneHas10OfDiamonds = false;

   for (auto card : playerOnePile)
   {
      if (card.cardToString() == "DX") 
      { 
         plOneHas10OfDiamonds = true;
         setPlayerOneScore(2);
         break;
      }
   }

   if (!plOneHas10OfDiamonds) { setPlayerTwoScore(2); }
}

void Score::calculate2OfSpades()
{
   bool plOneHas2OfSpades = false;

   for (auto card : playerOnePile)
   {
      if (card.cardToString() == "S2")
      {
         plOneHas2OfSpades = true;
         setPlayerOneScore(1);
         break;
      }
   }

   if (!plOneHas2OfSpades) { setPlayerTwoScore(1); }
}

void Score::calculatePerAce()
{
   int plOneTotal = 0;
   int plTwoTotal = 0;

   for (auto card : playerOnePile)
   {
      if (card.getSuit() == "A") { plOneTotal++; }
   }

   for (auto card : playerTwoPile)
   {
      if (card.getSuit() == "A") { plTwoTotal++; }
   }

   setPlayerOneScore(plOneTotal);
   setPlayerTwoScore(plTwoTotal);
}

void Score::calculateTotalScore()
{
   calculateMostCards();
   calculateMostSpades();
   calculate10OfDiamonds();
   calculate2OfSpades();
   calculatePerAce();
}