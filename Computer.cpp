//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#include "Computer.h"

// ****************************************************************
// Function Name: play
// Purpose: describes the sequence of actions to perform in the current move
// Parameters: tableCards, a vector of cards. Holds the current cards in play that are on the table
//             oppoBuild, a tuple of string and vector of cards. Holds the opponent's single build
// Return value: none
// Assistance Received: none
// ****************************************************************
void Computer::play(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild)
{
   // Order in which computer will make a move
   // 1) Increase opponent's build
   // 2) Capture cards (both as a set or individual cards)
   // 3) Make multiple builds
   // 4) Make single build
   // 5) Trail card

   // flag for when computer suceessfully makes a move
   bool moveSuccess = false;

   // Make moves respectively. Return from the function if successful as a player can only make one move.
   cout << "\n******************************************************************************" << endl;

   moveSuccess = increaseOpponentBuild(tableCards, oppoBuild);
   if (moveSuccess == true) 
   { 
      cout << "Increased Opponent's Build." << endl;
      hasCapturedInCurMove = false; 
      return; 
   }

   moveSuccess = captureCards(tableCards);
   if (moveSuccess == true)
   {
      cout << "Cards captured." << endl;
      hasCapturedInCurMove = true;
      return;
   }

   moveSuccess = makeMultipleBuild(tableCards);
   if (moveSuccess == true) 
   { 
      cout << "Multiple Build Successful." << endl;
      hasCapturedInCurMove = false; 
      return; 
   }

   moveSuccess = makeSingleBuild(tableCards);
   if (moveSuccess == true) 
   { 
      cout << "Single Build Successful." << endl;
      hasCapturedInCurMove = false; 
      return; 
   }

   moveSuccess = trailCard(tableCards);
   if (moveSuccess == true) 
   { 
      cout << "Card trailed." << endl;
      hasCapturedInCurMove = false; 
      return; 
   }
}

// ****************************************************************
// Function Name: makeSingleBuild
// Purpose: performs the sequence of actions to make a single build
// Parameters: tableCards, a vector of cards. Holds the current cards in play that are on the table
// Return value: a boolean. Returns whether the player was able to make a single build or not
// Assistance Received: none
// ****************************************************************
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

      // remove card that made up build successfully from the player's hand
      Card cardToRemove = findCommonCard(matchedTableCards);

      // Explain move reasoning
      cout << getPlayerName() << " played " << cardToRemove.cardToString() << " to create a single build of ";
      for (auto cards : matchedTableCards)
      {
         cout << cards.cardToString() << " ";
      }
      cout << endl;

      removeCardFromHand(cardToRemove);

      // remove cards that made up build successfully from the table
      removeCardsFromTable(tableCards, matchedTableCards);
      return true; 
   }
   // no matching keys found
   return false;
}

// ****************************************************************
// Function Name: makeMultipleBuild
// Purpose: performs the sequence of actions to make a multiple build
// Parameters: tableCards, a vector of cards. Holds the current cards in play that are on the table
// Return value: a boolean. Returns whether the player was able to make a multiple build or not
// Assistance Received: none
// ****************************************************************
bool Computer::makeMultipleBuild(vector<Card>& tableCards)
{
   // get the build score of last successful single build 
   int previousBuildScore = getFirstBuildScore();

   // flag if there does not exist a card in hand that matches the previous single build score
   bool buildScoreMismatch = false;

   // ensure that we check all the possible keys before we return
   bool multipleBuildPossible = false;

   // the valid build cards used to make a multiple build
   vector<Card> matchedTableCards = {};

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

   // we check if there are two hand cards equal the score
   // of the previous single build score. We need two cards because one card will be used to build a multibuild
   // while the other card will be used to capture the multiple build in the player's next turn
   // store the number of cards with the same score as the previous build score
   int sameCardScoreCount = 0;

   // loop through the cards in the player's hand
   for (auto handCardToBuildWith : getCardsOnHand())
   {
      if (calcSingleCardScore(handCardToBuildWith) == previousBuildScore)
      {
         sameCardScoreCount++;

         // we have cards with the same score. So, we can make a multiple build
         if (sameCardScoreCount >= 2)
         {
            matchedTableCards.push_back(handCardToBuildWith);

            // Explain move reasoning
            cout << getPlayerName() << " played " << handCardToBuildWith.cardToString() << " to create a multiple build of ";
            for (auto cards : matchedTableCards)
            {
               cout << cards.cardToString() << " ";
            }
            cout << ". It wanted to increase the number of builds. " << endl;

            removeCardFromHand(handCardToBuildWith);
            initiateMultipleBuild(matchedTableCards);

            // remove cards that made up build successfully from the table
            removeCardsFromTable(tableCards, matchedTableCards);
            return true;
         }
      }
   }

   // if there are no more than 1 card that match the score of the previous build,
   // then multibuild is not possible
   if (sameCardScoreCount < 2)
   {
      return false;
   }
   if (tableCards.size() > 0)
   {
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
   }

   // Since hand card score matched the key in map at least once, we return true
   if (multipleBuildPossible)
   {
      // remove card that made up build successfully from the player's hand
      Card cardToRemove = findCommonCard(matchedTableCards);
      
      // Explain move reasoning
      cout << getPlayerName() << " played " << cardToRemove.cardToString() << " to create a multiple build of ";
      for (auto cards : matchedTableCards)
      {
         cout << cards.cardToString() << " ";
      }
      cout << ". It wanted to increase the number of builds. " << endl;

      removeCardFromHand(cardToRemove);
      initiateMultipleBuild(matchedTableCards);

      // remove cards that made up build successfully from the table
      removeCardsFromTable(tableCards, matchedTableCards);
      return true; 
   }
   return false;
}

