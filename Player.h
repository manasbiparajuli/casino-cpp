//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#pragma once
#include "Deck.h"
#include "stdafx.h"

class Player
{
public:
   Player(string name);
   
   void addCardsToHand(Card card);
   void addCardsToPile(Card card);

   void printCardsOnHand();
   void printCardsOnPile();
   void printSingleBuild();
   void printMultipleBuild();

   vector<Card> getCardsOnPile() const;
   vector<Card> getCardsOnHand() const;

   void setCardsOnHand(vector<Card> cardSelected);
   void setCardsOnPile(vector<Card> cardSelected);

   void setPlayerScore(int playerScore);
   int getPlayerScore() const;
   int getFirstBuildScore() const;
   void setFirstBuildScore(int score);
   string getPlayerName() const;
   tuple<string, vector<Card>> getSingleBuild() const;
   void setSingleBuild(tuple<string, vector<Card>> build);
   tuple<string, vector<vector<Card>>> getMultipleBuild() const;

   bool isCardOnHand(string cardSelected) const;
   bool isCardOnPile(string cardSelected) const;
   bool isCardOnTable(string cardSelected, vector<Card> cardsOnTable) const;
   bool isDigit(string temp) const;
   bool isMultipleBuildExist() const;
   bool isSingleBuildExist() const;
   bool hasCapturedCard() const;

   string getString(char x);

   int calcSingleCardScore(Card tempCard);
   int calcLooseCardScore(vector<Card> looseCards);

   virtual void play(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild) = 0;
   virtual bool makeSingleBuild(vector<Card>& tableCards) = 0;
   virtual bool makeMultipleBuild(vector<Card>& tableCards) = 0;
   virtual bool increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild) = 0;
   virtual void initiateMultipleBuild(vector<Card> &looseCardsSelected) = 0;
   virtual bool captureCards(vector<Card>& tableCards) = 0;
   virtual bool captureSetCards(vector<Card>& tableCards, Card& handSelCard) = 0;
   virtual bool trailCard(vector<Card>& tableCards) = 0;

   void removeCardFromHand(Card& cardToRemove);
   void removeCardsFromTable(vector<Card>& tableCards, vector<Card> looseCardsToRemove);
   Card findCommonCard(const vector<Card>& matchedTableCards);

   ~Player();

protected:
   int score;
   int firstBuildScore;
   string playerName;
   bool hasCapturedInCurMove;
   vector<Card> cardsOnPile;
   vector<Card> cardsOnHand;
   tuple<string, vector<Card>> singleBuildCard;
   tuple<string, vector<vector<Card>>> multipleBuildCard;
};