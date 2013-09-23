#include <vector>
#include "Trick.h"
#include "CardPile.h"
#include "Card.h"
using namespace std;

Trick::Trick(): CardPile() {}

Trick::~Trick() {}

void Trick::addCard(Card *c){
	push_back(c);
	if (size() == 1){
		trumpCard = c;
	}

	else if (c->getRank() > trumpCard->getRank() && c->getSuit() == trumpCard->getSuit() )
		trumpCard = c;
}

Card * Trick::getTrumpCard() const{
 return trumpCard;
}
