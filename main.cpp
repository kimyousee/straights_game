#include "Model.h"
#include "Controller.h"
#include "Command.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main( int argc, char * argv[] ) {
	Model model;
	Controller controller(&model);
	Command cmd;

	// For reading in an integer for Deck's shuffle
	int seed = 0;
	if (argc == 2){
		seed = atoi(argv[1]);
	}

	model.initializeTable();
	model.start(seed);

	while (cmd.type != QUIT){
		controller.cpuTurn();
		controller.outputIfHumanPlayer();

		cout << ">";
		cin >> cmd;
		
		if (cmd == BAD_COMMAND ) break;
		if (cmd.type == PLAY) {
			controller.play(cmd.card);
		} else if (cmd.type == DISCARD){
			controller.discard(cmd.card);
		} else if (cmd.type == DECK) {
			controller.deck();
		} else if (cmd.type == RAGEQUIT){
			controller.ragequit();
		}
	}
	return 0;
}