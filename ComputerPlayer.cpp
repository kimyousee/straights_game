#include "ComputerPlayer.h"
#include "Player.h"
#include <string>

using namespace std;

ComputerPlayer::ComputerPlayer(int playerNumber) : Player(playerNumber, "c") {}

ComputerPlayer::ComputerPlayer(Player &player) {
	for (vector<Card*>::iterator it = player.getPlayerHand().begin() ; it != player.getPlayerHand().end(); ++it) {
		//this->incrementPlayerHand(*it);
		// this->playerHand_.push_back(new Card((*it)->getSuit(), (*it)->getRank()));
		this->playerHand_.push_back(*it);
	}

	for (vector< Card* >::iterator it = player.getDiscardedHand().begin() ; it != player.getDiscardedHand().end(); ++it) {
		//this->incrementDiscardedHand(*it);
		// this->playerDiscards_.push_back(new Card((*it)->getSuit(), (*it)->getRank()));
		this->playerDiscards_.push_back(*it);
	}

	this->playerNumber_ = player.getPlayerNumber();
	this->playerPoints_ = player.getPlayerPoints();
	this->playerType_ = "c";
}

string ComputerPlayer::getPlayerType() const {
	return (playerType_);
}