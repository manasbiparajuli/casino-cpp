//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#include "Computer.h"

void Computer::play(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild)
{
   // Order in which computer will make a move
   // 1) Increase opponent's build
   // 2) Make multiple builds
   // 3) Make single build
   // 4) Capture cards (both as a set or individual cards)
   // 5) Trail card

   // flag for when computer suceessfully makes a move
   bool moveSuccess = false;

   // Make moves respectively. Return from the function if successful as a player can only make one move.

   moveSuccess = increaseOpponentBuild(tableCards, oppoBuild);
   if (moveSuccess == true) { hasCapturedInCurMove = false; return; }

   moveSuccess = makeMultipleBuild(tableCards);
   if (moveSuccess == true) { hasCapturedInCurMove = false; return; }

   moveSuccess = makeSingleBuild(tableCards);
   if (moveSuccess == true) { hasCapturedInCurMove = false; return; }

   moveSuccess = captureCards(tableCards);
   if (moveSuccess == true) { hasCapturedInCurMove = true; return; }

   moveSuccess = trailCard(tableCards);
   if (moveSuccess == true) { hasCapturedInCurMove = false; return; }
}

bool Computer::makeSingleBuild(vector<Card>& tableCards)
{
   // ensure that we check all the possible keys before we return
   bool singleBuildPossible = false;

   // the valid build cards used to make a single build
   vector<Card> matchedTableCards;

   // player cannot make a build if there are less than two cards in their hand
   if (getCardsOnHand().size() < 2) { return false; }

   // Temporarily add a card to table to check if a build is possible
   for (auto handCardToBuildWith : getCardsOnHand())
   {
      // add card from hand temporarily to check if computer can make a build using this card
      tableCards.push_back(handCardToBuildWith);

      // enlist the possible power sets based on tableSize
      vector<string> buildComb = score.powerSet(static_cast<int> (tableCards.size()));

      // make a map of the scores possible from valid builds
      score.buildScoreMap(buildComb, tableCards);

      // get the map of <BuildScores, BuildCombination>
      auto map = score.getBuildComb();

      // Loop through the hand cards to check if a card score matches the key in map
      for (auto handCard : getCardsOnHand())
      {
         // calculate the hand card score for each card
         int handCardScore = calcSingleCardScore(handCard);

         // iterate through the map and check if the key matches the handCardScore
         for (auto itr = map.begin(); itr != map.end(); itr++)
         {
            // match found
            if (itr->first == handCardScore)
            {
               setFirstBuildScore(handCardScore);
               singleBuildPossible = true;
               matchedTableCards = itr->second;
            }
         }
      }
      // remove the card from the table that we temporarily added to get possible build combinations
      tableCards.erase(remove(tableCards.begin(), tableCards.end(), handCardToBuildWith), tableCards.end());
   }

   // Since hand card score matched the key in map at least once, we return true
   if (singleBuildPossible) 
   { 
      singleBuildCard = make_tuple(getPlayerName(), matchedTableCards);
      
      // remove cards that made up build successfully from the table
      removeCardsFromTable(tableCards, matchedTableCards);

      cout << "Computer's single build successful" << endl;
      return true; 
   }
   // no matching keys found
   return false;
}

