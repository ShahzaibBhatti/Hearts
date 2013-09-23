#ifndef _SMARTPLAYER_H__
#define _SMARTPLAYER_H__

#include "Player.h"

class SmartPlayer : public Player{
	public:
	SmartPlayer (string playerName);
	virtual ~SmartPlayer();

	private:
	Card* throwOff();
	Card* followSuit(Card::Suit leadsuit, Card::Rank trump);
	Card* lead();
	
	//functions used in throwOff(), followSuit(), and lead()
	
	Card* findRankWithSuit(bool findMax, Card::Suit suit) const; 
	/* find either max or min rank in hand of a certain suit
	   if no suit is found, returns NULL*/
	   
	Card* findFirstSuit(Card::Suit suit) const; 
	/* find find first card with desired suit
	   if no suit is found, returns NULL*/
	   
	Card* findRank(bool findMax) const; 
	/* returns the card in the hand with highest/lowest rank
	   if multiple highest/lowest ranks, returns LAST one in hand*/
	
};


#endif
