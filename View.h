// View class 
// Responsible for buttons clicked and displaying cards

#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
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
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	DeckGUI deck_;

	// Gtk::Frame
	// Gtk::HBox butBox; // stack buttons horizontally
	// Gtk::Button  
	// Gtk::Button
	Gtk::Image card;

	// Signal handlers
	// select card
	// Start new game
	// Quit
	// Ragequit

};


#endif