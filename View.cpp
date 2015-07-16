#include "View.h"
#include <gtkmm.h>
#include <iostream>
#include <string>
#include "DeckGUI.h"
#include "StartGameDialogBox.h"

using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), hand_(true,10), table_(true,10), gameBox_(false,10) {
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck_.getNullCardImage();
	
	// Sets some properties of the window.
	set_title( "Straights UI" );
	//Gtk::JUSTIFY_CENTER
	set_default_size( 750, 500 );

	add ( gameBox_ );

	Gtk::HBox* menu = Gtk::manage( new Gtk::HBox() );

	// Make the start button
	startButton_.signal_clicked().connect( sigc::mem_fun( *this, &View::on_start_game_clicked_) );
	startButton_.add_label("Start New Game");

    endButton_.signal_clicked().connect( sigc::mem_fun( *this, &View::on_end_game_clicked_) );
	endButton_.add_label("End Current Game");

	menu->pack_start( startButton_);
	menu->pack_start( endButton_);

    gameBox_.pack_start( *menu, Gtk::PACK_SHRINK );

	// Set the look of the frame.
	gameFrame_.set_label( "Cards on the table:" );
	gameFrame_.set_label_align( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
	gameFrame_.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	
	gameBox_.pack_start( gameFrame_, Gtk::PACK_SHRINK, true, 0 );

	
	for(int j = 0; j < 4; j++){
		for (int i = 0; i < 13; i++ ) {
			cards_[j][i] = new Gtk::Image( nullCardPixbuf );
			suit_[j].pack_start( *cards_[j][i] );
		}
		table_.pack_start( suit_[j], Gtk::PACK_SHRINK, true, 0 );
	}
    gameBox_.pack_start( table_, Gtk::PACK_SHRINK, true, 0 );

    for (int i = 0; i < 13; i++) { 
    	Gtk::Image *image = Gtk::manage( new Gtk::Image ( nullCardPixbuf ) );
    	currentHand_[i].set_image( *image );
    	currentHand_[i].signal_clicked().connect( sigc::bind(sigc::mem_fun( *this, &View::on_card_clicked_ ), i) );
    	hand_.pack_start( currentHand_[i], Gtk::PACK_SHRINK, true, 0 );
    }

    gameBox_.pack_start( hand_, Gtk::PACK_SHRINK);

    /*for (int i = 0; i < 13; i++) {
    	Gtk::Image *image = Gtk::manage( new Gtk::Image ( nullCardPixbuf ) );
    	currentHand_[i].set_image( *image );
    	currentHand_[i].signal_clicked().connect( sigc::bind(sigc::mem_fun( *this, &View::on_card_clicked_ ), i) );
    	hand_->pack_start( currentHand_[i], Gtk::PACK_SHRINK, true, 0 );
    }
    gameBox_.pack_start( *hand_, Gtk::PACK_SHRINK);*/

	// Register view as observer of model
	model_->subscribe(this);

	// The final step is to display the buttons (they display themselves)
	show_all();
	//update();
} // View::View

View::~View() {
	std::cout << "view destructor" << std::endl;
}

void View::on_start_game_clicked_(){
	StartGameDialogBox start(*this, "Initial Settings");
	std::cout << "1" << std::endl;
	vector<string> player = start.getTypes();
	std::cout << "1" << std::endl;
	seed_ = start.getSeed();
	std::cout << "2" << std::endl;
	model_->initializeTable(player);
	std::cout << "3" << std::endl;
	model_->start(seed_);
	std::cout << "4" << std::endl;
	controller_->startButtonClicked();
}

void View::on_end_game_clicked_(){
	controller_->endButtonClicked();
}

void View::on_card_clicked_( int i ){
	controller_->cardPlayedClicked( i );
}

void View::update() {
	// Suit suit = model_->suit();
	// Rank rank = model_->face();
	// if ( suit == NOSUIT ) 
	// 	card.set( deck.getNullImage() );
	// else
	// 	card.set( deck.getCardImage(suit, rank) );

}
