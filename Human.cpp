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
      
      cout << "\n******************************************************************************" << endl;

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
   // hand card used to make a build, input as string
   string cardSelectHand;
   // loose card on the table to make a build with, input as string
   string cardSelectTable;
   // total number of loose cards in the table to make the build
   string noOfLooseCardsToBuild;
   // the loose cards selected to make a build
   vector<Card> looseCardsSelected;

   // number of cards in the table to make a build
   int loopCount;

   // User cannot make a single build if there are less than two cards in hand
   if (getCardsOnHand().size() < 2)
   {
      cout << "Invalid. Cannot build when there are less than two cards in hand." << endl;
      return false;
   }

   // User cannot make a build if there are no cards in the table
   if (tableCards.size() < 1)
   {
      cout << "Invalid. No cards on table to build with." << endl;
      false;
   }

   // Get hand card to make a build from the user
   cout << "From your hand, enter the card (eg. S3) that you want to make a build of: ";
   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));
   Card selectedHandCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));

   // add the selected card to the build that the user is trying to make
   looseCardsSelected.push_back(selectedHandCard);

   // Get the total number of loose cards that the user wants to make a build
   cout << "\nEnter the number of loose cards that you want to make a build with your selected hand card: ";
   do
   {
      cin >> noOfLooseCardsToBuild;
   } while (!(isDigit(noOfLooseCardsToBuild)));

   // get the loose cards that the user wants to use to make a build
   loopCount = stoi(noOfLooseCardsToBuild);
   for (short int i = 0; i < loopCount; i++)
   {
      cout << "\nEnter the loose card to build with: ";
      do
      {
         cin >> cardSelectTable;
      } while (!(isCardOnTable(cardSelectTable, tableCards)));

      // convert the card input as string into a Card object
      // Then, push the cards into the possible buildCards
      Card tempCard(getString(cardSelectTable[0]), getString(cardSelectTable[1]));
      looseCardsSelected.push_back(tempCard);
   }

   int buildScore = calcLooseCardScore(looseCardsSelected);

   // check if there is a card on hand that matches the score of the new build 
   // that the user is trying to make
   for (auto handCard : getCardsOnHand())
   {
      // check if the hand card score matches the build that the user is trying to make
      if (calcSingleCardScore(handCard) == buildScore)
      {
         // if matched, initiate the building process
         initiateBuild(looseCardsSelected, buildScore);

         // remove the card from hand and the table now that the user has made the build
         removeCardFromHand(selectedHandCard);
         removeCardsFromTable(tableCards, looseCardsSelected);
         return true;
      }
   }

   // build score not matched, illegal.
   cout << "Build values do not match. " << endl;
   return false;
}

