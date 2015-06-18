#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
}

Suit Card::getSuit() const{
	return suit_;
}

Rank Card::getRank() const{
	return rank_;
}

// Returns an int corresponding to the Rank
// Needed for accessing the array of played cards
int Card::getRankInt() const{
	// switch (rank_){
	// 	case ACE: return 0; break;
	// 	case TWO: return 1; break;
	// 	case THREE: return 2; break;
	// 	case FOUR: return 3; break;
	// 	case FIVE: return 4; break;
	// 	case SIX: return 5; break;
	// 	case SEVEN: return 6; break;
	// 	case EIGHT: return 7; break;
	// 	case NINE: return 8; break;
	// 	case TEN: return 9; break;
	// 	case JACK: return 10; break;
	// 	case QUEEN: return 11; break;
	// 	case KING: return 12; break;
	// 	default: break;
	// }
	int rank = rank_;
	return rank;
}

int Card::getSuitInt() const{
	// switch (suit_){
	// 	case CLUB: return 0; break;
	// 	case DIAMOND: return 1; break;
	// 	case HEART: return 2; break;
	// 	case SPADE: return 3; break;
	// 	default: break;
	// }
	int suit = suit_;
	return suit;
}


bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

ostream &operator<<(ostream &out, const Card &c){
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
		
	out << ranks[c.getRank()] << suits[c.getSuit()];
	
	return out;
}

istream &operator>>(istream &in, Card &c){
	string suits = "CDHS", ranks = "A234567891JQK";
	
	string str;
	in >> str;
	assert ( !in.fail() );
	
	//Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranks.find( str.at(0) );
	assert ( c.rank_ != string::npos );
	
	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == TEN ){
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}
	
	//Read in the suit, make sure it's valid
	c.suit_ = (Suit)suits.find( str.at(1) );
	assert ( c.suit_ != string::npos );
	
	return in;
}