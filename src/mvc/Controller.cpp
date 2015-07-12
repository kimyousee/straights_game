#include "Controller.h"
#include "Model.h"

Controller::Controller(Model *m) : model_(m) {}

void Controller::play(Card card){
	model_->play(card);
}

void Controller::discard(Card card){
	model_->discard(card);
}

void Controller::deck(){
	model_->deck();
}

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