bool Human::makeMultipleBuild(vector<Card>& tableCards)
{
   // get the build score of last successful single build 
   int previousBuildScore = getFirstBuildScore();

   // flag if there does not exist a card in hand that matches the previous single build score
   bool buildScoreMismatch = false;

   // choice to form a multiple build with single card
   char choice;

   // hand card used to make a build, input as string
   string cardSelectHand;

   // the total number of loose cards that the user wants to make a build of
   string combineTotalLooseCards;

   // loose card on the table to make a build with, input as string
   string cardSelectTable;

   // the loose cards selected to make a build
   vector<Card> looseCardsSelected;

   // number of cards in the table to make a build
   int loopCount = 0;

   // User cannot make a multiple build if there are less than two cards in hand
   if (getCardsOnHand().size() < 2)
   {
      cout << "Invalid. Cannot build when there are less than two cards in hand." << endl;
      return false;
   }

   cout << "\n******************************************************************************" << endl;
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
   if (buildScoreMismatch == true)
   {
      cout << "Invalid. No card present on hand that matches previous build score." << endl;
      return false;
   }

   // Get the card from user's hand that will be used to make the new multibuild
   // Get hand card to make a build from the user
   cout << "From your hand, enter the card (eg. S3) that you want to make a build of: ";
   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));
   Card selectedHandCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));

   // Ask the human player if they want to make a multiple build with just a single card
   do
   {
      cout << "\n******************************************************************************" << endl;
      cout << "Do you want to make a multiple build with only the selected single hand card" << endl;
      cout << "that matches the previous build score of " << previousBuildScore << " (Y/N)?";
      cin >> choice;
      choice = toupper(choice);
   } while (!(choice == 'Y' || choice == 'N'));

   // Make multiple build of single card
   if (choice == 'Y')
   {
      // Check if the newest build matches the score of the previous build
      if (calcSingleCardScore(selectedHandCard) == previousBuildScore)
      {
         int sameHandCardScore = 0;
         // check if there are at least two cards on hand that match the 
         // score of the new build that the user is trying to make
         for (auto handCard : getCardsOnHand())
         {
            if (calcSingleCardScore(handCard) == previousBuildScore)
            {
               sameHandCardScore++;

               // initiate multiple build if we have two hand cards with same score as previous build score
               if (sameHandCardScore >= 2)
               {
                  // add the selected card to the build that the user is trying to make
                  looseCardsSelected.push_back(selectedHandCard);

                  initiateMultipleBuild(looseCardsSelected);
                  removeCardFromHand(selectedHandCard);
                  return true;
               }
            }
         }
      }
      // The single card that the user is trying to use to make a singular-build does not match the score of the previous build
      else
      {
         cout << "Invalid. Newest build score does not match the previous score of " << previousBuildScore << "." << endl;
         return false;
      }
   }

   // Make multiple build with multiple cards in the build
   else
   {
      // add the selected card to the build that the user is trying to make
      looseCardsSelected.push_back(selectedHandCard);

      // Get the total number of loose cards that the user wants to make a build
      cout << "\nFor your newest multiple build, enter the number of loose cards" << endl;
      cout << "that you want to combine your selected hand card with : ";
      do
      {
         cin >> combineTotalLooseCards;
      } while (!(isDigit(combineTotalLooseCards)));

      // get the loose cards that the user wants to use to make a build
      loopCount = stoi(combineTotalLooseCards);
      for (short int i = 0; i < loopCount; i++)
      {
         cout << "\nEnter the loose card to build with: ";
         do
         {
            cin >> cardSelectTable;
         } while (!(isCardOnTable(cardSelectTable, tableCards)));

         // convert the card input as string into a Card object
         // Then, push the cards into the possible buildCards
         Card tempCard(getString(cardSelectTable[0]), getString(cardSelectTable[1]));
         looseCardsSelected.push_back(tempCard);
      }

      // Check if the newest build matches the score of the previous build
      if (previousBuildScore != calcLooseCardScore(looseCardsSelected))
      {
         cout << "Invalid. Newest build score does not match the previous score of " << previousBuildScore << "." << endl;
         return false;
      }
      else
      {
         // check if there is a card on hand that matches the score of the new build 
         // that the user is trying to make
         for (auto handCard : getCardsOnHand())
         {
            // check if the hand card score matches the build that the user is trying to make
            if (calcSingleCardScore(handCard) == previousBuildScore)
            {
               // make multiple build as the build score matched the previous single build score
               // and there is a card in hand equal to the new build score
               initiateMultipleBuild(looseCardsSelected);

               // remove the card from hand and the table now that the user has made the build
               removeCardFromHand(selectedHandCard);
               removeCardsFromTable(tableCards, looseCardsSelected);
               return true;
            }
         }
      }
   }
   return false;
}