// ****************************************************************
// Function Name: initiateMultipleBuild
// Purpose: makes multiple build from the successfully created multiple build  
// Parameters: -> looseCardsSelected, a vector of cards. Holds the cards that make up the new multiple build
// Return value: none
// Assistance Received: none
// ****************************************************************
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

   // empty the single build tuple
   singleBuild = {};
   singleBuildCard = make_tuple("", singleBuild);
}

// ****************************************************************
// Function Name: increaseOpponentBuild
// Purpose: performs the sequence of actions to increase an opponent's build
// Parameters: -> tableCards, a vector of cards. Holds the current cards in play that are on the table
//             -> oppoBuild, a tuple of string and vector of cards. Holds the opponent's single build
// Return value: a boolean. Returns whether the player was able to increase opponent's single build or not
// Assistance Received: none
// ****************************************************************
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

            // Explain move reasoning
            cout << getPlayerName() << " played " << handCardToIncrease.cardToString() << " to increase opponent's build." << endl;
            cout << "It wanted to own the build of the opponent and thus dent their chances of capturing that build." << endl;

            return true;
         }
      }
      // remove the card from the opponent's build that we temporarily added to check if we can increase the build or not
      oppnBuildCard.erase(remove(oppnBuildCard.begin(), oppnBuildCard.end(), handCardToIncrease), oppnBuildCard.end());
   }
   return false;
}

// ****************************************************************
// Function Name: captureCards
// Purpose: performs the sequence of actions to capture cards
// Parameters: -> tableCards, a vector of cards. Holds the current cards in play that are on the table
// Algorithm:
//       1) Capture multiple builds first
//       2) Capture single builds
//       3) Capture set of cards
//       4) Capture individual loose cards
// Return value: a boolean. Returns whether the player was able to capture cards or not
// Assistance Received: none
// ****************************************************************
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
            // store the single and multiple builds
            vector<Card> singleBuild;
            vector<vector<Card>> multipleBuild;

            // unpack the tuple to get a list of Cards in the multiple build
            tie(ignore, multipleBuild) = multipleBuildCard;

            // Explain move reasoning
            cout << getPlayerName() << " played " << handCard.cardToString() << " to capture a multiple build of " << endl;

            // loop through the builds stored in the multibuild
            for (auto parsedBuild : multipleBuild)
            {
               // push the cards of the single build into the player's pile
               for (auto buildCards : parsedBuild)
               {
                  cardsOnPile.push_back(buildCards);
                  cout << buildCards.cardToString() << " ";
               }
            }
            cout << ". It wanted to maximize the number of captured cards." << endl;

            // empty the multibuild as we have captured these cards
            // Also, we need to empty the single build as multiple build has already captured those cards
            multipleBuild = {};
            singleBuild = {};
            multipleBuildCard = make_tuple("", multipleBuild);
            singleBuildCard = make_tuple("", singleBuild);

            // remove card that was used to capture the build successfully from the player's hand and add to pile
            removeCardFromHand(handCard);
            cardsOnPile.push_back(handCard);
            return true;
         }
         // capture single build
         if (isSingleBuildExist() == true)
         {
            // store the single build
            vector<Card> singleBuild;

            // unpack the tuple to get the single build
            tie(ignore, singleBuild) = singleBuildCard;

            // Explain move reasoning
            cout << getPlayerName() << " played " << handCard.cardToString() << " to capture a single build of " << endl;

            // push the cards in the single build into the player's pile
            for (auto buildCards : singleBuild)
            {
               cardsOnPile.push_back(buildCards);
               cout << buildCards.cardToString() << " ";
            }
            cout << ". It wanted to capture its single build." << endl;

            // empty the single build as we have captured these cards
            singleBuild = {};
            singleBuildCard = make_tuple("", singleBuild);

            // push the hand card into the player's pile and remove it from player's hand
            cardsOnPile.push_back(handCard);
            removeCardFromHand(handCard);
            return true;
         }
      }
   }

   // Since there are no cards on hand that matches the score of the builds, we move
   // to capture set of cards or loose cards from the table
   for (auto handCard : getCardsOnHand())
   {
      // flag that sets if capturing set of cards was possible
      bool captureSetSuccess = captureSetCards(tableCards, handCard);

      // if we captured set of cards, then return true from the function
      if (captureSetSuccess == true)
      {
         return true;
      }
   }

   // the loose individual cards that can be captured from the table
   vector<Card> matchedTableCards = {};

   // flag if individual cards have been captured
   bool indiCaptured = false;

   // Selected hand card to capture individual cards 
   Card cardToRemove;

   // If there were no sets to capture, check if there are any individual loose cards to capture
   for (auto handCard : getCardsOnHand())
   {
      int handCardScore = calcSingleCardScore(handCard);

      // Add any single card from the table that matches the score of the current card in player's hand
      for (auto tableCard : tableCards)
      {
         if (calcSingleCardScore(tableCard) == handCardScore)
         {
            // Explain move reasoning
            cout << getPlayerName() << " played " << handCard.cardToString() << " to capture individual card ";
            cout << tableCard.cardToString() << " " << endl;

            cardToRemove = handCard;
            cardsOnPile.push_back(tableCard);
            matchedTableCards.push_back(tableCard);
            indiCaptured = true;
         }
      }

      if (indiCaptured == true)
      {
         cardsOnPile.push_back(cardToRemove);
         removeCardFromHand(cardToRemove);
         removeCardsFromTable(tableCards, matchedTableCards);
         return true;
      }
   }

   // not possible to capture any cards from builds or as set of cards or as individual cards
   return false;
}

