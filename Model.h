#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include <string>
#include <vector>
#include <cstdlib>
#include "Subject.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Table.h"
#include <iostream>
#include <string>
#include <vector>

// Model controls the game and holds all logic
// Is a subject for the Observer pattern; it will notify all Observers
class Model : public Subject {
public:
	Model();
	~Model(){std::cout << "before" << std::endl; delete game_; std::cout << "after :)" << std::endl;}

	// Commands called from controller
	void start(int);
	void play(Card card);
	void discard(Card card);
	// void deck();
	void quit();
	void ragequit();

	// Not commands but called from controller
	void initializeTable(std::vector<std::string> player);
	void outputIfHumanPlayer();
	void cpuTurn();

private:
	void cpuPlayOrDiscard_();
	bool legalCardLookup_(Card);
	void incrCurrentPlayer_();
	void checkEndGame_();
	void outputEndGame_();

	std::vector<std::string> playerTypes_;
	Table* game_;
	Deck* deck_;

	int passes_; // for how many players are done playing this round
	bool outputHuman_; // This is used to skip outputting if it is false
	int seed_; // For Deck's shuffle
};

#endif