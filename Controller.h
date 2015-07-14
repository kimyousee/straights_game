#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include "Card.h"
class Model;

class Controller {
public:
  Controller(Model*);
  void play(Card);
  void discard(Card);
  // void deck();
  void quit();
  void ragequit();
  void outputIfHumanPlayer();
  void cpuTurn();
  void startButtonClicked();
private:
  Model *model_;
};

#endif