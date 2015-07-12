// View class 
// Responsible for buttons clicked and displaying cards

#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "Observer.h"
#include "Controller.h"
#include "Model.h"

class Controller;
class Model;

class View : public Gtk::Window, public Observer {
public:
	View (Controller*, Model*);
	virtual void update();

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Gtk::Frame
	// Gtk::HBox butBox; // stack buttons horizontally
	// Gtk::Button  
	// Gtk::Button

};


#endif