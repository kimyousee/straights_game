#include "View.h"
#include <gtkmm.h>
#include <iostream>
#include "DeckGUI.h"

using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), vboxframe_(true,10), deck_() {

	// Make the start button
	start_button_.signal_clicked().connect(sigc::mem_fun(*this,
		&View::on_start_game_clicked_));
	start_button_.add_label("button");
	add(start_button_);

	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck_.getNullCardImage();

	// Sets some properties of the window.
	set_title( "Straights UI" );
	set_border_width( 10 );

	// Set the look of the frame.
	frame_.set_label( "Cards on the table:" );
	frame_.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	frame_.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	

	for (int i = 0; i < 13; i++) {
		clubs_.push_back( new Gtk::Image( nullCardPixbuf ) );
		diamonds_.push_back( new Gtk::Image( nullCardPixbuf ) );
		spades_.push_back( new Gtk::Image( nullCardPixbuf ) );
		hearts_.push_back( new Gtk::Image( nullCardPixbuf ) );
	}

	table_.push_back(clubs_);
	table_.push_back(diamonds_);
	table_.push_back(spades_);
	table_.push_back(hearts_);


	// Add the frame to the window. Windows can only hold one widget, same for frames.
	add( frame_ );

	// Add the horizontal box for laying out the images to the frame.
	frame_.add( vboxframe_ );


	//cout << (table_[0][0]) << endl;


	// Initialize 4 empty cards and place them in the box.
	for(int j = 0; j < 4; j++){
		for (int i = 0; i < 13; i++ ) {
			//table_[j][i] = new Gtk::Image( nullCardPixbuf );
			row_.add( *((table_)[j][i]) );
		}
		vboxframe_.add(row_);
	}



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

View::~View() {
	std::cout << "view destructor" << std::endl;
}

void View::on_start_game_clicked_(){
	controller_->startButtonClicked();
}


void View::update() {
	// Suit suit = model_->suit();
	// Rank rank = model_->face();
	// if ( suit == NOSUIT ) 
	// 	card.set( deck.getNullImage() );
	// else
	// 	card.set( deck.getCardImage(suit, rank) );

}