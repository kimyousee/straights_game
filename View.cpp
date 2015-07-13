#include "View.h"
#include <gtkmm.h>
#include <iostream>
#include "DeckGUI.h"

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), card(deck_.getNullCardImage()) {

	// Sets some properties of the window.
	set_title( "CS247 MVC example" );
	set_border_width( 10 );
	
	// Add panels to the window
	// add(panels);

	// // Add button box and card image to the panels
	// panels.add( butBox );
	// panels.add( card );
	// card.set( deck.null() );

	// // Add buttons to the box (a container). Buttons initially invisible
	// butBox.add( next_button );
	// butBox.add( reset_button );


	// // Associate button "clicked" events with local onButtonClicked() method defined below.
	// next_button.signal_clicked().connect( sigc::mem_fun( *this, &View::nextButtonClicked ) );
	// reset_button.signal_clicked().connect( sigc::mem_fun( *this, &View::resetButtonClicked ) );
	
	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}


void View::update() {
	// Suit suit = model_->suit();
	// Rank rank = model_->face();
	// if ( suit == NOSUIT ) 
	// 	card.set( deck.getNullImage() );
	// else
	// 	card.set( deck.getCardImage(suit, rank) );

}