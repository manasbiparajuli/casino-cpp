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
Player::Player(string name = ""):playerName(name)
{
   score = 0;
   firstBuildScore = 0;
   vector<Card> temp = {};
   singleBuildCard = make_tuple("", temp);
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

void Player::addCardsToPile(Card card)
{
   cardsOnPile.push_back(card);
}

// ****************************************************************
// Function Name: playerCardsOnHand
// Purpose: prints the current cards on the player's hand
// Parameter: playerIdentifier, a string. The identifier is either "Human" or "Computer"
// Return value: none
// Assistance Received: none
// ****************************************************************
void Player::printCardsOnHand()
{
   cout << getPlayerName() + " cards on Hand: ";

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
void Player::printCardsOnPile()
{
   cout << getPlayerName() + " cards on Pile: ";

   for (auto card : cardsOnPile)
   {
      cout << card.cardToString() + " ";
   }
   cout << endl;
}

void Player::printSingleBuild()
{
   vector<Card> build;
   tie(ignore, build) = singleBuildCard;
   
   if (isSingleBuildExist() == true)
   {
      cout << " [";
      for (auto cards : build)
      {
         cout << cards.cardToString() << " ";
      }
      cout << "]";
      cout << endl;
   }
}

void Player::printMultipleBuild()
{
   vector<vector<Card>> multiBuild;
   tie(ignore, multiBuild) = multipleBuildCard;

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

void Player::setCardsOnHand(vector<Card> cardSelected)
{
   cardsOnHand = cardSelected;
}

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

int Player::getFirstBuildScore() const
{
   return firstBuildScore;
}

void Player::setFirstBuildScore(int score)
{
   firstBuildScore = score;
}

string Player::getPlayerName() const
{
   return playerName;
}

tuple<string, vector<Card>> Player::getSingleBuild() const 
{
   return singleBuildCard;
}

void Player::setSingleBuild(tuple<string, vector<Card>> build)
{
   singleBuildCard = build;
}

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

bool Player::hasCapturedCard() const
{
   return hasCapturedInCurMove;
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

int Player::calcLooseCardScore(vector<Card> looseCards)
{
   int score = 0;
   for (auto cards : looseCards)
   {
      score += calcSingleCardScore(cards);
   }
   return score;
}

void Player::removeCardFromHand(Card& cardToRemove)
{
   vector<Card> temp = getCardsOnHand();

   temp.erase(remove(temp.begin(), temp.end(), cardToRemove), temp.end());
   setCardsOnHand(temp);
}

void Player::removeCardsFromTable(vector<Card>& tableCards, vector<Card> looseCards)
{
   for (auto builtCards : looseCards)
   {
      tableCards.erase(remove(tableCards.begin(), tableCards.end(), builtCards), tableCards.end());
   }
}

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

Player::~Player()
{
}
