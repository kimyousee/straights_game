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
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	DeckGUI deck_;

	Gtk::VBox vboxframe_;
	Gtk::HBox row_;
	Gtk::Frame frame_;
	// Gtk::Frame
	// Gtk::HBox butBox; // stack buttons horizontally
	// Gtk::Button  
	// Gtk::Button
	std::vector<Gtk::Image*> clubs_;
	std::vector<Gtk::Image*> diamonds_;
	std::vector<Gtk::Image*> spades_;
	std::vector<Gtk::Image*> hearts_;
	std::vector<std::vector<Gtk::Image*> > table_;

	Gtk::Button start_button_;

	// Signal handlers
	// select card
	// Start new game
	// Quit
	// Ragequit

};


#endif