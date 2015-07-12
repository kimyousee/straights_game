#include "Deck.h"
#include <random>
#include <iostream>

using namespace std;

int CARD_COUNT = 52;

// An array of card png files
const char * image_names[] = {
	// Clovers
	"card_img/0_0.png", "card_img/0_1.png", "card_img/0_2.png", "card_img/0_3.png", "card_img/0_4.png", "card_img/0_5.png", 
	"card_img/0_6.png", "card_img/0_7.png", "card_img/0_8.png", "card_img/0_9.png", "card_img/0_j.png", "card_img/0_q.png", "card_img/0_k.png", 
	// Diamonds
	"card_img/1_0.png", "card_img/1_1.png", "card_img/1_2.png", "card_img/1_3.png", "card_img/1_4.png", "card_img/1_5.png", 
	"card_img/1_6.png", "card_img/1_7.png", "card_img/1_8.png", "card_img/1_9.png", "card_img/1_j.png", "card_img/1_q.png", "card_img/1_k.png", 
	// Hearts
	"card_img/2_0.png", "card_img/2_1.png", "card_img/2_2.png", "card_img/2_3.png", "card_img/2_4.png", "card_img/2_5.png", 
	"card_img/2_6.png", "card_img/2_7.png", "card_img/2_8.png", "card_img/2_9.png", "card_img/2_j.png", "card_img/2_q.png", "card_img/2_k.png", 
	// Spades
	"card_img/3_0.png", "card_img/3_1.png", "card_img/3_2.png", "card_img/3_3.png", "card_img/3_4.png", "card_img/3_5.png", 
	"card_img/3_6.png", "card_img/3_7.png", "card_img/3_8.png", "card_img/3_9.png", "card_img/3_j.png", "card_img/3_q.png", "card_img/3_k.png", 
	// Null card
	"card_img/nothing.png"
}

// Deck constructor
Deck::Deck(int seed) {
	// int suit = CLUB;
	// int rank = ACE;
	// seed_ = seed;

	// for (int i = 0; i < 52; i++){
	// 	int j = 0;
	// 	while (j < 13) {
	// 		cards_.push_back(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
	// 		j++;
	// 		rank = j;
	// 	}
	// 	suit++;
	// 	rank = ACE;
	// }
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(cards_), &createPixbuf );
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

// Load image to a pixel buffer
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string &name){
	return Gdk::Pixbuf::create_from_file( name );
}

Glib::RefPtr<Gdk::Pixbuf> Deck::getCardImage(Suit s, Face f){
	int index = ((int) s)*4 + ((int) f);
	return cards_[index];
}

Glib::RefPtr<Gdk::Pixbuf> Deck::getNullCardImage() {
	int size = cards_.size();
	return deck[size-1];
}
