#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include <string>
#include <vector>
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
	void cpuPlayOrDiscard();
	bool legalCardLookup(Card);
	void incrCurrentPlayer();
	void checkEndGame();
	void outputEndGame();
	std::vector<std::string> playerTypes_;
	int passes_ = 0; // for how many players are done
	Table* game_;
	Deck* deck_;
	bool outputHuman_ = true; // This is used to skip outputting if it is false
};

#endif