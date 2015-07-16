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

enum State { INIT_GAME, START_GAME, CARD_PLAYED, CARD_DISCARDED, END_GAME, RAGE_QUIT, INCR_PLAYER};

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
	void endGame();
	void ragequit();

	// Not commands but called from controller
	void initializeTable(std::vector<std::string> player);
	void outputIfHumanPlayer();
	void cpuTurn();

	State getState();
	std::vector<std::vector<int> >* getPlayedCards();
	Card* getPlayedCard();
	Player* getCurrentPlayer();
	std::vector<Player*> getPlayers();
	Card* getCardClicked(int i);
	int getNumLegalPlays();

	bool legalCardLookup(Card);

private:
	void cpuPlayOrDiscard_();
	void incrCurrentPlayer_();
	void checkEndGame_();
	void outputEndGame_();
	void setState_(State);

	std::vector<std::string> playerTypes_;
	Table* game_;
	Deck* deck_;
	State state_;

	int passes_; // for how many players are done playing this round
	bool outputHuman_; // This is used to skip outputting if it is false
	int seed_; // For Deck's shuffle
};

#endif