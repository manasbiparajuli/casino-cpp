//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
//****************************************************

#include "Player.h"

// ****************************************************************
// Function Name: Player()
// Purpose: serves as a default constructor for Player Class
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Player::Player()
{
   score = 0;
   firstBuildScore = 0;
}

// ****************************************************************
// Function Name: addCardsToHand
// Purpose: adds cards to the players' hand
// Parameters: card, a Card object. It holds the current card to be added.
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::addCardsToHand(Card card)
{
   cardsOnHand.push_back(card);
}

// ****************************************************************
// Function Name: playerCardsOnHand
// Purpose: prints the current cards on the player's hand
// Parameter: playerIdentifier, a string. The identifier is either "Human" or "Computer"
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::playerCardsOnHand(string playerIdentifier)
{
   cout <<  playerIdentifier + " cards on Hand: ";

   for (auto card : cardsOnHand)
   {
      cout << card.cardToString() + " ";
   }
   cout << endl;
}

// ****************************************************************
// Function Name: playerCardsOnPile
// Purpose: prints the current cards on the player's pile
// Parameter: playerIdentifier, a string. The identifier is either "Human" or "Computer"
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::playerCardsOnPile(string playerIdentifier)
{
   cout << playerIdentifier + " cards on Pile: ";

   for (auto card : cardsOnPile)
   {
      cout << card.cardToString() + " ";
   }
   cout << endl;
}

// ****************************************************************
// Function Name: getCardsOnPile
// Purpose: gets the current cards on the player's pile
// Parameter: none
// Return value: A vector of cards of the player's pile
// Assistance Received: none
// ****************************************************************
vector<Card> Player::getCardsOnPile() const
{
   return cardsOnPile;
}

// ****************************************************************
// Function Name: getCardsOnHand
// Purpose: gets the current cards on the player's hand
// Parameter: none
// Return value: A vector of cards of the player's hand
// Assistance Received: none
// ****************************************************************
vector<Card> Player::getCardsOnHand() const
{
   return cardsOnHand;
}

void Player::setCardsOnHand(vector<Card> cardSelected)
{
   cardsOnHand = cardSelected;
}

// ****************************************************************
// Function Name: makeNextMove
// Purpose: makes the next move in the game
// Parameter: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::makeNextMove()
{
}

// ****************************************************************
// Function Name: setPlayerScore
// Purpose: updates the score of the player
// Parameter: playerScore, an integer value. This score will be added 
//            to the player's total
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::setPlayerScore(int playerScore)
{
   score = playerScore;
}

// ****************************************************************
// Function Name: getPlayerScore
// Purpose: gets the score of the player
// Parameter: none
// Return value: The current score of the player
// Assistance Received: none
// ****************************************************************
int Player::getPlayerScore() const
{
   return score;
}

int Player::getFirstBuildScore() const
{
   return firstBuildScore;
}

// ****************************************************************
// Function Name: isCardOnHand
// Purpose: checks if the card selected by the player is in the player's hand
// Parameter: cardSelected, a string. The card selected by the player
// Return value: returns a boolean that checks if the player has the card in hand
// Assistance Received: none
// ****************************************************************
bool Player::isCardOnHand(string cardSelected) const
{
   for (auto card : getCardsOnHand())
   {
      if (card.cardToString() == cardSelected)
      {
         return true;
      }
   }
   return false;
}

// ****************************************************************
// Function Name: isCardOnPile
// Purpose: checks if the card selected by the player is in the player's pile
// Parameter: cardSelected, a string. The card selected by the player
// Return value: returns a boolean that checks if the player has the card in pile
// Assistance Received: none
// ****************************************************************
bool Player::isCardOnPile(string cardSelected) const
{
   for (auto card : getCardsOnPile())
   {
      if (card.cardToString() == cardSelected)
      {
         return true;
      }
   }
   return false;
}

bool Player::isCardOnTable(string cardSelected, vector<Card> cardsOnTable) const
{
   for (auto card : cardsOnTable)
   {
      if (card.cardToString() == cardSelected)
      {
         return true;
      }
   }
   return false;
}

bool Player::isDigit(string temp) const
{
   for (auto i : temp)
   {
      if (!isdigit(static_cast<unsigned char>(i))) { return false; }
   }
   return true;
}

string Player::getString(char x)
{
   string temp(1, x);
   return temp;
}

// ****************************************************************
// Function Name: cardScore
// Purpose: calculate the numerical equivalent of a card
// Parameters: tempCard, a string value of a card
// Return value: integer value, the numerical equivalent of a card
// Assistance Received: none
// ****************************************************************
int Player::cardScore(Card tempCard)
{
   //string face = getString(tempCard.at(1));
   string face = tempCard.getFace();

   if (face == "A") { return 1; }
   else if (face == "2") { return 2; }
   else if (face == "3") { return 3; }
   else if (face == "4") { return 4; }
   else if (face == "5") { return 5; }
   else if (face == "6") { return 6; }
   else if (face == "7") { return 7; }
   else if (face == "8") { return 8; }
   else if (face == "9") { return 9; }
   else if (face == "X") { return 10; }
   else if (face == "J") { return 11; }
   else if (face == "Q") { return 12; }
   else { return 13; }
   return 0;
}

