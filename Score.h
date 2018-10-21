//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/16/2018
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

   multimap <int, vector<Card>> getBuildComb() const;

   void calculateMostCards();
   void calculateMostSpades();
   void calculate10OfDiamonds();      
   void calculate2OfSpades();
   void calculatePerAce();
   void calculateTotalScore();

   int cardScore(Card tempCard);
   int calcBuildScore(const vector<Card> buildCards);

   vector <string> powerSet(int tableSize);
   void buildScoreMap(vector<string>& powerSets, const vector<Card>& tableCards);

   void printBuildMap(multimap<int, vector<Card>> map);

private:
   int playerOneScore;
   int playerTwoScore;

   vector<Card> playerOnePile, playerTwoPile;
   multimap <int, vector<Card>> buildComb;
};