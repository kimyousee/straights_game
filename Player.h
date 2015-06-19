#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

class Player {
public:
	Player(){};
	Player(int playerNumber, std::string playerType);
	virtual ~Player();

	int getPlayerPoints();
	void addPlayerPoints(int val);

	int getPlayerNumber();

	std::vector<Card*> getPlayerHand();
	std::vector<Card*> getDiscardedHand();
	void decrementPlayerHand(Card* card);
	void incrementPlayerHand(Card* card);
	void incrementDiscardedHand(Card* card);

	virtual std::string getPlayerType() const = 0; //Computer or Human

	int calcPlayerPoints(); // reset all card info for the next round
protected:
	int playerNumber_;
	int playerPoints_;
	std::vector<Card*> playerHand_;
	std::vector<Card*> playerDiscards_;
	std::string playerType_;
};

/*
class ComputerPlayer: public Player {

};

class HumanPlayer: public Player {

};
*/

#endif