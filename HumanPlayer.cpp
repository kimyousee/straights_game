#include "HumanPlayer.h"
#include "Player.h"
#include <string>

using namespace std;

HumanPlayer::HumanPlayer(int playerNumber) : Player(playerNumber, "h") {}

string HumanPlayer::getPlayerType() const {
 	return (playerType_);
}
