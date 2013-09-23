#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "CardPile.h"
#include "Card.h"

class Player{
	public:
	Player (string playerName);//sets player name, 0 score, and empty hand
	virtual ~Player();//deletes the hand, NOT my responsibility to delete the cards in my hand!

	/* playCard with Suit & Rank: im not the first to play in the trick, removes played Card from hand
	   to increase abstarction, we do not send in pointer to Trump, rather the rank and suit*/
	Card* playCard(Card::Suit leadSuit, Card::Rank trump);
	
	//calls either throwOff, followSuit, or lead, and sets the playedCard field, removes played Card from hand
	Card* playCard(); //playCard without trump: I'm the first to play in the trick

	void dealCard(Card* dealtcard); //give a card to the player
	void printName() const;
	void increaseScore(unsigned int heartsValue); //increases score by heartsValue
	unsigned int getScore () const;
	void printScore () const;
	virtual void printHand() const; 
	bool hasTwoOfClubs () const; //returns true if player has the TwoOfClubs (to see if this player should lead)
	bool hasCard (Card *c) const; //returns true if player has card

	private:
	virtual Card* throwOff() =0;
	virtual Card* followSuit(Card::Suit leadSuit, Card::Rank trump) =0;
	virtual Card* lead() =0;
	//returns the Card in the hand that was played, Card is removed from player's hand, NOT deleted

	protected:
	void removeCard(Card* c); //removes a Card from player's hand
	Card * findCard(Card c) const; //finds a specific Card in the hand (for QueenOfSpades, TwoOfClubs)
	//returns the Card back if it is found, otherwise returns NULL
	CardPile *hand; //each player's hand
	unsigned int score; //hearts value of all the cards in the
	string name;
};


#endif
