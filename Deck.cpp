#include "Deck.h"
#include <random>
#include <iostream>

using namespace std;

int CARD_COUNT = 52;


// Deck constructor
Deck::Deck(int seed) {
	int suit = CLUB;
	int rank = ACE;
	seed_ = seed;

	for (int i = 0; i < 52; i++){
		int j = 0;
		while (j < 13) {
			cards_.push_back(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
			j++;
			rank = j;
		}
		suit++;
		rank = ACE;
	}
}

// Destructor
Deck::~Deck(){
	while (!cards_.empty()){
		delete cards_.back();
		cards_.pop_back();
	}
}

// Give each player 13 cards
void Deck::dealCards(std::vector<Player*> players) {
	int c = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 13; j++, c++){
			players[i]->incrementPlayerHand(cards_[c]);
		}
	}
}

// Used for the deck command
void Deck::printDeck(){
	int card = 0;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 13; j++){
			cout << *cards_[card];
			if (j != 12) cout << " "; // no space at end of line
			card++;
		}
		cout << endl;
	}
}

// CARD_COUNT is the constant 52
// cards_ is an array of pointers to cards
void Deck::shuffle(){
    static mt19937 rng(seed_);

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}
