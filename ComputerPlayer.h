#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include <string>

class ComputerPlayer : public Player {
public:
    ComputerPlayer(int playerNumber);
    ComputerPlayer(Player &player);
    ~ComputerPlayer(){};

    virtual std::string getPlayerType() const;

    //void playCard(Table* table);
    //void discardCard(Table* table);
};

#endif