bool Computer::makeMultipleBuild(vector<Card>& tableCards)
{
   // get the build score of last successful single build 
   int previousBuildScore = getFirstBuildScore();

   // flag if there does not exist a card in hand that matches the previous single build score
   bool buildScoreMismatch = false;

   // ensure that we check all the possible keys before we return
   bool multipleBuildPossible = false;

   // the valid build cards used to make a multiple build
   vector<Card> matchedTableCards;

   // player cannot make a multibuild if there are less than two cards in their hand
   if (getCardsOnHand().size() < 2) { return false; }

   // multibuild is not possible if the player does not have a single build already
   if (isSingleBuildExist() == false) { return false; }

   for (auto handCards : getCardsOnHand())
   {
      // check if we have a card in hand that matches score of previous single build score
      if (calcSingleCardScore(handCards) != previousBuildScore)
      {
         buildScoreMismatch = true;
      }
      // if found, break from the loop
      else
      {
         buildScoreMismatch = false;
         break;
      }
   }

   // if there are no cards to match the previous build score, then return from the function
   if (buildScoreMismatch) { return false; }
   
   //////////
   // We now repeat the steps that we took to build a single build
   //////////

   // Temporarily add a card to table to check if a build is possible
   for (auto handCardToBuildWith : getCardsOnHand())
   {
      // add card from hand temporarily to check if computer can make a build using this card
      tableCards.push_back(handCardToBuildWith);

      // enlist the possible power sets based on tableSize
      vector<string> buildComb = score.powerSet(static_cast<int> (tableCards.size()));

      // make a map of the scores possible from valid builds
      score.buildScoreMap(buildComb, tableCards);

      // get the map of <BuildScores, BuildCombination>
      auto map = score.getBuildComb();

      // Loop through the hand cards to check if a card score equivalent to 
      // previous build score matches a key in map
      for (auto handCard : getCardsOnHand())
      {
         // calculate the hand card score for each card
         int handCardScore = calcSingleCardScore(handCard);

         // only traverse through map if the hand card score is equal to the previous build score
         if (handCardScore == previousBuildScore)
         {
            // iterate through the map and check if the key matches the handCardScore
            for (auto itr = map.begin(); itr != map.end(); itr++)
            {
               // match found
               if (itr->first == handCardScore)
               {
                  multipleBuildPossible = true;
                  matchedTableCards = itr->second;
               }
            }
         }
      }
      // remove the card from the table that we temporarily added to get possible build combinations
      tableCards.erase(remove(tableCards.begin(), tableCards.end(), handCardToBuildWith), tableCards.end());
   }

   // Since hand card score matched the key in map at least once, we return true
   if (multipleBuildPossible)
   {
      initiateMultipleBuild(matchedTableCards);

      // remove cards that made up build successfully from the table
      removeCardsFromTable(tableCards, matchedTableCards);

      cout << "Computer's multiple build successful" << endl;
      return true; 
   }
   return false;
}

bool Computer::increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild)
{
   // owner of the build
   string owner;

   // cards in the build of the opponent
   vector<Card> oppnBuildCard;

   // unpack the tuple and store the owner of the build and the cards present in the build
   tie(owner, oppnBuildCard) = oppoBuild;

   // return false if the build is not owned by the player or if the opponent's build is empty
   if (owner == getPlayerName() || (oppnBuildCard.size() == 0))
   {
      cout << "Computer cannot increment its own build!" << endl;
      return false;
   }

   // player cannot increase an opponent's build if there are less than two cards in their hand
   if (getCardsOnHand().size() < 2) { return false; }

   // temporarily add cards to the opponent's build and loop through the cards in the hand
   // to check if there exists a hand card that will match the score of the extended build
   for (auto handCardToIncrease : getCardsOnHand())
   {
      // add card from hand temporarily to check if computer can increase opponent's build using this card
      oppnBuildCard.push_back(handCardToIncrease);

      for (auto handCard : getCardsOnHand())
      {
         // check if there is any card on hand that matches the score of the new extended build
         if (calcSingleCardScore(handCard) == calcLooseCardScore(oppnBuildCard))
         {
            // if increasing opponent's build is valid, own the new extended build and remove 
            // ownership of the opponent's build 
            singleBuildCard = make_tuple(getPlayerName(), oppnBuildCard);
            vector<Card> empty{};
            oppoBuild = make_tuple("", empty);
            removeCardFromHand(handCardToIncrease);

            cout << "Computer has increased the build of its opponent." << endl;
            return true;
         }
      }
      // remove the card from the opponent's build that we temporarily added to check if we can increase the build or not
      oppnBuildCard.erase(remove(oppnBuildCard.begin(), oppnBuildCard.end(), handCardToIncrease), oppnBuildCard.end());
   }
   return false;
}

void Computer::initiateMultipleBuild(vector<Card>& looseCardsSelected)
{
   // owner of the single build
   string owner;

   // cards in the single build
   vector<Card> singleBuild;

   // store multiple build card values
   vector<vector<Card>> multipleBuild;

   // unpack the tuple 
   tie(owner, singleBuild) = singleBuildCard;

   // push the newest build into multiple build
   multipleBuild.push_back(looseCardsSelected);

   // push the previous single build into multiple build
   multipleBuild.push_back(singleBuild);

   // create a tuple for the multiple build
   multipleBuildCard = make_tuple(owner, multipleBuild);

   cout << "Computer's multibuild successful" << endl;
}

