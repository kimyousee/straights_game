#include "DialogBox.h"
#include <gtkmm/stock.h>
#include <gtkmm/entry.h>
#include <iostream>

using namespace std;

DialogBox::DialogBox(Gtk::Window & parentWindow, string title, string message) : Dialog( title, parentWindow, true, true ) {
	Gtk::Label messageLabel(message);

	// Obtain the dialog box's vertical alignment box.
	Gtk::VBox* contentArea = this->get_vbox();
	contentArea->pack_start( messageLabel, Gtk::PACK_SHRINK, true, false );

	// Add a standard "ok" buttons_ with the appropriate responses when clicked.
	Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();

	// Wait for a response from the dialog box.
	int result = run();
	switch (result) {
		case Gtk::RESPONSE_OK:
			break;
	}
}