bool Human::increaseOpponentBuild(vector<Card>& tableCards, tuple<string, vector<Card>>& oppoBuild)
{
   // string input of the card that the player will use to increase opponent's build
   string cardSelectHand;

   // owner of the opponent's build
   string owner;

   // opponent's single build
   vector<Card> oppnBuildCard;

   // unpack the tuple of the opponent's build
   tie(owner, oppnBuildCard) = oppoBuild;

   // ensure that the player is not increasing their own build or that the opponent's build is not empty
   if (owner == getPlayerName() || oppnBuildCard.size() == 0)
   {
      cout << "Cannot increment your own build or opponent's build is empty!" << endl;
      return false;
   }

   cout << "When extending an opponent's \"single\" build, ensure that you are holding" << endl;
   cout << "a card equal to the extended sum." << endl;

   // get the card that the user wants to use to increase opponent's build
   cout << "From your hand, enter the card (eg. S3) to increase opponent's build: ";
   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));

   // convert the string card into Card object and push it to opponent's build temporarily
   Card selectedHandCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));
   oppnBuildCard.push_back(selectedHandCard);

   // check if there is a handcard that the player can use to increase the opponent's build
   // by matching the handcard score against the score of the possible extended build
   for (auto handCard : getCardsOnHand())
   {
      if (calcSingleCardScore(handCard) == calcLooseCardScore(oppnBuildCard))
      {
         cout << "Successfully increased opponent's build." << endl;

         // store the new build into the human's single build
         // and set the opponent's build to be empty
         singleBuildCard = make_tuple(getPlayerName(), oppnBuildCard);
         vector<Card> empty{};
         oppoBuild = make_tuple("", empty);

         // As the player successfully increased the opponent's build, 
         // remove the card from the player's hand
         removeCardFromHand(selectedHandCard);
         return true;
      }
   }
   return false;
}

void Human::initiateBuild(vector<Card> &looseCardsSelected, int handCardScore)
{
   vector<Card> build;

   // set the score of the first build
   firstBuildScore = handCardScore;

   // extract the cards from the successful build and add it to the player's temporary build
   for (auto buildCard : looseCardsSelected)
   {
      build.push_back(buildCard);
   }
   // create a single build with the player as the owner of the build
   singleBuildCard = make_tuple(getPlayerName(), build);
   cout << "Single build successful!" << endl;
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

   // empty the single build tuple as we have made the multiple build
   singleBuild = {};
   singleBuildCard = make_tuple("", singleBuild);

   cout << "Multiple build successful!" << endl;
}

