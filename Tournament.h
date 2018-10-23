//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#pragma once
#include "stdafx.h"
#include "Round.h"

class Tournament 
{
public:
   Tournament();

   void startMenu();
   void tossCoin();
   void newGame();
   void loadGame();
   void evaluateScores(std::vector<std::pair<std::string, int>> &roundScores, Round &round);
   void setFirstPlayer(string firstPlayer);
   void displayTourneyResult();
   ~Tournament();
private:
   int roundNumber;
   int playerOneScore;
   int playerTwoScore;

   string firstPlayer;
   string lastCapturer;

   string firstPlayerName;
   string secondPlayerName;
};