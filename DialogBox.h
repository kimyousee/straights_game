#ifndef DIALOG_BOX
#define DIALOG_BOX

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <string>

class DialogBox : Gtk::Dialog {
public:
	DialogBox(Gtk::Window & parentWindow, std::string title, std::string message);
	virtual ~DialogBox(){};
};

#endif