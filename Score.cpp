//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#include "Score.h"

// ****************************************************************
// Function Name: Score
// Purpose: default constructor for Score class 
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Score::Score()
{
   this-> playerOneScore = 0;
   this-> playerTwoScore = 0;
}

// ****************************************************************
// Function Name: Score
// Purpose: default constructor for Score class that takes in the pile cards of the 
//          players and calculates the score
// Parameters: playerOnePile, a vector Card object. The cards in pile of the first player
//             playerTwoPile, a vector Card object. The cards in pile of the second player
// Return value: none
// Assistance Received: none
// ****************************************************************
Score::Score(vector<Card> playerOnePile, vector<Card> playerTwoPile)
{
   this->playerOneScore = 0;
   this->playerTwoScore = 0;
   this->playerOnePile = playerOnePile;
   this->playerTwoPile = playerTwoPile;
}

// ****************************************************************
// Function Name: setPlayerOneScore
// Purpose: updates the score of player one
// Parameter: score, an integer value. This score will be added 
//            to the player's total
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::setPlayerOneScore(int score)
{
   playerOneScore += score;
}

// ****************************************************************
// Function Name: setPlayerTwoScore
// Purpose: updates the score of player two
// Parameter: score, an integer value. This score will be added 
//            to the player's total
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::setPlayerTwoScore(int score)
{
   playerTwoScore += score;

}

// ****************************************************************
// Function Name: getPlayerOneScore
// Purpose: gets the score of player one
// Parameter: none
// Return value: The current score of the player one
// Assistance Received: none
// ****************************************************************
int Score::getPlayerOneScore() const
{
   return playerOneScore;
}

// ****************************************************************
// Function Name: getPlayerTwoScore
// Purpose: gets the score of player two
// Parameter: none
// Return value: The current score of player two
// Assistance Received: none
// ****************************************************************
int Score::getPlayerTwoScore() const
{
   return playerTwoScore;
}

// ****************************************************************
// Function Name: getBuildComb
// Purpose: gets the map of the possible build and corresponding scores
// Parameter: none
// Return value: map of possible build and corresponding scores
// Assistance Received: none
// ****************************************************************
multimap<int, vector<Card>> Score::getBuildComb() const
{
   return buildComb;
}

// ****************************************************************
// Function Name: calculateMostCards
// Purpose: sets the scores of the player with the most number of cards in pile
// Parameter : none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::calculateMostCards()
{
   int plOneTotal = static_cast<int> (playerOnePile.size());
   int plTwoTotal = static_cast<int> (playerTwoPile.size());

   cout << "Human has    " << plOneTotal << " cards." << endl;
   cout << "Computer has " << plTwoTotal << " cards." << endl;

   // Player with most cards gets a score of 3
   if (plOneTotal > plTwoTotal) { setPlayerOneScore(3); }
   else if (plOneTotal < plTwoTotal) { setPlayerTwoScore(3); }
}

// ****************************************************************
// Function Name: calculateMostSpades
// Purpose: sets the scores of the player with the most number of spades in pile
// Parameter : none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::calculateMostSpades()
{
   int plOneTotal = 0;
   int plTwoTotal = 0;

   for (auto card : playerOnePile)
   {
      if (card.getSuit() == "S") { plOneTotal++; }
   }

   for (auto card : playerTwoPile)
   {
      if (card.getSuit() == "S") { plTwoTotal++; }
   }

   cout << "Human has    " << plOneTotal << " spades." << endl;
   cout << "Computer has " << plTwoTotal << " spades." << endl;

   if (plOneTotal > plTwoTotal) { setPlayerOneScore(1); }
   else if (plOneTotal < plTwoTotal) { setPlayerTwoScore(1); }
}

// ****************************************************************
// Function Name: calculate10OfDiamonds
// Purpose: sets the score of the player with 10 of Diamonds a value of 2
// Parameter : none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::calculate10OfDiamonds()
{
   bool plOneHas10OfDiamonds = false;

   for (auto card : playerOnePile)
   {
      if (card.cardToString() == "DX") 
      { 
         plOneHas10OfDiamonds = true;
         setPlayerOneScore(2);
         break;
      }
   }
   if (plOneHas10OfDiamonds == false) { setPlayerTwoScore(2); }
}

// ****************************************************************
// Function Name: calculate2OfSpades
// Purpose: sets the score of the player with 2 of Spades a value of 1
// Parameter : none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::calculate2OfSpades()
{
   bool plOneHas2OfSpades = false;

   for (auto card : playerOnePile)
   {
      if (card.cardToString() == "S2")
      {
         plOneHas2OfSpades = true;
         setPlayerOneScore(1);
         break;
      }
   }
   if (plOneHas2OfSpades == false) { setPlayerTwoScore(1); }
}