int Player::calcLooseCardScore(vector<Card> looseCards)
{
   int score = 0;
   for (auto cards : looseCards)
   {
      score += cardScore(cards);
   }
   return score;
}

bool Player::makeSingleBuild(vector<Card>& tableCards)
{
   string cardSelectHand;
   string cardSelectTable;
   string combineTotalLooseCards;
   vector<Card> looseCardsSelected;

   int loopCount;

   cout << "From your hand, enter the card (eg. S3) that you want to make a build of: ";
   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));

   cout << "\nEnter the number of loose cards that you want to make a build of: ";
   do
   {
      cin >> combineTotalLooseCards;
   } while (!(isDigit(combineTotalLooseCards)));

   loopCount = stoi(combineTotalLooseCards);

   for (short int i = 0; i < loopCount; i++)
   {
      cout << "\nEnter the loose card to build with: ";
      do
      {
         cin >> cardSelectTable;
      } while (!(isCardOnTable(cardSelectTable, tableCards)));

      Card tempCard(getString(cardSelectTable[0]), getString(cardSelectTable[1]));
      looseCardsSelected.push_back(tempCard);
   }

   Card handSelCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));

   int handCardScore = cardScore(handSelCard);
   int looseCardsScore = calcLooseCardScore(looseCardsSelected);

   if (handCardScore == looseCardsScore)
   {
      initiateBuild(handSelCard, looseCardsSelected, handCardScore);
      playerCardsOnHand("Human");

      for (auto builtCards : looseCardsSelected)
      {
         tableCards.erase(remove(tableCards.begin(), tableCards.end(), builtCards), tableCards.end());
      }
   }
   else
   {
      cout << "Build values do not match. " << endl;
      return false;
   }
   return true;
}

bool Player::makeMultipleBuild(vector<Card>& tableCards)
{
   int previousBuildScore = getFirstBuildScore();

   string combineTotalLooseCards;
   string cardSelectTable;
   vector<Card> looseCardsSelected;

   int loopCount = 0;

   cout << "\nTo create multiple builds, make sure that your newest build score matches the " << endl;
   cout << "score of your prior builds. Also, make sure that you have the card on your hand" << endl;
   cout << "that matches the score of the multiple build." << endl;

   for (auto handCards : getCardsOnHand())
   {
      if (cardScore(handCards) != previousBuildScore)
      {
         cout << "Invalid. No card present on hand that matches previous build score." << endl;
         return false;
      }
   }

   cout << "\nEnter the number of loose cards for your newest multiple build: ";
   do
   {
      cin >> combineTotalLooseCards;
   } while (!(isDigit(combineTotalLooseCards)));

   loopCount = stoi(combineTotalLooseCards);

   for (short int i = 0; i < loopCount; i++)
   {
      cout << "\nEnter the loose card to build with: ";
      do
      {
         cin >> cardSelectTable;
      } while (!(isCardOnTable(cardSelectTable, tableCards)));

      Card tempCard(getString(cardSelectTable[0]), getString(cardSelectTable[1]));
      looseCardsSelected.push_back(tempCard);
   }

   int looseCardsScore = calcLooseCardScore(looseCardsSelected);

   if (previousBuildScore != looseCardsScore)
   {
      cout << "Newest build score does not match the previous score of " << previousBuildScore << endl;
      return false;
   }
   else
   {
      initiateMultipleBuild(looseCardsSelected);

      for (auto builtCards : looseCardsSelected)
      {
         tableCards.erase(remove(tableCards.begin(), tableCards.end(), builtCards), tableCards.end());
      }
   }
   return true;
}

bool Player::increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild)
{
   string cardSelectHand;
   string owner;
   vector<Card> oppnBuildCard;
   bool success = false;

   cout << "When extending an opponent's \"single\" build, ensure that you are holding" << endl; 
   cout << "a card equal to the extended sum." << endl;
   cout << "From your hand, enter the card (eg. S3) to increase opponent's build: ";
   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));

   tie(owner, oppnBuildCard) = oppoBuild;

   if (owner != "Computer")
   {
      cout << "Cannot increment your own build!" << endl;
      return false;
   }

   Card handSelCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));
   oppnBuildCard.push_back(handSelCard);

   for (auto handCard : getCardsOnHand())
   {
      if (cardScore(handCard) == calcLooseCardScore(oppnBuildCard))
      {
         cout << "Valid to increase opponent's build." << endl;

         singleBuildCard = make_tuple("Human", oppnBuildCard);
         vector<Card> empty{};
         oppoBuild = make_tuple("", empty);

         // As the player successfully increased the opponent's build, 
         // remove the card from the player's hand
         vector<Card> temp = getCardsOnHand();
         temp.erase(remove(temp.begin(), temp.end(), handCard), temp.end());
         setCardsOnHand(temp);
         success = true;
      }
   }
   return success;
}

