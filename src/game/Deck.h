#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Player.h"
#include "Card.h"
#include <gdkmm/pixbuf.h>

class Deck {
public:
	Deck(int);
	~Deck();
	void dealCards(std::vector<Player*>);
	void shuffle();
	void printDeck();

	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Suit s, Face f)

private:
	// std::vector<Card*> cards_;
	std::vector< Glib::RefPtr<Gdk::Pixbuf> > cards_;
	int seed_;
};

#endif