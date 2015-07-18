#include "Player.h"
#include <iostream>
#include <ostream>
#include <istream>
#include <string>

using namespace std;

Player::Player(int playerNumber, string playerType) {
	playerNumber_ = playerNumber;
	playerPoints_ = 0;
	playerType_ = playerType;
}

Player::~Player() {}

int Player::getPlayerPoints() {
	return playerPoints_;
}

int Player::getPlayerNumber() {
	return playerNumber_;
}

void Player::addPlayerPoints(int val) {
	playerPoints_ += val;
}

vector<Card*> Player::getPlayerHand() {
	return playerHand_;
}

vector<Card*> Player::getDiscardedHand() {
	return playerDiscards_;
}

void Player::incrementPlayerHand(Card* card) {
	playerHand_.push_back(card);
}

void Player::incrementDiscardedHand(Card* card) {
	playerDiscards_.push_back(card);
}

void Player::decrementPlayerHand(Card* card) {
	int i = 0;
	for (vector<Card*>::iterator it = playerHand_.begin() ; it != playerHand_.end();) {
		if ( (**it) == *card ) {
			playerHand_.erase( playerHand_.begin() + i );
		} else it++;
		i++;
	}
}

void Player::clearDiscards(){
	playerDiscards_.clear();
}

// reset all card info for the next round
int Player::calcPlayerPoints() {
	int tempPoints = 0;
	for (vector<Card*>::iterator it = playerDiscards_.begin() ; it != playerDiscards_.end(); ++it) {
		tempPoints += (*it)->getRankInt()+1;
	}
	return (tempPoints);
}
