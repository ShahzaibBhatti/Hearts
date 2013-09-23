#ifndef _RANDOMPLAYER_H__
#define _RANDOMPLAYER_H__

#include "Player.h"
#include "Card.h"

class RandomPlayer : public Player{	
	public:
	RandomPlayer (string playerName, uint32_t seed);
	virtual ~RandomPlayer();

	private:
	PRNG prng; //to hold the seed for generating random Cards
	Card * throwOff();
	Card * followSuit(Card::Suit leadSuit, Card::Rank trump);
	Card * lead();
};


#endif
