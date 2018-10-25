//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#pragma once

#include "Deck.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Score.h"
#include <sstream>

class Round
{   
public:
   Round();
   Round(string next, string lastCap, int rnd);
   void createPlayers();

   void startGame();
   void loadGame();
   void setSavedPreferences(int lineNumber, string line);
   vector<Card> makeCardFromFile(vector<string> cards);
   
   void printDeckConfigChoices();
   void loadDeckFromFile();
   void displayMainMenu(int& turn);
   void dealCardsToPlayers(bool newRound);

   void gamePlay();
   void makeMove(int& turn);

   void calculateScore();
   vector<pair<string, int>> sendRndScoreToTourney();
   void printScore();

   void saveGame();
   void saveBuildOwnerToFile(ofstream &saveToFile);
   void saveTableCardsToFile(ofstream &saveToFile);
   void saveSingleBuildToFile(ofstream &saveToFile, vector<Card> &singleBuild);
   void saveMultipleBuildToFile(ofstream &saveToFile, vector<vector<Card>> &multiBuild);
   void getHelp(int& turn);
   void quitGame();

   int getRoundNumber() const;
   void setRoundNumber(int rnd);
   string getLastCapturer() const;
   void setLastCapturer(string capturer);
   string getNextPlayer() const;
   void setNextPlayer(string next);
   void setDeck(vector<Card> tempDeck);

   vector<Card>& getTableCards();
   void setTableCards(vector<Card> cards);
   string getString(char x);
   bool isTableEmpty() const;

   void removeCardsFromTable(vector<Card> cardsToRemove);

   void displayRoundStatus();
   void printCardsOnTable();
   void printCardsOnHand();
   void printCardsOnPile();

   ~Round();

private:
   int roundNumber;
   int numberOfPlayers;
   int humanIndex;
   int computerIndex;

   string lastCapturer;
   string nextPlayer;
   bool isNewGame;

   vector<Card> tableCards;
   Deck deck;

   Player *players[2];
};