#include "View.h"
#include "Table.h"
#include "Player.h"
#include "Card.h"
#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <string>
#include "DeckGUI.h"
#include "StartGameDialogBox.h"
#include "DialogBox.h"

using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), hand_(true,10), table_(true,10), gameBox_(false,10) {
	nullCardPixbuf_ = deck_.getNullCardImage();
	
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

	Gtk::VBox* cardArea = Gtk::manage( new Gtk::VBox() );
	Gtk::Label *cardLabel = new Gtk::Label( "Cards on the table:" );
	cardLabel->set_alignment( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
	cardArea->pack_start( *cardLabel);
	gameBox_.pack_start( *cardArea, Gtk::PACK_SHRINK );
	cardLabel->show();

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 13; i++ ) {
			cards_[j][i] = new Gtk::Image( nullCardPixbuf_ );
			suit_[j].pack_start( *cards_[j][i] );
		}
		table_.pack_start( suit_[j], Gtk::PACK_SHRINK, true, 0 );
	}
	gameBox_.pack_start( table_, Gtk::PACK_SHRINK, true, 0 );

	/*
	for (int i = 0; i < 4; i++ ) {
		pScore_.push_back(0);
		pDiscards_.push_back(0);
	}
	*/

	for ( int i = 0; i < 4; i++ ) {
		Gtk::VBox* playerArea = Gtk::manage( new Gtk::VBox(true, 0 ) );

		playerRagequit_[i].set_label( "Rage!" );
		playerRagequit_[i].signal_clicked().connect( sigc::bind(sigc::mem_fun( *this, &View::on_rage_clicked_ ), i) );
		stringstream temp_i; temp_i << (i+1);
		Gtk::Label *playerLabel = new Gtk::Label( "Player " + temp_i.str() );
		playerRagequit_[i].set_sensitive(false);
		playerLabel->set_alignment( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
		//stringstream temp_score; temp_score << pScore_[i];
		pScore_.push_back(0);
		playerScore_[i] = new Gtk::Label( "0 points" );
		//stringstream temp_disc; temp_disc << pDiscards_[i];
		pDiscards_.push_back(0);
		playerDiscards_[i] = new Gtk::Label( " 0 discards" );

		playerArea->pack_start( *playerLabel );
		playerArea->pack_start( playerRagequit_[i] );
		playerArea->pack_start( *playerScore_[i] );
		playerArea->pack_start( *playerDiscards_[i] );

		playerFrame_[i].add( *playerArea );
		player_.pack_start( playerFrame_[i]);
	}

	gameBox_.pack_start( player_, Gtk::PACK_SHRINK, true, 0 );


	Gtk::VBox* handArea = Gtk::manage( new Gtk::VBox() );
	Gtk::Label *handLabel = new Gtk::Label( "Your Hand:" );
	handLabel->set_alignment( Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP );
	handArea->pack_start( *handLabel);
	gameBox_.pack_start( *handArea, Gtk::PACK_SHRINK );
	handLabel->show();

	//Display empty 13 cards
	for (int i = 0; i < 13; i++) { 
		Gtk::Image *image = Gtk::manage( new Gtk::Image ( nullCardPixbuf_ ) );
		currentHand_[i].set_image( *image );
		currentHand_[i].set_sensitive(false);
		currentHand_[i].signal_clicked().connect( sigc::bind(sigc::mem_fun( *this, &View::on_card_clicked_ ), i) );
		hand_.pack_start( currentHand_[i], Gtk::PACK_SHRINK, true, 0 );
	}

	gameBox_.pack_start( hand_, Gtk::PACK_SHRINK);

	Gtk::VBox* playerLegalCardsArea = Gtk::manage( new Gtk::VBox() );
	playerLegalCards_ = new Gtk::Label( "" );
	playerLegalCards_->set_padding ( 10, 10 );
	playerLegalCardsArea->pack_start( *playerLegalCards_ );
	gameBox_.pack_start( *playerLegalCardsArea );

	Gtk::VBox* playerTurnArea = Gtk::manage( new Gtk::VBox() );
	playerTurn_ = new Gtk::Label( "" );
	// playerTurn_->override_color(Gdk::RGBA("red"));
	playerTurn_->set_padding ( 15, 15 );
	playerTurnArea->pack_start( *playerTurn_ );
	gameBox_.pack_start( *playerTurnArea );

	// Register view as observer of model
	model_->subscribe(this);

	// The final step is to display the buttons (they display themselves)
	show_all();
}

// Destructor
View::~View() {}

// Signal Handlers

void View::on_start_game_clicked_() {
	StartGameDialogBox start(*this, "Initial Settings");
	playerTypes_ = start.getTypes();
	seed_ = start.getSeed();

	controller_->startButtonClicked(playerTypes_, seed_);
}

void View::on_end_game_clicked_() {
	controller_->endButtonClicked();
}

void View::on_card_clicked_( int i ) {
	Card* card = model_->getCardClicked(i);
	int legalMoves = model_->getNumLegalPlays();
	if (legalMoves == 0){
		//increment_discards_();
		controller_->discard(*card);
	} else {
		if (model_->legalCardLookup(*card)){
			//std::cout << "cardPlayed: " << i << *card << std::endl;
			controller_->play(*card);
		} else {
			stringstream ss; ss << "Invalid Play: '" << *card << "'' is not a legal move." ;
			DialogBox start(*this, "ERROR", ss.str());
		}
	}
}

void View::on_rage_clicked_( int i ) {
	playerTypes_[i] = "c";
	controller_->rageButtonClicked( i );
}

// Helper functions

