#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include <string>

class HumanPlayer : public Player {
public:
    HumanPlayer(int playerNumber);
    virtual std::string getPlayerType() const;
    ~HumanPlayer(){};
};

#endif