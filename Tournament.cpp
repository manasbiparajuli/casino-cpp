//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#include "Tournament.h"

// ****************************************************************
// Function Name: Tournament()
// Purpose: serves as a default constructor for Tournament class
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Tournament::Tournament()
{
   cout << R"(
   Welcome to Casino, a board game where your objective is to
   score the most points by capturing cards.To begin the game, we 
   will have a coin toss that will determine who will go first. 
   A correct choice will let you go first, else computer plays first.)" << endl;

   firstPlayer = "Human";
   lastCapturer = "";
   roundNumber = 1;

   startMenu();
}

// ****************************************************************
// Function Name: startMenu()
// Purpose: gives option for the user to either start a new game or 
//          load a game from a saved file
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Tournament::startMenu()
{
   // Display choices for new game or load game from file
   cout << "**********************************" << endl;
   cout << "1. New Game" << endl;
   cout << "2. Load Saved Game" << endl;
   cout << "**********************************" << endl;

   // player input for the choice
   int choice;

   cout << "Enter your choice (1/2): ";
   // validate user input
   do
   {
      cin >> choice;
   } while (!(choice == 1 || choice == 2));

   cout << endl;

   if (choice == 1) { newGame();}
   else { loadGame();}
}

// ****************************************************************
// Function Name: createRounds()
// Purpose: creates rounds for the game
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Tournament::createRounds()
{
   Round round(firstPlayer, "", roundNumber);
}

// ****************************************************************
// Function Name: tossCoin
// Purpose: initiates a coin toss and prompts the human player to guess.
//          A correct guess will let the human player go first, else the
//          computer will go first.
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Tournament::tossCoin()
{
   // seed value to randomize number
   // used  explicit cast as seed wants an unsigned int of 32-bit integer
   auto seed = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());

   // random number generator
   auto rng = default_random_engine(seed);
   uniform_int_distribution<> generate(1, 2);

   // generate random number between 1 and 2
   // treat 1 as Heads, 2 as Tails
   char tossedSide = (generate(rng) == 1) ? 'H' : 'T';

   // get user choice for the coin toss
   char choice;
   cout << "The coin has been tossed. Choose (H/T): ";

   // validate user input. Accept lower case values for H and T
   do 
   {
      cin >> choice;
   } while (!(choice == 'H' || choice == 'h' || choice == 'T' || choice == 't'));

   // Display the result of the user choice on the screen and set the firstPlayer value
   if (toupper(choice) == tossedSide)
   {
      cout << "\nCorrect choice. You go first." << endl;
      setFirstPlayer("Human");
   }
   else
   {
      cout << "\nWrong Choice. Computer goes first." << endl;
      setFirstPlayer("Computer");
   }
}

// ****************************************************************
// Function Name: newGame
// Purpose: initiates new game and starts coin toss to decide the first player
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Tournament::newGame()
{
   tossCoin();
   createRounds();
}

// ****************************************************************
// Function Name: loadGame
// Purpose: loads the game from a saved file
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Tournament::loadGame()
{
   Round round(firstPlayer, lastCapturer, roundNumber);
   round.loadGame();
   round.gamePlay();
}

// ****************************************************************
// Function Name: setFirstPlayer
// Purpose: sets the first player to start the game
// Parameters: firstPlayer, a character. Options include 'H' for human, 
//             'C' for computer. 
// Return value: none
// Assistance Received: none
// ****************************************************************
void Tournament::setFirstPlayer(string firstPlayer)
{
   this->firstPlayer = firstPlayer;
}