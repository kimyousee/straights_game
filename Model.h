#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include <string>
#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Table.h"

class Model {
public:
	Model(){};
	~Model(){delete game_;}
	//Table* getTable();

	void start(int);
	void play(Card card);
	void discard(Card card);
	void deck();
	void quit();
	void ragequit();
	void cpuTurn();

	void initializeTable();
	void outputIfHumanPlayer();


private:
	void cpuPlayOrDiscard_();
	bool legalCardLookup_(Card);
	void incrCurrentPlayer_();
	void checkEndGame_();
	void outputEndGame_();
	std::vector<std::string> playerTypes_;
	int passes_ = 0; // for how many players are done
	Table* game_;
	Deck* deck_;
	// This is used to skip outputting if it is false
	bool outputHuman_ = true;
	int seed_;
};

#endif