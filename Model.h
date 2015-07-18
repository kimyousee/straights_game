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

enum State { INIT_GAME, START_GAME, END_GAME, GAME_FINISHED, GAME_RESET, SHOW_POINTS,
			 CARD_PLAYED, CARD_DISCARDED, RAGE_QUIT, INCR_PLAYER};

// Model controls the game and holds all logic
// Is a subject for the Observer pattern; it will notify all Observers
class Model : public Subject {
public:
	Model();
	~Model(){ if (game_ != NULL) delete game_; }

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
	std::vector<int> getPlayersScores();
	int getNumLegalPlays();
	int getWinner();
	std::string getRecentScores();

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
	int winner_;
	std::string output_scores_;
	int turnCount_;

	int passes_; // for how many players are done playing this round
	bool outputHuman_; // This is used to skip outputting if it is false
	int seed_; // For Deck's shuffle
};

#endif