//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
//****************************************************

#pragma once
#include "Deck.h"
#include "stdafx.h"

class Player
{
public:
   Player();
   
   void addCardsToHand(Card card);

   void playerCardsOnHand(string playerIdentifier);

   void playerCardsOnPile(string playerIdentifier);

   vector<Card> getCardsOnPile() const;

   vector<Card> getCardsOnHand() const;

   void setCardsOnHand(vector<Card> cardSelected);

   void makeNextMove();

   void setPlayerScore(int playerScore);

   int getPlayerScore() const;

   int getFirstBuildScore() const;

   bool isCardOnHand(string cardSelected) const;
   bool isCardOnPile(string cardSelected) const;
   bool isCardOnTable(string cardSelected, vector<Card> cardsOnTable) const;
   bool isDigit(string temp) const;

   string getString(char x);

   int cardScore(Card tempCard);
   int calcLooseCardScore(vector<Card> looseCards);

   bool makeSingleBuild(vector<Card>& tableCards);

   bool makeMultipleBuild(vector<Card>& tableCards);

   bool increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild);

   void initiateBuild(Card &handSelCard, vector<Card> &looseCardsSelected, int handCardScore);

   void initiateMultipleBuild(vector<Card> &looseCardsSelected);

   bool captureCards(vector<Card>& tableCards);

   bool captureSetCards(vector<Card>& tableCards, Card& handSelCard);

   void removeCardsOnHand(Card& cardToRemove);

private:
   int score;
   int firstBuildScore;
   vector<Card> cardsOnPile;
   vector<Card> cardsOnHand;
   tuple<string, vector<Card>> singleBuildCard;
   tuple<string, vector<vector<Card>>> multipleBuildCard;
};