bool Human::captureCards(vector<Card>& tableCards)
{
   // user input for their selected card to be used to capture cards
   string cardSelectHand;
   
   // store user choice to either capture builds or sets
   int captureChoice;

   // store the selected hand card score
   int handCardScore = 0;

   // check if user wants to capture a set or not
   char userInput;

   // flag for a captured card
   bool captured = false;

   // flag if a set has been captured
   bool setCaptureSuccess = false;

   // Provide the human player with option to capture cards
   cout << "Choose what you want to capture (1-3)" << endl;
   cout << "1. Capture Multiple Build" << endl;
   cout << "2. Capture Single Build" << endl;
   cout << "3. Capture set or individual cards" << endl;
   
   // get user choice
   do 
   {
      cin >> captureChoice;
   } while (!(captureChoice >= 1 && captureChoice <= 3));

   // get the handcard that the user wants to use to capture cards
   cout << "From your hand, enter the card (eg. S3) that you will use to" << endl;
   cout << "capture your choice option of cards: ";

   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));
   Card selectedHandCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));
   handCardScore = calcSingleCardScore(selectedHandCard);

   /////////////////////////
   // Start Capturing
   /////////////////////////

   // Capture multiple build
   if (captureChoice == 1)
   {
      // check if multiple build was captured
      bool multiCaptured = captureMultipleBuild(handCardScore, selectedHandCard);

      if (multiCaptured == true) { return true; }
      else { return false; }
   }
   
   // Capture single build
   else if (captureChoice == 2)
   {
      // check if single build was captured
      bool singleCaptured = captureSingleBuild(handCardScore, selectedHandCard);
      
      if (singleCaptured == true) { return true; }
      else { return false; }
   }

   // Capture individual or set of cards
   else
   {
      // Capture any individual cards that are on the table that matches the selected card
      for (auto table : tableCards)
      {
         if (selectedHandCard.getFace() == table.getFace())
         {
            cardsOnPile.push_back(table);

            // remove the matched loose cards from the table that were captured using the selected hand card 
            tableCards.erase(remove(tableCards.begin(), tableCards.end(), table), tableCards.end());
            captured = true;
         }
      }

      // At this point, individual cards have been captured
      // We now ask the user if they want to capture set of cards 
      // as it is optional to capture set of cards
      cout << "Do you want to capture set of cards (Y/N)?";
      do
      {
         cin >> userInput;
         userInput = toupper(userInput);
      } while (!(userInput == 'Y' || userInput == 'N'));

      if (userInput == 'N')
      {
         cout << "You opted not to capture a set of cards" << endl;

         // check if any individual loose cards were captured
         if (captured == true)
         {
            cardsOnPile.push_back(selectedHandCard);
            removeCardFromHand(selectedHandCard);
            cout << "Individual loose cards have been captured using your selected card!" << endl;
            return true;
         }
         else 
         { 
            cout << "No individual cards captured!" << endl; 
            return false; 
         }
      }

      // Player will now begin to capture set of cards
      else
      {
         setCaptureSuccess = captureSetCards(tableCards, selectedHandCard);

         // After capturing of the set, we remove the card that was 
         // used to capture cards on the table from the player's hand
         if (captured == true || setCaptureSuccess == true)
         {
            cardsOnPile.push_back(selectedHandCard);
            removeCardFromHand(selectedHandCard);
            cout << "Card capture successful!" << endl;
            return true;
         }

         // check if any cards were captured in this move
         else if (captured == false && setCaptureSuccess == false)
         {
            cout << "No sets captured or any other individual loose cards." << endl;
            return false;
         }
      }
   }
   return false;
}

bool Human::captureSingleBuild(int handCardScore, Card &selectedHandCard)
{
   // single build card of the player
   vector<Card> singleBuild;

   if (isSingleBuildExist() == false)
   {
      cout << "Invalid. No single build exists to capture!!" << endl;
      return false;
   }

   // check if the selected hand card score matches the single build card score
   if (handCardScore == firstBuildScore)
   {
      // unpack the tuple of the single build
      tie(ignore, singleBuild) = singleBuildCard;

      // add cards from the single build to the pile
      for (auto cards : singleBuild)
      {
         cardsOnPile.push_back(cards);
      }

      // after capturing the card, empty the single build of the player and set the build score to 0
      singleBuild = {};
      singleBuildCard = make_tuple("", singleBuild);
      firstBuildScore = 0;

      // add selected hand card to the pile and then remove it from the player's hand
      cardsOnPile.push_back(selectedHandCard);
      removeCardFromHand(selectedHandCard);

      cout << "Captured single build!!" << endl;
      return true;
   }
   else
   {
      cout << "Invalid. Selected hand card does not match the single build score of " << firstBuildScore << endl;
      return false;
   }
   return false;
}

bool Human::captureMultipleBuild(int handCardScore, Card &selectedHandCard)
{
   // multiple build cards of the player
   vector<vector<Card>> multipleBuild;

   if (isMultipleBuildExist() == false)
   {
      cout << "Invalid. No multiple builds exist to capture!!" << endl;
      return false;
   }

   // check if the selected hand card score matches the multiple build card score
   if (handCardScore == firstBuildScore)
   {
      // unpack the multiple build tuple
      tie(ignore, multipleBuild) = multipleBuildCard;

      // add the cards in the multiple build to the pile of the human player
      for (auto singleBuild : multipleBuild)
      {
         for (auto cards : singleBuild)
         {
            cardsOnPile.push_back(cards);
         }
      }

      // after capturing the card, empty the multiple build of the player and set the build score to 0
      multipleBuild = {};
      multipleBuildCard = make_tuple("", multipleBuild);
      firstBuildScore = 0;

      // add selected hand card to the pile and then remove it from the player's hand
      cardsOnPile.push_back(selectedHandCard);
      removeCardFromHand(selectedHandCard);

      cout << "Captured multiple build!!" << endl;
      return true;
   }
   else
   {
      cout << "Invalid. Selected hand card does not match the multiple build score of " << firstBuildScore << endl;
      return false;
   }
   return false;
}

