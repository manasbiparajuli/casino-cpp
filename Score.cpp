//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#include "Score.h"

Score::Score()
{
   this-> playerOneScore = 0;
   this-> playerTwoScore = 0;
}

Score::Score(vector<Card> playerOnePile, vector<Card> playerTwoPile)
{
   this->playerOneScore = 0;
   this->playerTwoScore = 0;
   this->playerOnePile = playerOnePile;
   this->playerTwoPile = playerTwoPile;
}

void Score::setPlayerOneScore(int score)
{
   playerOneScore += score;
}

void Score::setPlayerTwoScore(int score)
{
   playerTwoScore += score;
}

int Score::getPlayerOneScore() const
{
   return playerOneScore;
}

int Score::getPlayerTwoScore() const
{
   return playerTwoScore;
}

multimap<int, vector<Card>> Score::getBuildComb() const
{
   return buildComb;
}

void Score::calculateMostCards()
{
   int plOneTotal = static_cast<int> (playerOnePile.size());
   int plTwoTotal = static_cast<int> (playerTwoPile.size());

   cout << "Human has    " << plOneTotal << " cards." << endl;
   cout << "Computer has " << plTwoTotal << " cards." << endl;

   if (plOneTotal > plTwoTotal) { setPlayerOneScore(3); }
   else if (plOneTotal < plTwoTotal) { setPlayerTwoScore(3); }
}

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

   if (!plOneHas10OfDiamonds) { setPlayerTwoScore(2); }
}

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

   if (!plOneHas2OfSpades) { setPlayerTwoScore(1); }
}

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

void Score::calculateTotalScore()
{
   calculateMostCards();
   calculateMostSpades();
   calculate10OfDiamonds();
   calculate2OfSpades();
   calculatePerAce();
}

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

int Score::calcBuildScore(const vector<Card> buildCards)
{
   int score = 0;
   for (auto cards : buildCards)
   {
      score += cardScore(cards);
   }
   return score;
}

vector<string> Score::powerSet(int tableSize)
{
   vector <string> validSets;
   vector<char> temp;
   vector<string> totalSets;

   vector<int> index = {};

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

   // Get only the combinations that we can form a pair with
   // We want pairs of cards, not a single card
   for (auto a : totalSets)
   {
      if (a.size() > 1)
      {
         validSets.push_back(a);
      }
   }
   return validSets;
}

void Score::buildScoreMap(vector<string>& powerSets, const vector<Card>& tableCards)
{
   int buildCombiScore = 0;
   vector<Card> buildCards;
   int buildIndex;

   for (auto build : powerSets)
   {
      buildCards = {};
      buildCombiScore = 0;

      for (char& c : build)
      {
         buildIndex = c - '0';
         buildCards.push_back(tableCards[buildIndex]);
      }

      buildCombiScore = calcBuildScore(buildCards);
      buildComb.insert(make_pair(buildCombiScore, buildCards));
   }
}

void Score::printBuildMap(multimap<int, vector<Card>> map)
{
   multimap <int, vector<Card>> ::iterator itr;

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

Score::~Score()
{
}
