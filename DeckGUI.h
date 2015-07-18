#ifndef DECK_GUI_H
#define DECK_GUI_H

#include <gdkmm/pixbuf.h>
#include <vector>

#include "Model.h"
#include "Card.h"

// This deck is solely used for the UI, to show cards on the table
class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	// Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Suit, Rank);
	// Returns the image to use for the placeholder.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();

private:
	std::vector< Glib::RefPtr< Gdk::Pixbuf > > deck_;
};

#endif