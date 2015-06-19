#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include <string>

// The computer plays and discards cards automatically
//
// Specified at the beginning of the game
// or when a human player rage quits
class ComputerPlayer : public Player {
public:
	ComputerPlayer(int playerNumber);
	ComputerPlayer(Player &player);
	~ComputerPlayer(){};

	virtual std::string getPlayerType() const;

};

#endif