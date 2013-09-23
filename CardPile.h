#ifndef _CARDPILE_H_
#define _CARDPILE_H_

using namespace std;

#include <vector>
#include "Card.h"
#include "PRNG.h"

class CardPile : private vector<Card*> {
    public:
	// Constructors and destructor
	CardPile ();
	virtual ~CardPile (); //DOES NOT DELETE THE CARDS IN THE PILE

	void setRandomSeed(uint32_t randomSeed);
	void print() const;
	void shuffle();
	int getHeartsValue() const; //gets heartsValue of all Cards in the pile

	virtual void remove(); //removes all Cards from the vector

	//'exported' accessor functions
	using vector<Card*>::begin;
	using vector<Card*>::size;
	using vector<Card*>::at;
	using vector<Card*>::push_back;
	using vector<Card*>::empty;
	using vector<Card*>::erase;

    private:
	PRNG prng;
	static const uint32_t DefaultRandomSeed;
};

#endif
