#include "Deck.h"
#include <random>
#include <iostream>

using namespace std;

int CARD_COUNT = 52;

using namespace std;

// Deck constructor
Deck::Deck(int seed) {
	int suit = CLUB;
	int rank = ACE;
	seed_ = seed;

	for (int i = 0; i < 52; i++){
		int j = 0;
		while (j < 4) {
			cards_.push_back(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
			j++;
			suit = j;
		}
		suit = CLUB;
		rank++;
	}
}

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


void Deck::printDeck(){

	for (int i = 0; i < 52; i++){
		if (i!= 0 && i % 13 == 0) cout << endl;
		cout << *cards_[i] << " ";
	}
	cout << endl;
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


