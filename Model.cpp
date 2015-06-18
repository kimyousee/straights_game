#include "Model.h"
#include <iostream>
#include <string>

using namespace std;

namespace {
	void printIntsToRank(int rank){
	    string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
		cout << ranks[rank];
	} 

}

void Model::initializeTable() {
	string playerTypeStr;
	for (int i = 0; i < 4; i++) {
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl;
		cout << ">";
		cin >> playerTypeStr;
		playerTypes_.push_back(playerTypeStr);
	}
	game_ = new Table(playerTypes_);
}

bool Model::legalCardLookup(Card card){
	int suit = card.getSuitInt();
	int rank = card.getRankInt();
	vector<vector<int> >& played = *(game_->getPlayedCards());
	if (played[suit][rank] == 2) return true;
	return false;
}

void Model::incrCurrentPlayer(){
	// After playing the card, it's the next player's turn
	Player* curPlayer = game_->currentPlayer();
	int playerNum = curPlayer->getPlayerNumber();
	if (playerNum < 4){
		// note that parameter is playerNum - 1 + 1
		// -1 for vector accessing and +1 to increment
		game_->changeCurPlayerOnTable(playerNum);
	} else if (playerNum == 4){
		game_->changeCurPlayerOnTable(0);
	}
}

void Model::start(int seed){
	deck_ = new Deck(seed);
	deck_->shuffle();
	deck_->dealCards(game_->players());
	int start = game_->findStartingPlayer();

	cout << "A new round begins. It's player " << start << "'s turn to play." << endl;

}

// Play a card if it is legal to do so
// Note that in the table, game_, 
//   0 = not a legal move
//   1 = card is on the table
//   2 = legal move
void Model::play(Card card){
	int suit = card.getSuitInt();
	int rank = card.getRankInt();
	vector<vector<int> >& played = *(game_->getPlayedCards());

	// Get card from player's hand
	Card* playerCard;
	vector<Card*> hand = game_->currentPlayer()->getPlayerHand();
	for (vector<Card*>::iterator it = hand.begin(); it!=hand.end(); it++){
		if( (**it) == card )  playerCard = *it;
	}
	// When the card is legal to play
	if (played[suit][rank] == 2){
		played[suit][rank] = 1;
		game_->playCard(playerCard);
		cout << "Player " << game_->currentPlayerNumber() << " plays " << card << "." << endl;

		Player* curPlayer = game_->currentPlayer();
		curPlayer->decrementPlayerHand(&card);

		incrCurrentPlayer();
		if (game_->currentPlayer()->getPlayerType() == "h") outputHuman_ = true;		

	} // When the card is already played 
	else if (played[suit][rank] == 1){
		// card is on the table already...
	} // When the card is not a legal move
	else if (played[suit][rank] == 0){
		cout << "This is not a legal play." << endl;
		outputHuman_ = false;
		// note it's still the same person's turn
	}
}

void Model::discard(Card card){
	int suit = card.getSuitInt();
	int rank = card.getRankInt();
	vector<vector<int> >& played = *(game_->getPlayedCards());
	Player* curPlayer = game_->currentPlayer();
	vector<Card*> hand = curPlayer->getPlayerHand();

	// Check for legal plays
	for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
		int suitTemp = (*it)->getSuitInt();
		int rankTemp = (*it)->getRankInt();

		// When card is legal
		if (played[suitTemp][rankTemp] == 2){
			cout << "You have a legal play. You may not discard." << endl;
			outputHuman_ = false;
			return;
		}
	}

	// When card is not legal and is not on the board already
	if (played[suit][rank] == 0) {
		Player* curPlayer = game_->currentPlayer();
		curPlayer->incrementDiscardedHand(&card);
		curPlayer->decrementPlayerHand(&card);
		cout << "Player " << game_->currentPlayerNumber() << " discards " << card << "." << endl;
		if (game_->currentPlayer()->getPlayerType() == "h") outputHuman_ = true;

		incrCurrentPlayer();
	}
}

// Prints out the deck
void Model::deck(){
	deck_->printDeck();
}

void Model::quit(){}

void Model::ragequit(){
	// Player* curPlayer = game_->currentPlayer();
	// cout << "Before making cpu" << endl;
	// ComputerPlayer* cpu = new ComputerPlayer(*curPlayer);
	// cout << "After making cpu, before replace" << endl;
	// game_->replacePlayerWithCPU(cpu);
	// cout << "done" << endl;
}

void Model::cpuTurn(){
	Player* curPlayer = game_->currentPlayer();
	// Check if current player is human
	if (curPlayer->getPlayerType() == "h") { return; }

	while(game_->currentPlayer()->getPlayerType() == "c"){
		cpuPlayOrDiscard();
	}
}

void Model::cpuPlayOrDiscard(){
	Player* curPlayer = game_->currentPlayer();
	vector<Card*> hand = curPlayer->getPlayerHand();
	vector<vector<int> >& played = *(game_->getPlayedCards());

	bool playedCard = false;
	for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
		int suitTemp = (*it)->getSuitInt();
		int rankTemp = (*it)->getRankInt();

		// When card is legal, play it
		if (played[suitTemp][rankTemp] == 2){
			play(**it);
			playedCard = true;
			break;
		}
	}

	// When there are no legal cards in the hand, discard.
	if (!playedCard){
		discard(*(hand[0]));
	}
}

void Model::outputIfHumanPlayer(){
	if (!outputHuman_) return;
	if (game_->currentPlayer()->getPlayerType() == "h"){
		vector<vector<int> >& played = *(game_->getPlayedCards());
		
		// // For debugging the playedCards_ vector
		// for (int i = 0; i < 4; i++){
		// 	for (int j = 0; j < 13; j++){
		// 		cout << played[i][j] << " ";
		// 	}
		// 	cout << endl;
		// }


		cout << "Cards on the table:" << endl;
		
		for(int i = 0; i<4; i++){
			if (i == 0)      cout << "Clubs: ";
			else if (i == 1) cout << "Diamonds: ";
			else if (i == 2) cout << "Hearts: ";
			else             cout << "Spades: ";
			for(int j = 0; j<13; j++){
				if (played[i][j] == 1) { // when card is on the table
					printIntsToRank(j);
					cout << " ";
				}
			}
			cout << endl;
		}

		cout << "Your hand: ";
		vector<Card*> hand = game_->currentPlayer()->getPlayerHand();
		for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
			cout << (**it) << " " ;
		}
		cout << endl;
		
		cout << "Legal plays: ";
		for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
			if (legalCardLookup(**it)){
				cout << (**it) << " " ;
			}
		}
		cout << endl;
	}
}

// Table* Model::getTable() {
// 	return game_;
// }
