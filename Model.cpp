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

// Start the game
void Model::start(int seed){
	if (!(game_->getReset())){
		seed_ = seed; // store seed for when we start a new game
		deck_ = new Deck(seed);
	} else {
		game_->reset();
	}
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
	Player* curPlayer = game_->currentPlayer();

	// Get card from player's hand
	Card* playerCard;
	vector<Card*> hand = curPlayer->getPlayerHand();

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

		incrCurrentPlayer_();
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
	checkEndGame_();
}

// Discard a card from the current player's hand unless
// the player has legal cards
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

	// Get card from player's hand
	Card* playerCard;

	for (vector<Card*>::iterator it = hand.begin(); it!=hand.end(); it++){
		if( (**it) == card )  playerCard = *it;
	}

	// When card is not legal and is not on the board already
	if (played[suit][rank] == 0) {
		Player* curPlayer = game_->currentPlayer();
		curPlayer->incrementDiscardedHand(playerCard);
		curPlayer->decrementPlayerHand(playerCard);
		cout << "Player " << game_->currentPlayerNumber() << " discards " << card << "." << endl;
		if (game_->currentPlayer()->getPlayerType() == "h") outputHuman_ = true;

		incrCurrentPlayer_();
	}
	checkEndGame_();
}

// Prints out the deck
void Model::deck(){
	deck_->printDeck();
}

void Model::quit(){}

// When a human player leaves, we must replace it by a ComputerPlayer
void Model::ragequit(){
	// Player* curPlayer = game_->currentPlayer();
	// cout << "Before making cpu" << endl;
	// ComputerPlayer* cpu = new ComputerPlayer(*curPlayer);
	// cout << "After making cpu, before replace" << endl;
	// game_->replacePlayerWithCPU(cpu);
	// cout << "done" << endl;
}

void Model::checkEndGame_(){
	vector<Card*> nextHand = game_->currentPlayer()->getPlayerHand();

	// If the next player is out of the game, proceed to next player
	if (nextHand.size() == 0) {
		while (nextHand.size() == 0){
			passes_ += 1;
			if (passes_ == 4){
				cout << "passed 4 players"<<endl;
				outputEndGame_();
				break;
			}
			incrCurrentPlayer_();
			nextHand = game_->currentPlayer()->getPlayerHand();

		}
		passes_ = 0;
	}
}

void Model::cpuTurn(){
	Player* curPlayer = game_->currentPlayer();
	// Check if current player is human
	if (curPlayer->getPlayerType() == "h") { return; }

	// while(!game_->getReset() && game_->currentPlayer()->getPlayerType() == "c"){
	while(!(game_->end()) && game_->currentPlayer()->getPlayerType() == "c"){
		cpuPlayOrDiscard_();
	}
}

void Model::cpuPlayOrDiscard_(){
	Player* curPlayer = game_->currentPlayer();
	vector<Card*> hand = curPlayer->getPlayerHand();
	vector<vector<int> >& played = *(game_->getPlayedCards());
	
	// ////
	// for (int i = 0; i < 4; i++){
	// 	for (int j = 0; j < 13; j++){
	// 		cout << played[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// ////
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
					if (j != 12) cout << " ";
				}
			}
			cout << endl;
		}

		cout << "Your hand: ";
		vector<Card*> hand = game_->currentPlayer()->getPlayerHand();
		for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
			cout << (**it);
			if (it != hand.end()-1) cout << " " ;
		}
		cout << endl;
		
		cout << "Legal plays: ";
		for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
			if (legalCardLookup_(**it)){
				cout << (**it);
				if (it != hand.end()-1) cout << " " ;
			}
		}
		cout << endl;
	}
}

void Model::outputEndGame_(){
	vector<Player*> players = game_->players();
	int points[4];
	bool end = false;
	for(int i = 0; i < 4; i++){
		Player* p = players[i];

		cout << "Player " << i+1 << "\'s discards: ";
		vector<Card*> discarded = p->getDiscardedHand();
		for(vector<Card*>::iterator it = discarded.begin(); it != discarded.end(); it++){
			cout << (**it) ;
			if (it != discarded.end() - 1) cout << " ";
		}
		cout << endl;

		cout << "Player " << i+1 << "\'s score: ";
		int oldPoints = p->getPlayerPoints();
		int newPoints = discarded.size();
		p->addPlayerPoints(newPoints);

		points[p->getPlayerNumber()-1] = p->getPlayerPoints();
		if (p->getPlayerPoints() >= 80) end = true;

		cout << oldPoints << " + " << newPoints << " = " << p->getPlayerPoints() << endl;
	}
	// Output winners if points are greater than 80
	// else start a new game
	if (end){
		cout << "Ending a game" << endl;
		int lowest = points[0];
		int lowestPlayer[4] = {1,0,0,0};
		for (int i = 1; i < 4; i++){
			if (points[i] < lowest) {
				lowest = points[i];
				fill(lowestPlayer, lowestPlayer+4, 0); // reset array to 0s
				lowestPlayer[i] = 1;
			} else if (points[i] == lowest){
				lowestPlayer[i] = 1;
			}
		}
		for (int i = 0; i < 4; i++){
			if (lowestPlayer[i] == 1){
				cout << "Player " << i+1 << " wins!" << endl;
			}
		}
		game_->setEnd(true); // end the game
		exit(0);
	} else {
		game_->setReset(true);
		cout << "Starting a new game" << endl;
		start(seed_);
	}
}

bool Model::legalCardLookup_(Card card){
	int suit = card.getSuitInt();
	int rank = card.getRankInt();
	vector<vector<int> >& played = *(game_->getPlayedCards());
	if (played[suit][rank] == 2) return true;
	return false;
}

void Model::incrCurrentPlayer_(){
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

