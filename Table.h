#ifndef TABLE_H
#define TABLE_H

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <string>

// Table holds the players and the played cards for the game
class Table {
public:
	Table(std::vector<std::string>); // Constructor
	~Table(); // Destructor

	// For modifying the played cards on the table
	std::vector<std::vector<int> >* getPlayedCards();
	void playCard(Card*);

	// Functions for current player
	int currentPlayerNumber() const; // accessor, returns the number of the player
	Player* currentPlayer() const;
	void changeCurPlayerOnTable(int);

	std::vector<Player*> players() {return listOfPlayers_;}
	int findStartingPlayer(); // For finding the player with 7S

	// Used for ragequit
	void replacePlayerWithCPU(ComputerPlayer*);

	bool getReset(){return reset_;}
	void setReset(bool b) {reset_ = b;}
	void reset();

	void setEnd(bool b) {end_ = b;}
	bool end(){return end_;}

private:
	std::vector<Player*> listOfPlayers_;
	Player* currentPlayer_;

	// The array of played cards.
	// This decides which cards can and cannot be played
	//   0 = not a legal move
	//   1 = card is on table
	//   2 = legal move
	std::vector<std::vector<int> >* playedCards_;

	bool reset_ = false; // set this to true when we start a new game
	bool end_ = false;   // set this to true to end the game
};

#endif
