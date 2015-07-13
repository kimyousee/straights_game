#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"
#include <istream>

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command{
	Type type;
	Card card;
	
	Command() : type(BAD_COMMAND), card(SPADE, ACE) {}
	bool operator== (const Type& t) const {
		if (type == t){
			return true;
		} else {
			return false;
		}
	}

};

std::istream &operator>>(std::istream &, Command &);


#endif