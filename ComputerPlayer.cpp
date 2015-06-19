#include "ComputerPlayer.h"
#include "Player.h"
#include <string>

using namespace std;

ComputerPlayer::ComputerPlayer(int playerNumber) : Player(playerNumber, "c") {}

ComputerPlayer::ComputerPlayer(Player &player) {

	vector<Card*> hand = player.getPlayerHand();
	for (vector<Card*>::iterator it = hand.begin() ; it != hand.end(); it++) {

		this->playerHand_.push_back(*it);
	}
	vector<Card*> discHand = player.getDiscardedHand();
	for (vector< Card* >::iterator it = discHand.begin() ; it != discHand.end(); ++it) {
		this->playerDiscards_.push_back(*it);
	}
	this->playerNumber_ = player.getPlayerNumber();
	this->playerPoints_ = player.getPlayerPoints();
	this->playerType_ = "c";
}

string ComputerPlayer::getPlayerType() const {
	return (playerType_);
}