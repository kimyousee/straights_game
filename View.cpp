#include "View.h"
#include "Table.h"
#include "Player.h"
#include "Card.h"
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
	vector<string> player = start.getTypes();
	seed_ = start.getSeed();
	model_->initializeTable(player);
	model_->start(seed_);
	controller_->startButtonClicked();
}

void View::on_end_game_clicked_(){
	controller_->endButtonClicked();
}

void View::on_card_clicked_( int i ){
	controller_->cardPlayedClicked( i );
}

void View::display_current_hand_(){
	Player* p = model_->getCurrentPlayer();
	vector<Card*> cards = p->getPlayerHand();
	for (int i = 0; i < cards.size(); i++){
		Card* c = cards[i];
		Glib::RefPtr<Gdk::Pixbuf> cardImage = deck_.getCardImage(c->getSuit(), c->getRank());

		Gtk::Image *image = Gtk::manage( new Gtk::Image ( cardImage ) );
		currentHand_[i].set_image( *image );
	}
}

void View::update() {
	State currentState = model_->getState();
	switch (currentState){
		case INIT_GAME:
			// code to show if players are computers or humans
			break;
		case START_GAME:
			display_current_hand_();
			break;
	}
}
