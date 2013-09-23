#ifndef _TRICK_H__
#define _TRICK_H__
#include "CardPile.h"
#include "Card.h"

class Trick : public CardPile {

	public:
	Trick();
	virtual ~Trick();
	
	//adds a card to the trick
	void addCard(Card *c); //updates trump card, and sets leadSuit if necessary
	Card * getTrumpCard() const;

	private:
	Card * trumpCard; //current trump Card (highest rank of leadSuit)

};



#endif
