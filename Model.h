#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include <string>
#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Table.h"

// Model controls the game and holds all logic
class Model {
public:
	Model(){};
	~Model(){delete game_;}

	// Commands called from controller
	void start(int);
	void play(Card card);
	void discard(Card card);
	void deck();
	void quit();
	void ragequit();

	// Not commands but called from controller
	void initializeTable();
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

	int passes_ = 0; // for how many players are done
	// This is used to skip outputting if it is false
	bool outputHuman_ = true;
	int seed_; // For Deck's shuffle
};

#endif