bool Computer::captureCards(vector<Card>& tableCards)
{
   for (auto handCard : getCardsOnHand())
   {
      // If we capture either multiple build or single bulid, then we return from the function
      // because we cannot use the hand card to capture loose or set of cards as they are not 
      // part of the build
      if (calcSingleCardScore(handCard) == getFirstBuildScore())
      {
         // capture multiple builds, if there exist a matching card in the player's hand
         if (isMultipleBuildExist() == true)
         {
            // store the multiple builds
            vector<vector<Card>> multipleBuild;

            // unpack the tuple to get a list of Cards in the multiple build
            tie(ignore, multipleBuild) = multipleBuildCard;

            // loop through the builds stored in the multibuild
            for (auto parsedBuild : multipleBuild)
            {
               // push the cards of the single build into the player's pile
               for (auto buildCards : parsedBuild)
               {
                  cardsOnPile.push_back(buildCards);
               }
            }
            // push the hand card into the player's pile and remove it from player's hand
            cardsOnPile.push_back(handCard);
            removeCardFromHand(handCard);
            return true;
         }
         // capture single build
         else if (isSingleBuildExist() == true)
         {
            // store the single build
            vector<Card> singleBuild;

            // unpack te tuple to get the single build
            tie(ignore, singleBuild) = singleBuildCard;

            // push the cards in the single build into the player's pile
            for (auto buildCards : singleBuild)
            {
               cardsOnPile.push_back(buildCards);
            }
            // push the hand card into the player's pile and remove it from player's hand
            cardsOnPile.push_back(handCard);
            removeCardFromHand(handCard);
            return true;
         }
      }

      // Since there are no cards on hand that matches the score of the builds, we move
      // to capture set of cards or loose cards from the table
      else
      {
         // flag that sets if capturing set of cards was possible
         bool captureSetSuccess = captureSetCards(tableCards, handCard);
        
         // if we captured set of cards, then return true from the function
         if (captureSetSuccess) 
         { 
            return true; 
         }
      }
   }
   // not possible to capture any cards from builds or as set of cards
   return false;
}

bool Computer::captureSetCards(vector<Card>& tableCards, Card & handSelCard)
{
   // ensure that we check all the possible keys before we return
   bool setPossible = false;

   // the valid build cards used to make a set
   vector<Card> matchedTableCards;

   // enlist the possible power sets based on tableSize
   vector<string> buildComb = score.powerSet(static_cast<int> (tableCards.size()));

   // make a map of the scores possible from valid builds
   score.buildScoreMap(buildComb, tableCards);

   // get the map of <BuildScores, BuildCombination>
   auto map = score.getBuildComb();

   // calculate the hand card score
   int handCardScore = calcSingleCardScore(handSelCard);

   // iterate through the map and check if the key matches the handCardScore
   for (auto itr = map.begin(); itr != map.end(); itr++)
   {
      // match found
      if (itr->first == handCardScore)
      {
         setPossible = true;
         
         // add the possible set of cards to the player's pile
         // also, add the cards temporarily to a vector of cards to remove 
         // them from the table after capturing is done
         for (auto match : itr->second)
         {
            cardsOnPile.push_back(match);
            matchedTableCards.push_back(match);
         }
      }
   }

   // Add any single card from the table that matches the score of the current card in player's hand
   for (auto tableCard : tableCards)
   {
      if (calcSingleCardScore(tableCard) == handCardScore)
      {
         cardsOnPile.push_back(tableCard);
         matchedTableCards.push_back(tableCard);
         setPossible = true;
      }
   }

   // if capturing of sets was possible, then remove the captured cards from the table 
   // and the card that was used to capture from player's hand
   // Then, return true from the function
   if (setPossible)
   {
      // remove cards that were captured successfully from the table
      removeCardsFromTable(tableCards, matchedTableCards);
      removeCardFromHand(handSelCard);
      return true;
   }

   // no matching keys found
   return false;
}

bool Computer::trailCard(vector<Card>& tableCards)
{
   // store the size of the table cards
   int sizeOfTable = static_cast<int> (tableCards.size());

   // Cannot trail if there exists a build owned by the player
   if (isSingleBuildExist() == true || isMultipleBuildExist() == true)
   {
      return false;
   }

   // seed value to randomize number
   // used  explicit cast as seed wants an unsigned int of 32-bit integer
   auto seed = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());

   // random number generator
   auto rng = default_random_engine(seed);
   uniform_int_distribution<> generate(0, sizeOfTable - 1);

   // generate random number between 0 and (size of table - 1 ) 
   // treat the generated number as the index from which we select the card to trail
   int randomTableIndex = generate(rng);

   // trail the randomly selected card to the table
   tableCards.push_back(getCardsOnHand()[randomTableIndex]);
   
   // remove the card from player's hand once the handCard has been added to the table
   removeCardFromHand(getCardsOnHand()[randomTableIndex]);

   return true;
}