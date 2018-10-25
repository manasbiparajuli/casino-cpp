//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#include "Player.h"

// ****************************************************************
// Function Name: Player
// Purpose: serves as a default constructor for Player Class
// Parameters: name, the name of the player
// Return value: none
// Assistance Received: none
// ****************************************************************
Player::Player(string name = "") : playerName(name)
{
   score = 0;
   firstBuildScore = 0;
   vector<Card> temp = {};
   singleBuildCard = make_tuple("", temp);

   cardsOnPile = {};
   cardsOnHand = {};

   vector<vector<Card>> temp2 = {};
   multipleBuildCard = make_tuple("", temp2);
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
// Function Name: addCardsToPile
// Purpose: adds cards to the players' pile
// Parameters: card, a Card object. It holds the current card to be added.
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::addCardsToPile(Card card)
{
   cardsOnPile.push_back(card);
}

// ****************************************************************
// Function Name: playerCardsOnHand
// Purpose: prints the current cards on the player's hand
// Parameter: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::printCardsOnHand()
{
   cout << getPlayerName() + " cards on Hand: ";

   for (auto card : getCardsOnHand())
   {
      cout << card.cardToString() + " ";
   }
   cout << endl;
}

// ****************************************************************
// Function Name: playerCardsOnPile
// Purpose: prints the current cards on the player's pile
// Parameter: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::printCardsOnPile()
{
   cout << getPlayerName() + " cards on Pile: ";

   for (auto card : getCardsOnPile())
   {
      cout << card.cardToString() + " ";
   }
   cout << endl;
}

// ****************************************************************
// Function Name: printSingleBuild
// Purpose: prints the single build of the players
// Parameter: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::printSingleBuild()
{
   vector<Card> build;

   // unpack the single build tuple and print the cards
   tie(ignore, build) = singleBuildCard;
   
   // print the single build if it exists
   if (isSingleBuildExist() == true)
   {
      cout << " [";
      for (auto cards : build)
      {
         cout << cards.cardToString() << " ";
      }
      cout << "]";
   }
}

// ****************************************************************
// Function Name: printMultipleBuild
// Purpose: prints the multiple build of the players
// Parameter: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::printMultipleBuild()
{
   vector<vector<Card>> multiBuild;

   // unpack the multiple build tuple and print the code
   tie(ignore, multiBuild) = multipleBuildCard;

   // print the multiple build if it exists
   if (isMultipleBuildExist() == true)
   {
      cout << " [ ";

      for (auto builds : multiBuild)
      {
         cout << "[";

         for (auto cards : builds)
         {
            cout << cards.cardToString() << " ";
         }
         cout << "]";
      }
      cout << " ]";
   }
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

// ****************************************************************
// Function Name: setCardsOnHand
// Purpose: sets the current cards on the player's hand
// Parameter: cardSelected, a vector of Cards. Holds the new hand cards for the player
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::setCardsOnHand(vector<Card> cardSelected)
{
   cardsOnHand.assign(cardSelected.begin(), cardSelected.end());
}

// ****************************************************************
// Function Name: setCardsOnPile
// Purpose: sets the current cards on the player's pile
// Parameter: cardSelected, a vector of Cards. Holds the new pile cards for the player
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::setCardsOnPile(vector<Card> cardSelected)
{
   cardsOnPile = cardSelected;
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

// ****************************************************************
// Function Name: getFirstBuildScore
// Purpose: gets the first build score of the player
// Parameter: none
// Return value: The current score of the player's valid build
// Assistance Received: none
// ****************************************************************
int Player::getFirstBuildScore() const
{
   return firstBuildScore;
}

// ****************************************************************
// Function Name: setFirstBuildScore
// Purpose: sets the first build score of the player
// Parameter: score, an integer value. The score of the valid build. 
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::setFirstBuildScore(int score)
{
   firstBuildScore = score;
}

// ****************************************************************
// Function Name: getPlayerName
// Purpose: gets the name of the player
// Parameter: none
// Return value: The current name of the player
// Assistance Received: none
// ****************************************************************
string Player::getPlayerName() const
{
   return playerName;
}

// ****************************************************************
// Function Name: getSingleBuild
// Purpose: gets the successful single build of the player
// Parameter: none
// Return value: a tuple of owner as string and single build as vector of cards
// Assistance Received: none
// ****************************************************************
tuple<string, vector<Card>> Player::getSingleBuild() const 
{
   return singleBuildCard;
}

// ****************************************************************
// Function Name: setSingleBuild
// Purpose: sets the successful single build of the player
// Parameter: build, a tuple of owner as string and single build as vector of cards
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::setSingleBuild(tuple<string, vector<Card>> build)
{
   singleBuildCard = build;
}

// ****************************************************************
// Function Name: getMultipleBuild
// Purpose: gets the successful multiple build of the player
// Parameter: none
// Return value: a tuple of owner as string and multiple builds as vector of vector of cards
// Assistance Received: none
// ****************************************************************
tuple<string, vector<vector<Card>>> Player::getMultipleBuild() const
{
   return multipleBuildCard;
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

// ****************************************************************
// Function Name: isCardOnTable
// Purpose: checks if the card selected by the player is in the table
// Parameter: cardSelected, a string. The card selected by the player
//            cardsOnTable, a vector of cards. The ongoing cards on the table
// Return value: returns a boolean that checks if the card is on table
// Assistance Received: none
// ****************************************************************
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

// ****************************************************************
// Function Name: isDigit
// Purpose: checks if all the characters in a string are digits
// Parameters: temp, a string.
// Return value: a boolean that returns if a string is entirely composed of digits
// Assistance Received: none
// ****************************************************************
bool Player::isDigit(string temp) const
{
   for (auto i : temp)
   {
      if (!isdigit(static_cast<unsigned char>(i))) { return false; }
   }
   return true;
}

// ****************************************************************
// Function Name: isMultipleBuildExist
// Purpose: checks if the player has a multiple build
// Parameters: none
// Return value: a boolean that returns if a player has a multiple build
// Assistance Received: none
// ****************************************************************
bool Player::isMultipleBuildExist() const
{
   vector<vector<Card>> multipleBuild;
   
   //unpack the multiple build tuple
   tie(ignore, multipleBuild) = multipleBuildCard;

   // check if multi build contains a vector of single builds
   if (multipleBuild.size() >= 1)
   {
      return true;
   }
   return false;
}

// ****************************************************************
// Function Name: isSingleBuildExist
// Purpose: checks if the player has a single build
// Parameters: none
// Return value: a boolean that returns if a player has a single build
// Assistance Received: none
// ****************************************************************
bool Player::isSingleBuildExist() const
{
   vector<Card> singleBuild;

   // unpack the singleBuild tuple
   tie(ignore, singleBuild) = singleBuildCard;

   // check if the vector of cards is empty or not
   if (singleBuild.size() >= 1)
   {
      return true;
   }
   return false;
}

// ****************************************************************
// Function Name: hasCapturedCard
// Purpose: checks if the player has captured any cards in current move
// Parameters: none
// Return value: a boolean that returns if a player captured any cards 
//                in the current move
// Assistance Received: none
// ****************************************************************
bool Player::hasCapturedCard() const
{
   return hasCapturedInCurMove;
}

// ****************************************************************
// Function Name: getString
// Purpose: converts a character into a string
// Parameters: x, a character. Holds any character that needs conversion to string
// Return value: the string representation of the character
// Assistance Received: none
// ****************************************************************
string Player::getString(char x)
{
   string temp(1, x);
   return temp;
}

// ****************************************************************
// Function Name: calcSingleCardScore
// Purpose: calculate the numerical equivalent of a card
// Parameters: tempCard, a string value of a card
// Return value: integer value, the numerical equivalent of a card
// Assistance Received: none
// ****************************************************************
int Player::calcSingleCardScore(Card tempCard)
{
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

// ****************************************************************
// Function Name: calcLooseCardScore
// Purpose: calculates the total score of a vector of cards
// Parameters: looseCards, a vector of cards. Holds the cards whose 
//                   score needs to be determined
// Return value: integer value, the score of the total cards
// Assistance Received: none
// ****************************************************************
int Player::calcLooseCardScore(vector<Card> looseCards)
{
   int score = 0;
   for (auto cards : looseCards)
   {
      score += calcSingleCardScore(cards);
   }
   return score;
}

// ****************************************************************
// Function Name: removeCardFromHand
// Purpose: remove the card from hand
// Parameters: cardToRemove, a card object that needs to be 
//                   removed from player's hand
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::removeCardFromHand(Card& cardToRemove)
{
   vector<Card> temp = getCardsOnHand();

   // find and remove the selected card from the table
   temp.erase(remove(temp.begin(), temp.end(), cardToRemove), temp.end());

   // set the modified card on the hand
   setCardsOnHand(temp);
}

// ****************************************************************
// Function Name: removeCardFromTable
// Purpose: remove the group of cards from table
// Parameters: tableCards, a vector of cards. Holds the cards that are
//                   in the table.
//             looseCards, a vector of cards that need to be 
//                   removed from the table
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::removeCardsFromTable(vector<Card>& tableCards, vector<Card> looseCards)
{
   // remove the selected group of cards from the table
   for (auto builtCards : looseCards)
   {
      tableCards.erase(remove(tableCards.begin(), tableCards.end(), builtCards), tableCards.end());
   }
}

// ****************************************************************
// Function Name: findCommonCard
// Purpose: finds the card in common with the player's hand
// Parameters: matchedTableCards, a vector of cards. Holds the cards that were
//                   used to perform an action in the current move.
// Return value: a card object. Returns the card that was in common with the set of matched cards
// Assistance Received: none
// ****************************************************************
Card Player::findCommonCard(const vector<Card>& matchedTableCards)
{
   // loop through the cards in the player's hand to check if any card
   // is contained in one of the built table cards
   for (auto handCard : getCardsOnHand())
   {
      // return the card if found
      if (find(matchedTableCards.begin(), matchedTableCards.end(), handCard) != matchedTableCards.end())
      {
         return handCard;
      }
   }
   return Card();
}

// ****************************************************************
// Function Name: ~Player
// Purpose: destructor for Player class 
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Player::~Player()
{
}