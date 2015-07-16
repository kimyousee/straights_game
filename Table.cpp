#include "Table.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
Table::Table(std::vector<std::string> playerTypes) {
	// listOfPlayers_ = NULL;
	reset_ = false;
	end_ = false;
	for (int i = 0; i < 4; i++) {
		if (playerTypes[i] == "h") {
			listOfPlayers_.push_back(new HumanPlayer(i+1));
		} else if (playerTypes[i] == "c") {
			listOfPlayers_.push_back(new ComputerPlayer(i+1));
		}
    }

    // Create playedCards
    playedCards_ = new vector<vector<int> >(4, vector<int>(13,0));
    (*playedCards_)[3][6] = 2; // Make 7S spot a legal play
    
}

Table::~Table(){
	cout << "before Table" << endl;
	cout << listOfPlayers_.size() << endl;
	cout << "why" << endl;
	while (!listOfPlayers_.empty()){
		cout << "before (while)" << endl;
		delete listOfPlayers_.back();
		cout << "after (while)" << endl;
		listOfPlayers_.pop_back();
	}
	delete playedCards_;
	cout << "after Table" << endl;
}

// Returns the player number; from 1 to 4
int Table::currentPlayerNumber() const {
	return currentPlayer_->getPlayerNumber();
}

vector<vector<int> >* Table::getPlayedCards(){ return playedCards_;}

Card* Table::getPlayedCard(){
	return playedCard_;
}

void Table::playCard(Card* card) {
	int suit = card->getSuitInt();
	int rank = card->getRankInt();
	playedCard_ = card;
	vector<vector<int> >& cards = *getPlayedCards();
	// Set legal plays for adjacent cards
	if (rank <= 11 && cards[suit][rank+1] != 1) cards[suit][rank+1] = 2;
	if (rank >= 1 && cards[suit][rank-1] != 1) cards[suit][rank-1] = 2;

	// Set legal plays for this card's suit
	if (rank == 6) {
		for (int i = 0; i <= 3; i++){
			if (cards[i][rank] != 1) {
				cards[i][rank] = 2;
			}
		}
	}
	cards[suit][rank] = 1;
}

int Table::findStartingPlayer(){
	for(int i = 0; i < 4; i++){
		vector<Card*> hand = listOfPlayers_[i]->getPlayerHand();
		for (vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
			if((*it)->getSuit() == SPADE && (*it)->getRank() == SEVEN){
				currentPlayer_ = listOfPlayers_[i];
				return i+1;
			}
		}
	}
	return 0; // 7S was not found
}

Player* Table::currentPlayer() const{
	return currentPlayer_;
}

void Table::changeCurPlayerOnTable(int newCurrent){
	currentPlayer_ = listOfPlayers_[newCurrent]; 
}

// the cpu passed in should have been constructed with the player passed in
void Table::replacePlayerWithCPU(ComputerPlayer* cpu){
	int index = currentPlayerNumber()-1;
	Player* temp = listOfPlayers_[index];
	listOfPlayers_[index] = cpu;
	delete temp;
	currentPlayer_ = cpu;
}

void Table::reset(){
	for (vector<vector<int> >::iterator it = (*playedCards_).begin(); it != (*playedCards_).end(); it++){
		fill((*it).begin(), (*it).end(), 0);
	}
	(*playedCards_)[3][6] = 2; // Make 7S spot a legal play
}
