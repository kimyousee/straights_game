// Hi
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
	//playerHand_ = NULL;
	//playerDiscards_ = NULL;
}

Player::~Player() {
	// while (!playerHand_.empty()) {
	// 	delete playerHand_.back();
	// 	playerHand_.pop_back();
	// }

	// while (!playerDiscards_.empty()) {
	// 	delete playerDiscards_.back();
	// 	playerDiscards_.pop_back();
	// }
}

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
	// Card* newCard = new Card(card.getSuit(), card.getRank());
	playerHand_.push_back(card);
}

void Player::incrementDiscardedHand(Card* card) {
	// Card* newCard = new Card(card.getSuit(), card.getRank());
	playerDiscards_.push_back(card);
}

void Player::decrementPlayerHand(Card* card) {
	int i = 0;
	for (vector<Card*>::iterator it = playerHand_.begin() ; it != playerHand_.end();) {
		if ( (**it) == *card ) {
			// delete (*it);
			playerHand_.erase( playerHand_.begin() + i );
		} else it++;
		i++;
		/*if ( ((*it)->getSuitInt() == card.getSuitInt()) && ((*it)->getRankInt() == card.getRankInt()) ) {
			//incrementDiscardedHand(card);
			delete (*it);
			playerHand_.erase( playerHand_.begin() + it );
		}*/
	}
}

// virtual string Player::getPlayerType() const = 0; //Computer or Human // why ?

// reset all card info for the next round
void Player::resetPlayer() {
	for (vector<Card* >::iterator it = playerHand_.begin() ; it != playerHand_.end(); ++it) {
    	delete (*it);
   	} 
   	playerHand_.clear();

   	int tempPoints = 0;
   	for (vector<Card*>::iterator it = playerDiscards_.begin() ; it != playerDiscards_.end(); ++it) {
   		tempPoints += (*it)->getRankInt();
    	delete (*it);
   	} 

   	addPlayerPoints(tempPoints);
   	playerDiscards_.clear();
} 
