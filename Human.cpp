//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/23/2018
//****************************************************

#include "Human.h"

void Human::play(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild)
{
   // store the choice made by the user
   char choice;

   // check if the user has made a valid move
   bool moveSuccess = false;

   do
   {
      // Display the moves possible for the human player
      cout << "Choose the move that you want to make (1-5)" << endl;
      cout << "1. Make Single Build" << endl;
      cout << "2. Make Multiple Build" << endl;
      cout << "3. Increase Opponent's Build" << endl;
      cout << "4. Capture Cards" << endl;
      cout << "5. Trail Card" << endl;

      // Validate user choice
      do
      {
         cin >> choice;
      } while (!(choice >= '1' && choice <= '5'));

      // get choice as integer
      int ch = choice - '0';

      // call move functions based on user choice
      switch (ch)
      {
      case 1:
         moveSuccess = makeSingleBuild(tableCards);
         if (moveSuccess == true) { hasCapturedInCurMove = false; return; }
         break;
      case 2:
         moveSuccess = makeMultipleBuild(tableCards);
         if (moveSuccess == true) { hasCapturedInCurMove = false; return; }
         break;
      case 3:
         moveSuccess = increaseOpponentBuild(tableCards, oppoBuild);
         if (moveSuccess == true) { hasCapturedInCurMove = false; return; }
         break;
      case 4:
         moveSuccess = captureCards(tableCards);
         if (moveSuccess == true) { hasCapturedInCurMove = true; return; }
         break;
      default:
         moveSuccess = trailCard(tableCards);
         if (moveSuccess == true) { hasCapturedInCurMove = false; return; }
         break;
      }
      cout << "Invalid move. Try trailing the card!" << endl;
   } while (moveSuccess == false);
}

bool Human::makeSingleBuild(vector<Card>& tableCards)
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

   if (calcSingleCardScore(handSelCard) == calcLooseCardScore(looseCardsSelected))
   {
      initiateBuild(handSelCard, looseCardsSelected, calcSingleCardScore(handSelCard));
      removeCardFromHand(handSelCard);

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

bool Human::makeMultipleBuild(vector<Card>& tableCards)
{
   // get the build score of last successful single build 
   int previousBuildScore = getFirstBuildScore();

   // flag if there does not exist a card in hand that matches the previous single build score
   bool buildScoreMismatch = false;

   string combineTotalLooseCards;
   string cardSelectTable;
   vector<Card> looseCardsSelected;

   int loopCount = 0;

   cout << "\nTo create multiple builds, make sure that your newest build score matches the " << endl;
   cout << "score of your prior builds. Also, make sure that you have the card on your hand" << endl;
   cout << "that matches the score of the multiple build." << endl;

   for (auto handCards : getCardsOnHand())
   {
      // check if we have a card in hand that matches score of previous single build score
      if (calcSingleCardScore(handCards) != previousBuildScore)
      {
         buildScoreMismatch = true;
      }
      else
      {
         // since there exists a card that matches previous build score, we can break from loop
         buildScoreMismatch = false;
         break;
      }
   }

   // if there are no cards to match the previous build score, then return from the function
   if (buildScoreMismatch)
   {
      cout << "Invalid. No card present on hand that matches previous build score." << endl;
      return false;
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

bool Human::increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild)
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
      if (calcSingleCardScore(handCard) == calcLooseCardScore(oppnBuildCard))
      {
         cout << "Valid to increase opponent's build." << endl;

         singleBuildCard = make_tuple("Human", oppnBuildCard);
         vector<Card> empty{};
         oppoBuild = make_tuple("", empty);

         // As the player successfully increased the opponent's build, 
         // remove the card from the player's hand
         removeCardFromHand(handSelCard);
         success = true;
      }
   }
   return success;
}

void Human::initiateBuild(Card &handSelCard, vector<Card> &looseCardsSelected, int handCardScore)
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

void Human::initiateMultipleBuild(vector<Card>& looseCardsSelected)
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

   cout << "Multiple build successful!" << endl;
}

bool Human::captureCards(vector<Card>& tableCards)
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

bool Human::captureSetCards(vector<Card>& tableCards, Card& handSelCard)
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
      if (calcSingleCardScore(handSelCard) != calcLooseCardScore(looseCardsSelected))
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

bool Human::trailCard(vector<Card>& tableCards)
{
   return false;
}
