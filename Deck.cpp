//****************************************************
//* Name: Manasbi Parajuli
//* Project: Casino
//* Class: CMPS 366-01
//* Date: 10/2/2018
//****************************************************

#include "Deck.h"

// ****************************************************************
// Function Name: Deck
// Purpose: constructor to create an instance of deck of cards 
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
Deck::Deck()
{
	const string faces[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K" };
	const string suits[] = { "C", "D", "H", "S" };

	for (auto const &suit: suits)
	{
      for (auto const &face : faces)
      {
         // push the card into the deck
         deck.push_back(Card (suit, face));
		}
	}
}

// ****************************************************************
// Function Name: shuffleDeck
// Purpose: to shuffle the cards in a given deck and reverses the order
//          so that we can use pop_back() method while dealing cards
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Deck::shuffleDeck()
{
   // seed value to randomize deck
   // used  explicit cast as seed wants an unsigned int of 32-bit integer
   auto seed = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());
   
   // random number generator
   auto rng = default_random_engine(seed);

   // shuffle the deck of cards using seed value
   shuffle(deck.begin(), deck.end(), rng);

   // reversed the card so that 1st card is placed at the end of the vector
   // then we can use pop_back() function to deal the first card
   reverse(deck.begin(), deck.end());
}

// ****************************************************************
// Function Name: dealCard
// Purpose: to draw one card from the deck
// Parameters: none
// Return value: The topmost card on the deck, a Card object
// Assistance Received: none
// ****************************************************************
Card Deck::dealCard()
{
   // get the first card and decrease the vector size by 1
   auto cardOnTop = deck.back();
   deck.pop_back();
   return cardOnTop;
}

// ****************************************************************
// Function Name: printDeck
// Purpose: prints all the cards in the deck
// Parameters: none
// Return value: none
// Assistance Received: none
// ****************************************************************
void Deck::printDeck()
{
   cout << "helo" << endl;
   for (auto card : deck)
   {
      cout << card.cardToString() + " ";
   }
   cout << endl;
}

// ****************************************************************
// Function Name: isDeckEmpty
// Purpose: checks if the deck is empty
// Parameters: none
// Return value: returns true or false based on whether the deck is empty or not
// Assistance Received: none
// ****************************************************************
bool Deck::isDeckEmpty() const
{
   return deck.empty();
}

// ****************************************************************
// Function Name: getDeck
// Purpose: get the current deck
// Parameters: none
// Return value: returns the current deck used in the game
// Assistance Received: none
// ****************************************************************
vector<Card> Deck::getDeck()
{
   return deck;
}

// ****************************************************************
// Function Name: setDeck
// Purpose: set the current deck
// Parameters: card, a vector<Card> type. The deck to be used for the game
// Return value: none
// Assistance Received: none
// ****************************************************************
void Deck::setDeck(vector<Card> tempDeck)
{
   deck = tempDeck;
}
