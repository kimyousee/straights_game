#include "Controller.h"
#include "Model.h"
#include "Card.h"
#include <iostream>
#include "DialogBox.h"

Controller::Controller(Model *m) : model_(m) {}

void Controller::play(Card card){
	model_->play(card);
}

void Controller::discard(Card card){
	model_->discard(card);
}

// void Controller::deck(){
// 	model_->deck();
// }

void Controller::quit(){
	model_->quit();
}

void Controller::ragequit(){
	model_->ragequit();
}

void Controller::outputIfHumanPlayer(){
	//model_->outputIfHumanPlayer();
}

void Controller::cpuTurn(){
	model_->cpuTurn();
}

// Not actually used to start a game.
// Use this to create an empty game, waiting for the user to 'Start New Game'
void Controller::initEmptyGame(){
	std::vector<std::string> types;
	types.push_back("h");
	types.push_back("h");
	types.push_back("h");
	types.push_back("h");	

	model_->initializeTable(types);
}

void Controller::startButtonClicked(std::vector<std::string> playerTypes, int seed){
	model_->initializeTable(playerTypes);
	model_->start(seed);
}

void Controller::endButtonClicked(){
	model_->endGame();
}

void Controller::rageButtonClicked( int i ){
	model_->ragequit();
	
}