//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 9/18/2018
//****************************************************

#pragma once

#include "Deck.h"

class Round
{
private:
   int humanScore;
   int computerScore;

public:
   Round();

   void startGame();

   void currentPlayer();
   
   void dealCardsToPlayers();

   Card cardsOnTable();

   int calculateScore();
};