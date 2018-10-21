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

   void createRounds();

   void tossCoin();

   void newGame();

   void loadGame();

   void setFirstPlayer(string firstPlayer);

private:
   string firstPlayer;
   string lastCapturer;
   int roundNumber;
};