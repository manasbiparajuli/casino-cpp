//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
//****************************************************

#pragma once

#include "Deck.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Score.h"

class Round
{   
public:
   Round();

   void startGame();

   void printDeckConfigChoices();

   void loadDeckFromFile();

   void displayMainMenu();

   string getNextPlayer();
   
   void dealCardsToPlayers();

   void cardsOnTable();

   void printCardsOnHand();

   void printCardsOnPile();

   void calculateScore();

   void printScore();

   void saveGame();

   void makeMove();

   void getHelp();

   void quitGame();

   int getRoundNumber() const;

   void setDeck(vector<Card> tempDeck);

   void buildOption();

   void captureCard();

   vector<Card>& getTableCards();

private:
   int humanScore;
   int computerScore;
   int roundNumber;
   vector<Card> tableCards;

   Deck deck;
   Human humanPlayerOne;
   Computer computerPlayerTwo;
};