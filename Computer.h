//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#pragma once
#include "Player.h"
#include "Score.h"

class Computer:public Player
{
public:
   Computer(string name) : Player(name) {};
   void play(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild);
   bool makeSingleBuild(vector<Card>& tableCards);
   bool makeMultipleBuild(vector<Card>& tableCards);
   bool increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild);
   void initiateMultipleBuild(vector<Card> &looseCardsSelected);
   bool captureCards(vector<Card>& tableCards);
   bool captureSetCards(vector<Card>& tableCards, Card& handSelCard);
   bool trailCard(vector<Card>& tableCards);

   ~Computer();

private:
   Score score;
};