// ****************************************************************
// Function Name: calculatePerAce
// Purpose: adds a score to every Ace card that a player has in pile
// Parameter : none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::calculatePerAce()
{
   int plOneTotal = 0;
   int plTwoTotal = 0;

   for (auto card : playerOnePile)
   {
      if (card.getSuit() == "A") { plOneTotal++; }
   }

   for (auto card : playerTwoPile)
   {
      if (card.getSuit() == "A") { plTwoTotal++; }
   }

   setPlayerOneScore(plOneTotal);
   setPlayerTwoScore(plTwoTotal);
}

// ****************************************************************
// Function Name: calculateTotalScore
// Purpose: calculates the total score of the player by applying the scoring rules
// Parameter : none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::calculateTotalScore()
{
   calculateMostCards();
   calculateMostSpades();
   calculate10OfDiamonds();
   calculate2OfSpades();
   calculatePerAce();
}

// ****************************************************************
// Function Name: cardScore
// Purpose: calculate the numerical equivalent of a card
// Parameters: tempCard, a string value of a card
// Return value: integer value, the numerical equivalent of a card
// Assistance Received: none
// ****************************************************************
int Score::cardScore(Card tempCard)
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
// Function Name: calcBuildScore
// Purpose: calculate the score of the build
// Parameters: buildCards, a vector of strings. It holds the build combination.
// Return value: integer value, the score of the build
// Assistance Received: none
// ****************************************************************
int Score::calcBuildScore(const vector<Card> buildCards)
{
   int score = 0;
   // Go through the build and add the score of each of the cards
   for (auto cards : buildCards)
   {
      score += cardScore(cards);
   }
   return score;
}

// ****************************************************************
// Function Name: powerSet
// Purpose: calculate the power set based on the size of the table
// Parameters: tableSize, an integer value. It holds the size of the table
// Return value: a vector of string that lists all the possible valid power sets
// Assistance Received: none
// ****************************************************************
vector<string> Score::powerSet(int tableSize)
{
   // the power set that will be used to create a map of possible scores
   vector <string> validSets;

   // all the power sets possible
   vector<char> temp;
   vector<string> totalSets;

   vector<int> index = {};

   // input numbers into the vector that will be used to create the possible power set 
   for (int i = 0; i < tableSize; i++)
   {
      index.push_back('0' + i);
   }

   // total number of power set elements possible   
   int N = static_cast<int> (pow(2, tableSize));

   // generate each subset one by one
   for (int i = 0; i < N; i++)
   {
      temp = {};
      // check every bit of i
      for (int j = 0; j < tableSize; j++)
      {
         // if jth bit of i set, print index[j]
         if (i & (1 << j))
         {
            temp.push_back(index[j]);
         }
      }
      // convert the possible combination into a string and push into vector string
      string comb(temp.begin(), temp.end());
      totalSets.push_back(comb);
   }

   // Get only the combinations that has more than one card as we don't form a build with only a single card
   for (auto a : totalSets)
   {
      if (a.size() > 1)
      {
         validSets.push_back(a);
      }
   }
   return validSets;
}

// ****************************************************************
// Function Name: buildScoreMap
// Purpose: constructs a map of possible builds with the current table cards corresponding to 
//          the build score
// Parameters: -> powerSets, a vector of string. It holds the possible power set combinations that 
//                      can be formed using the current cards in the table.
//             -> tableCards, a vector of cards. It holds the current table cards.
//       
//       Both parameters have been passed by reference.
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::buildScoreMap(vector<string>& powerSets, const vector<Card>& tableCards)
{
   // the build combination score 
   int buildCombiScore = 0;

   // the combination of cards for the build
   vector<Card> buildCards;

   // the integer representation of index that was converted from a character
   int buildIndex;

   // map the generated power set to the repective indices of cards in the table
   for (auto build : powerSets)
   {
      buildCards = {};
      buildCombiScore = 0;

      for (char& c : build)
      {
         buildIndex = c - '0';
         buildCards.push_back(tableCards[buildIndex]);
      }

      // calculate the build score and insert into the map as a pair
      buildCombiScore = calcBuildScore(buildCards);
      buildComb.insert(make_pair(buildCombiScore, buildCards));
   }
}

// ****************************************************************
// Function Name: printBuildMap
// Purpose: prints the map of the build and its corresponding score
// Parameters: map, a multimap of integer and vector of Cards
// Return value: none
// Assistance Received: none
// ****************************************************************
void Score::printBuildMap(multimap<int, vector<Card>> map)
{
   multimap <int, vector<Card>> ::iterator itr;

   // print the score combination of the generated possible build
   for (itr = map.begin(); itr != map.end(); ++itr)
   {
      cout << "Score: " << itr->first;
      cout << "\t";

      for (auto a : itr->second)
      {
         cout << a.cardToString() << " ";
      }
      cout << endl;
   }
}

// ****************************************************************
// Function Name: ~Score
// Purpose: destructor for Score class 
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Score::~Score()
{
}