void View::display_current_hand_() {
	//const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf_ = deck_.getNullCardImage();

	Player* p = model_->getCurrentPlayer();

	stringstream ss; ss << p->getPlayerNumber();
	playerTurn_->set_label( "Player " + ss.str() + "'s Turn" );

	playerLegalCards_->set_label ( "Legal Play(s): " + get_legal_plays_() );

	vector<Card*> cards = p->getPlayerHand();
	for (int i = 0; i < cards.size(); i++){
		Card* c = cards[i];
		Glib::RefPtr<Gdk::Pixbuf> cardImage = deck_.getCardImage(c->getSuit(), c->getRank());
		Gtk::Image *image = Gtk::manage( new Gtk::Image ( cardImage ) );
		currentHand_[i].set_image( *image );
		currentHand_[i].set_sensitive(true);
	}
	for (int i = cards.size(); i < 13; i++) {
		Gtk::Image *image = Gtk::manage( new Gtk::Image ( nullCardPixbuf_ ) );
		currentHand_[i].set_image( *image );
		currentHand_[i].set_sensitive(false);
	}
	model_->outputIfHumanPlayer();
}

void View::display_played_card_() {
	Card* card = model_->getPlayedCard();
	int suit = card->getSuitInt();
	int rank = card->getRankInt();
	Glib::RefPtr<Gdk::Pixbuf> cardImage = deck_.getCardImage(card->getSuit(), card->getRank());
	// Gtk::Image *image = Gtk::manage( new Gtk::Image ( cardImage ) );
	cards_[suit][rank]->set(cardImage);
}

void View::display_players_() {
	// vector<Player*> players = model_->getPlayers();
	// for (int i = 0; i < 4; i++){
	// 	string type = players[i]->getPlayerType(); // "h" or "c"
	// 	if (type == "c"){
	// 		// disable rage button
	// 		// change label to CPU
	// 	} else {
	// 		// change label to Human Player
	// 	}
	// }
}

void View::display_ending_dialog_() {
	int winner = model_->getWinner();
	stringstream ss; ss << "Player " << winner << " has won the game!";
	DialogBox start(*this, "Congratulations!", ss.str());
}

void View::display_score_dialog_() {
	DialogBox start(*this, "Results", model_->getRecentScores());
}

void View::update_scores_() {
	vector<int> scores = model_->getPlayersScores();
	for (int i = 0; i < 4; i++){
		pScore_[i] += scores[i];
		stringstream ss; ss << pScore_[i];
		playerScore_[i]->set_label(ss.str() + " points");
	}
}

void View::increment_discards_() {
	int i = get_current_player_number_();
	pDiscards_[i] += 1;
	stringstream ss; ss << pDiscards_[i];
	playerDiscards_[i]->set_label(ss.str() + " discards");
}

void View::clear_table_(bool continueGame) {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 13; i++ ) {
			cards_[j][i]->set( nullCardPixbuf_ );
		}
	}
	for (int i = 0; i < 13; i++) {
		Gtk::Image *image = Gtk::manage( new Gtk::Image ( nullCardPixbuf_ ) );
		currentHand_[i].set_image( *image );
		currentHand_[i].set_sensitive(false);
	}
	for (int i = 0; i < 4; i++ ) {
		if (!continueGame){
			pScore_[i] = 0;
			playerScore_[i]->set_label("0 points");
		}
		pDiscards_[i] = 0;
		playerDiscards_[i]->set_label("0 discards");
		playerRagequit_[i].set_sensitive(false);
	}

	playerTurn_->set_label( " " );

	playerLegalCards_->set_label ( " " );

}

void View::set_rage_button_(bool enable) {
	int playerNumber = get_current_player_number_();
	string pType = playerTypes_[playerNumber];
	if (enable && pType == "h") {
		playerRagequit_[playerNumber].set_sensitive(true);
	} else {
		playerRagequit_[playerNumber].set_sensitive(false);
	}
}

int View::get_current_player_number_() {
	return model_->getCurrentPlayer()->getPlayerNumber() -1;
}

void View::check_cpu_turn_() {
	string pType = playerTypes_[get_current_player_number_()];
	if (pType == "c")
		model_->cpuTurn();
}

string View::get_legal_plays_() {
	stringstream ss;
	vector<Card*> hand = model_->getCurrentPlayer()->getPlayerHand();
	for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
		if (model_->legalCardLookup(**it)){
			ss << **it << " ";
		}
	}
	return (ss.str());
}

// Update for the MVC and Observer pattern
void View::update() {
	State currentState = model_->getState();
	switch (currentState){
		case INIT_GAME:
			clear_table_(false);
			// code to show if players are computers or humans
			display_players_();
			break;
		case START_GAME:
			set_rage_button_(true);
			display_current_hand_();
			check_cpu_turn_();
			break;
		case CARD_PLAYED:
			set_rage_button_(false);
			display_played_card_();
			//set_rage_button_(true);
			break;
		case CARD_DISCARDED:
			increment_discards_();
			set_rage_button_(false);
			break;
		case END_GAME:
			clear_table_(false);
			break;
		case RAGE_QUIT:
			//disable_rage_button_();
			break;
		case INCR_PLAYER:
			// cout << "player type: " << playerTypes_[get_current_player_number_()] << endl;
			set_rage_button_(true);
			display_current_hand_(); //Display the next player's hand
			check_cpu_turn_();
			break;
		case GAME_FINISHED:
			display_score_dialog_();
			display_ending_dialog_();
			clear_table_(false);
			break;
		case GAME_RESET:
			display_score_dialog_();
			update_scores_();
			clear_table_(true);
			break;
	}

}