bool Human::captureSetCards(vector<Card>& tableCards, Card& selectedHandCard)
{
   // cards to capture as a set
   string combineTotalLooseCards;
   
   // total number of sets to capture
   string totalSetsToCapture;

   // cards to capture as a set from the table
   string selectedTableCard;

   // possible set combination
   vector<Card> looseCardsSelected;

   // flag if sets have been captured
   bool setsCaptured = false;

   int setCaptureCount = 0, looseCaptureCount = 0;

   // Ask user for the number of sets that they want to capture
   cout << "\nEnter the number of set of cards that you want to capture : ";
   do
   {
      cin >> totalSetsToCapture;
   } while (!(isDigit(totalSetsToCapture)));

   // convert the total number of sets from string to integer
   setCaptureCount = stoi(totalSetsToCapture);

   // Loop through the number of sets to capture
   for (short int i = 0; i < setCaptureCount; i++)
   {
      // Get the cards to capture in the current set
      cout << "Enter the number of loose cards that you want to capture in set " << i << endl;
      do
      {
         cin >> combineTotalLooseCards;
      } while (!(isDigit(combineTotalLooseCards)));
      looseCaptureCount = stoi(combineTotalLooseCards);


      // Loop through the total cards to capture in the current set
      for (short int j = 0; j < looseCaptureCount; j++)
      {
         cout << "\nEnter the loose card to capture as a set (eg. S3): ";
         do
         {
            cin >> selectedTableCard;
         } while (!(isCardOnTable(selectedTableCard, tableCards)));

         Card tempCard(getString(selectedTableCard[0]), getString(selectedTableCard[1]));
         looseCardsSelected.push_back(tempCard);
      }

      // check if the selected hand card score matches the score of set of cards
      if (calcSingleCardScore(selectedHandCard) != calcLooseCardScore(looseCardsSelected))
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
         setsCaptured = true;
      }
   }
   if (setsCaptured == true)
   {
      // Capture of the set of cards has been successful
      return true;
   }
   return false;
}

bool Human::trailCard(vector<Card>& tableCards)
{
   string cardSelectHand;
   int handCardScore = 0;

   // Warn the human player that trailing is not possible when they own a build
   if (isSingleBuildExist() == true || isMultipleBuildExist() == true)
   {
      cout << "Invalid. Cannot trail when you have builds. Capture the build instead?" << endl;
      return false;
   }

   cout << "\nFrom your hand, enter the card (eg. S3) that you want to trail: ";
   do
   {
      cin >> cardSelectHand;
   } while (!(isCardOnHand(cardSelectHand)));
   
   // convert the string into a Card object
   Card trailCard(getString(cardSelectHand[0]), getString(cardSelectHand[1]));
   handCardScore = calcSingleCardScore(trailCard);

   if (tableCards.size() > 0)
   {
      // Check whether there are any loose cards on the table that the user 
      // has not captured using this selected hand card
      for (auto tblCard : tableCards)
      {
         if (handCardScore == calcSingleCardScore(tblCard))
         {
            cout << "Invalid. Cannot trail when you have a matching loose card in the table. Try capturing instead?" << endl;
            return false;
         }
      }
   }

   // add the selected card to trail on the table and then remove from the player's hand
   tableCards.push_back(trailCard);
   removeCardFromHand(trailCard);

   // Human trailed the card successsfully
   return true;
}

Human::~Human()
{
}