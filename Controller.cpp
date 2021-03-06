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

// // Used to check the current deck
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
	model_->outputIfHumanPlayer();
}

void Controller::cpuTurn(){
	model_->cpuTurn();
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