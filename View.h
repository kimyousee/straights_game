// View class 
// Responsible for buttons clicked and displaying cards

#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include <vector>
#include "DeckGUI.h"
#include "Observer.h"
#include "Subject.h"
#include "Controller.h"
#include "Model.h"

class Controller;
class Model;

class View : public Gtk::Window, public Observer {
public:
	View (Controller*, Model*);
	~View();
	virtual void update();

private:
	void on_start_game_clicked_();
	void on_end_game_clicked_();
	void on_card_clicked_( int i );
	void on_rage_clicked_( int i );

	void display_current_hand_();
	void display_played_card_();
	void display_players_();
	void increment_discards_();
	void clear_table_();

	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	int seed_;

	DeckGUI deck_;

	//Widgets
	Gtk::VBox table_;
	Gtk::VBox gameBox_;

	Gtk::HBox suit_[4];
	Gtk::HBox hand_;
	Gtk::HBox player_;

	Gtk::Image *cards_[4][13]; // Images to display.

	Gtk::Button startButton_;
	Gtk::Button endButton_;
	Gtk::Button currentHand_[13];

	Gtk::Button playerRagequit_[4];
	std::vector<int> playerScore_;
	std::vector<int> playerDiscards_;

	Gtk::Frame playerFrame_[4];

	std::vector<std::string> playerTypes_;

	Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf_;

	//std::vector<Gtk::Image*> clubs_;
	//std::vector<Gtk::Image*> diamonds_;
	//std::vector<Gtk::Image*> spades_;
	//std::vector<Gtk::Image*> hearts_;
	//std::vector<std::vector<Gtk::Image*> > table_;
	// Signal handlers
	// select card
	// Start new game
	// Quit
	// Ragequit

};


#endif
