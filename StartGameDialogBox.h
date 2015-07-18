#ifndef START_GAME_BOX
#define START_GAME_BOX

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/radiobutton.h>
#include <string>
#include <vector>

// A dialog box that appears when the user clicks on the "Start New Game" button
// This dialog lets the user set the seed and
// the type of each player (ie Human Player or Computer Player)
class StartGameDialogBox : Gtk::Dialog {
public:
	StartGameDialogBox(Gtk::Window & parentWindow, std::string title);
	std::vector<std::string> getTypes();
	int getSeed();
	virtual ~StartGameDialogBox();

private:
	// Used to group the radio buttons so only one can be active at a time.
	Gtk::RadioButton::Group group1_;
	Gtk::RadioButton::Group group2_;
	Gtk::RadioButton::Group group3_;
	Gtk::RadioButton::Group group4_;
	// Buttons for the messages for players 1-4
	std::vector<Gtk::RadioButton *> buttons1_;
	std::vector<Gtk::RadioButton *> buttons2_;
	std::vector<Gtk::RadioButton *> buttons3_;
	std::vector<Gtk::RadioButton *> buttons4_;
	std::vector<std::string> chosenTypes_;
	int seed_;
};


#endif