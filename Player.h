#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

// This class is abstract
// Possible players are HumanPlayer and ComputerPlayer
class Player {
public:
	Player(){}
	Player(int, std::string);                // Constructor
	virtual ~Player();                       // Destructor

	// Accessors
	int getPlayerPoints();
	int getPlayerNumber();
	std::vector<Card*> getPlayerHand();
	std::vector<Card*> getDiscardedHand();

	// Mutators
	void addPlayerPoints(int val);
	void decrementPlayerHand(Card* card);
	void incrementPlayerHand(Card* card);
	void incrementDiscardedHand(Card* card);
	void clearDiscards();

	virtual std::string getPlayerType() const = 0; //Computer "c" or Human "h"

	int calcPlayerPoints(); // reset all card info for the next round
protected:
	int playerNumber_;
	int playerPoints_;
	std::vector<Card*> playerHand_;
	std::vector<Card*> playerDiscards_;
	std::string playerType_;
};

#endif