// ****************************************************************
// Function Name: captureSetCards
// Purpose: performs the sequence of actions to capture set of cards
// Parameters: -> tableCards, a vector of cards. Holds the current cards in play that are on the table
//             -> handSelCard, a Card object. Holds the card that will be used to capture set of cards
// Return value: a boolean. Returns whether the player was able to capture set of cards or not
// Assistance Received: none
// ****************************************************************
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
         
         // Explain move reasoning
         cout << getPlayerName() << " played " << handSelCard.cardToString() << " to capture the set of " << endl;

         // add the possible set of cards to the player's pile
         // also, add the cards temporarily to a vector of cards to remove 
         // them from the table after capturing is done
         for (auto match : itr->second)
         {
            cardsOnPile.push_back(match);
            matchedTableCards.push_back(match);
            cout << match.cardToString() << " ";
         }

         cout << ". It wanted to maximize the number of captured cards." << endl;
         
         // Add any single card from the table that matches the score of the current card in player's hand
         for (auto tableCard : tableCards)
         {
            if (calcSingleCardScore(tableCard) == handCardScore)
            {            
               // Explain move reasoning
               cout << getPlayerName() << " played " << handSelCard.cardToString() << " to capture individual card ";
               cout << tableCard.cardToString() << " " << endl;

               cardsOnPile.push_back(tableCard);
               matchedTableCards.push_back(tableCard);
            }
            cout << endl;
         }

         // add the hand card that was used to capture to computer's pile
         // then remove it from its hand
         cardsOnPile.push_back(handSelCard);
         removeCardFromHand(handSelCard);

         // if capturing of sets was possible, then remove the captured cards from the table 
         removeCardsFromTable(tableCards, matchedTableCards);
         return true;
      }
   }
   // no matching keys found
   return false;
}

// ****************************************************************
// Function Name: trailCard
// Purpose: performs the sequence of actions to trail a card
// Parameters: -> tableCards, a vector of cards. Holds the current cards in play that are on the table
// Return value: a boolean. Returns whether the player was able to trail a card or not
// Assistance Received: none
// ****************************************************************
bool Computer::trailCard(vector<Card>& tableCards)
{
   // store the size of the table cards
   int sizeOfHandCards = static_cast<int> (getCardsOnHand().size());

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
   uniform_int_distribution<> generate(0, sizeOfHandCards - 1);

   // generate random number between 0 and (size of hand cards - 1 ) 
   // treat the generated number as the index from which we select the card to trail
   int randomTableIndex = generate(rng);

   Card trailCard = getCardsOnHand()[randomTableIndex];

   // trail the randomly selected card to the table
   tableCards.push_back(trailCard);
   
   // remove the card from player's hand once the handCard has been added to the table
   removeCardFromHand(trailCard);

   cout << getPlayerName() << " trailed " << trailCard.cardToString() << " because there were no other possible moves." << endl;
   return true;
}

// ****************************************************************
// Function Name: ~Computer
// Purpose: destructor for Computer class 
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Computer::~Computer()
{
}