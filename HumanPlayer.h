#ifndef _HUMANPLAYER_H__
#define _HUMANPLAYER_H__

#include "Player.h"
#include "Card.h"

class HumanPlayer : public Player{
	public:
	HumanPlayer (string playerName);
	virtual ~HumanPlayer();

	private:
	Card * throwOff();
	Card * followSuit(Card::Suit leadSuit, Card::Rank trump);
	Card * lead();
	void printHand() const; //overrided from Player, to print additional information
	string readValidString(); //read in a valid string (to be interpreted as a Card)
};



#endif
