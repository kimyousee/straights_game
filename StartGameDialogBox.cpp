#include "StartGameDialogBox.h"
#include <gtkmm/stock.h>
#include <gtkmm/entry.h>
#include <iostream>

using namespace std;

namespace {
	// Set up a group of radio buttons
	void addRadioButtons(Gtk::VBox* contentArea, vector<Gtk::RadioButton *>* b, Gtk::RadioButton::Group* group, vector<string> text){
		for (int i = 0; i < (signed)text.size(); i++){
			b->push_back(Gtk::manage( new Gtk::RadioButton( *group, text[i] ) ) );
			contentArea->add(*((*b)[i])); // *b?
		}
	}
}

StartGameDialogBox::StartGameDialogBox(Gtk::Window & parentWindow, string title) : Dialog( title, parentWindow, true, true ) {
	Gtk::Label seedLabel("Please enter seed: ");
	Gtk::Entry seedField;

	Gtk::Label p1Label("Choose player 1 type: ");
	Gtk::Label p2Label("Choose player 2 type: ");
	Gtk::Label p3Label("Choose player 3 type: ");
	Gtk::Label p4Label("Choose player 4 type: ");

	vector<string> types;
	types.push_back( "Human Player" );
	types.push_back( "Computer Player" );

	// Obtain the dialog box's vertical alignment box.
	Gtk::VBox* contentArea = this->get_vbox();
	contentArea->pack_start( seedLabel, true, false );
	contentArea->pack_start( seedField, true, false );

	contentArea->pack_start( p1Label, true, false );
	addRadioButtons(contentArea, &buttons1_, &group1_, types);
	contentArea->pack_start( p2Label, true, false );
	addRadioButtons(contentArea, &buttons2_, &group2_, types);
	contentArea->pack_start( p3Label, true, false );
	addRadioButtons(contentArea, &buttons3_, &group3_, types);
	contentArea->pack_start( p4Label, true, false );
	addRadioButtons(contentArea, &buttons4_, &group4_, types);
	

	// Make the first button the initial active choice.
	vector<vector<Gtk::RadioButton *> > buttons = {buttons1_,buttons2_,buttons3_,buttons4_};
	for (int i = 0; i < 4; i++) buttons[i][0]->set_active();
	// buttons1_[0]->set_active();
	// buttons2_[0]->set_active();
	// buttons3_[0]->set_active();
	// buttons4_[0]->set_active();

	// Add a standard "ok" buttons_ with the appropriate responses when clicked.
	Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();

	// Wait for a response from the dialog box.
	int result = run();
	cout << "before switch" <<endl;
	switch (result) {
		case Gtk::RESPONSE_OK:
			seed_ = atoi((seedField.get_text()).c_str());
			cout << "in switch: " << seed_ << endl;
			for (int i = 0; i < 4; i++){
				if (buttons[i][0]->get_active()){
					chosenTypes_.push_back("h");
				} else {
					chosenTypes_.push_back("c");
				}
			}
			break;
	}
}

StartGameDialogBox::~StartGameDialogBox() {
	for ( int i = 0; i < buttons1_.size(); i++ ) delete buttons1_[i];
	buttons1_.clear();
	for ( int i = 0; i < buttons2_.size(); i++ ) delete buttons2_[i];
	buttons2_.clear();
	for ( int i = 0; i < buttons3_.size(); i++ ) delete buttons3_[i];
	buttons3_.clear();
	for ( int i = 0; i < buttons4_.size(); i++ ) delete buttons4_[i];
	buttons4_.clear();
}

vector<string> StartGameDialogBox::getTypes(){
	return chosenTypes_;
}

int StartGameDialogBox::getSeed(){
	return seed_;
}