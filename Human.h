//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#pragma once
#include "Player.h"

class Human:public Player
{
public:
   Human(string name) : Player(name) {};

   void play(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild);

   bool makeSingleBuild(vector<Card>& tableCards);
   bool makeMultipleBuild(vector<Card>& tableCards);
   bool increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild);
   void initiateBuild(vector<Card> &looseCardsSelected, int handCardScore);
   void initiateMultipleBuild(vector<Card> &looseCardsSelected);
   bool captureCards(vector<Card>& tableCards);
   bool captureSingleBuild(int handCardScore, Card &selectedHandCard);
   bool captureMultipleBuild(int handCardScore, Card &selectedHandCard);
   bool captureSetCards(vector<Card>& tableCards, Card& selectedHandCard);
   bool trailCard(vector<Card>& tableCards);

   ~Human();
};