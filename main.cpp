
#include <gtkmm/main.h>
#include "Model.h"
#include "Controller.h"
#include "View.h"
#include "Command.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main( int argc, char * argv[] ) {
	// Initialize gtkmm with the command line arguments, as appropriate.
	Gtk::Main  kit( argc, argv );

	Model model;
	Controller controller(&model);

	View view(&controller, &model);

	Gtk::Main::run(view);

	return 0;
}