//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 9/18/2018
//****************************************************

#pragma once
#include "Deck.h"
#include "stdafx.h"

class Player
{
private:
   string playerName;

public:
   Player(string playerName);

   void playerCards();

   void makeNextMove();
};
