#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <string>

class Table {
public:
	Table(){};
	~Table();
	Table(std::vector<std::string>);
	std::vector<std::vector<int> >* getPlayedCards(); // syntax for ret val?
	void playCard(Card*);
	int currentPlayerNumber() const; // accessor, returns the number of the player
	Player* currentPlayer() const;
	// std::vector<Player*> players() {return *listOfPlayers_;}
	std::vector<Player*> players() {return listOfPlayers_;}
	int findStartingPlayer();
	void changeCurPlayerOnTable(int);
	void replacePlayerWithCPU(ComputerPlayer*);
	bool getReset(){return reset_;}
	void setReset(bool b) {reset_ = b;}
	void reset();
	//vector<Deck> getPlayedCards();

private:
	std::vector<Player*> listOfPlayers_;
	Deck* gameDeck_; //change name after?
	// The array of played cards.
	// This decides which cards can and cannot be played
	//   0 = not a legal move
	//   1 = card is on table
	//   2 = legal move
	// int playedCards_[4][13] = {0};
	std::vector<std::vector<int> >* playedCards_;
	Player* currentPlayer_;
	bool reset_ = false; // set this to true when we start a new game
};

#endif
