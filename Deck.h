#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Player.h"
#include "Card.h"

class Deck {
public:
	Deck(int);
	~Deck();
	void dealCards(std::vector<Player*>);
	void shuffle();
	void printDeck();


private:
	// std::vector<Card*> cards_;
	std::vector< Card* > cards_;
	int seed_;
};

#endif