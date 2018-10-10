//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
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

   void setFirstPlayer(char firstPlayer);

private:
   char firstPlayer;
};