#include "DeckGUI.h"
#include <gdkmm/pixbuf.h>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

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
};

// Load image to a pixel buffer
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string &name){
	return Gdk::Pixbuf::create_from_file( name );
}

DeckGUI::DeckGUI(){
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(deck_), &createPixbuf );
}

DeckGUI::~DeckGUI() {
}

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getCardImage(Suit s, Rank r){
	int index = ((int) s)*4 + ((int) r);
	return deck_[index];
}

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getNullCardImage() {
	int size = deck_.size();
	return deck_[size-1];
}