void Player::initiateBuild(Card &handSelCard, vector<Card> &looseCardsSelected, int handCardScore)
{
   vector<Card> build;
   firstBuildScore = handCardScore;

   for (auto buildCard : looseCardsSelected)
   {
      build.push_back(buildCard);
   }

   singleBuildCard = make_tuple("Human", build);
   cout << "Build successful!" << endl;
}

void Player::initiateMultipleBuild(vector<Card>& looseCardsSelected)
{
   vector<Card> build;
   vector<Card> singleBuild;
   vector<vector<Card>> multipleBuild;

   string owner;

   for (auto buildCard : looseCardsSelected)
   {
      build.push_back(buildCard);
   }

   tie(owner, singleBuild) = singleBuildCard;

   multipleBuild.push_back(build);
   multipleBuild.push_back(singleBuild);

   multipleBuildCard = make_tuple(owner, multipleBuild);

   cout << "Multiple build successful!" << endl;
}

bool Player::captureCards(vector<Card>& tableCards)
{
   string cardSelectHand;
   char userInput;

   bool addSelHandCardOnce = true;
   bool captured = false;
   bool setCaptureSuccess = false;

   cout << "From your hand, enter the card (eg. S3) that you want to capture with loose cards: ";
   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));

   Card handSelCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));

   for (auto table : tableCards)
   {
      if (handSelCard.getFace() == table.getFace())
      {
         if (addSelHandCardOnce) { cardsOnPile.push_back(handSelCard); }
         cardsOnPile.push_back(table);

         tableCards.erase(remove(tableCards.begin(), tableCards.end(), table), tableCards.end());

         addSelHandCardOnce = false;
         captured = true;
      }
   }

   // At this point, individual cards have been captured
   // We now ask the user if they want to capture set of cards
   cout << "Do you want to capture set of cards (Y/N)?";
   do
   {
      cin >> userInput;
      userInput = toupper(userInput);
   } while (!(userInput == 'Y' || userInput == 'N'));

   if (userInput == 'N')
   {
      cout << "You opted not to capture a set of cards" << endl;
   }
   else
   {
      // User will now begin to capture set of cards
      setCaptureSuccess = captureSetCards(tableCards, handSelCard);
   }
   
   // After capturing of the set, we remove the card that was 
   // used to capture cards on the table from the player's hand
   if (captured)
   {
      vector<Card> temp = getCardsOnHand();
      temp.erase(remove(temp.begin(), temp.end(), handSelCard), temp.end());

      setCardsOnHand(temp);
      cout << "Card capture successful!" << endl;
   }

   // exit if there are no cards to capture
   if (!captured && !setCaptureSuccess)
   {
      return false;
   }
   return true;
 }

bool Player::captureSetCards(vector<Card>& tableCards, Card& handSelCard)
{
   string cardSelectHand;
   string combineTotalLooseCards;
   string totalSetCards;
   string cardSelectTable;
   vector<Card> looseCardsSelected;

   int setCaptureCount = 0, looseCaptureCount = 0;

   cout << "\nEnter the number of set of cards that you want to capture : ";
   do
   {
      cin >> totalSetCards;
   } while (!(isDigit(totalSetCards)));

   setCaptureCount = stoi(totalSetCards);

   for (short int i = 0; i < setCaptureCount; i++)
   {
      cout << "Enter the number of loose cards that you want to capture in set " << i << endl;      
      do
      {
         cin >> combineTotalLooseCards;
      } while (!(isDigit(combineTotalLooseCards)));
      looseCaptureCount = stoi(combineTotalLooseCards);

      for (short int j = 0; j < looseCaptureCount; j++)
      {
         cout << "\nEnter the loose card to capture as a set (eg. S3): ";
         do
         {
            cin >> cardSelectTable;
         } while (!(isCardOnTable(cardSelectTable, tableCards)));

         Card tempCard(getString(cardSelectTable[0]), getString(cardSelectTable[1]));
         looseCardsSelected.push_back(tempCard);
      }

      // check if the selected hand score can be used to capture a set of cards
      if (cardScore(handSelCard) != calcLooseCardScore(looseCardsSelected))
      {
         cout << "Invalid combination for set of cards." << endl;
         return false;
      }

      // Can successfully capture a set of cards
      // Add the cards to the pile of the player
      // After adding the card, remove the card from the table
      for (auto card : looseCardsSelected)
      {
         cardsOnPile.push_back(card);
         tableCards.erase(remove(tableCards.begin(), tableCards.end(), card), tableCards.end());
      }
   }
   // Capture of the set of cards has been successful
   return true;
}

void Player::removeCardsOnHand(Card& cardToRemove)
{
   vector<Card> temp = getCardsOnHand();

   temp.erase(remove(temp.begin(), temp.end(), cardToRemove), temp.end());
   setCardsOnHand(temp);
}