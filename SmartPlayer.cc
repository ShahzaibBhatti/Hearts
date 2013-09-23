#include "SmartPlayer.h"
#include "Player.h"
#include "Card.h"
#include "CardPile.h"
#include "Trick.h"

SmartPlayer::SmartPlayer(string playerName):Player(playerName){}

SmartPlayer::~SmartPlayer(){}

Card* SmartPlayer::throwOff(){

	Card *c =findCard(Card::QueenOfSpades);//find QueenOfSpades

	if (c != NULL) //return immediately if we have it (QueenOfSpades)
		return c;

	//otherwise find highest heart
	c = findRankWithSuit(true, Card::Hearts);

	if (c == NULL) //find highest card if no heart
		return findRank(true);

	return c;
}

Card* SmartPlayer::followSuit(Card::Suit leadSuit, Card::Rank trump){
	
	Card*c =NULL;
	
	//find first card in hand lower than trump with lead suit
	for (int i =0; i < hand->size(); i++){
		if (hand->at(i)->getSuit() == leadSuit && trump > hand->at(i)->getRank()){
			c = hand->at(i);
			break;
		}
	}
	
	if ( c !=NULL){ //Case A: highest card lower than trump with leadsuit
		for (int i = 0; i < hand->size(); i++){
			if (hand->at(i)->getRank() > c->getRank() //must be highest rank
			    && hand->at(i)->getRank() < trump //but lower than trump
			    && hand->at(i)->getSuit() == leadSuit){ //and same suit
				c = hand->at(i);
			}//if
		}//for
	}//if
	
	else //Case B: lowest ranking card with same suit
		c = findRankWithSuit(false, leadSuit);
	
	return c;

}

Card* SmartPlayer::lead(){
	return findRank(false); //find minimum rank
}

/* finds first occurence of a card witha given suit in the hand
   used primarily for having a starting card to compare rest of the hand to 
   (i.e.,when finding Max/Min rank in the hand) */
Card* SmartPlayer::findFirstSuit(Card::Suit suit) const{

	for (int i =0; i < hand->size(); i++){
		if (hand->at(i)->getSuit() == suit){
			return hand->at(i); //return first Card with desired suit
		}
	}
	return NULL;
}

//find the max/mn rank in a hand with a given suit
Card * SmartPlayer::findRankWithSuit(bool findMax, Card::Suit suit) const{
	//find an instance of desired suit in hand to check against
	Card *c = findFirstSuit(suit);

	for (int i = 0; i < hand->size(); i++){
		if (findMax && hand->at(i)->getSuit() == suit
		    && hand->at(i)->getRank() > c->getRank()){
			c = hand->at(i);
		}// find max card with desired suit
		else if (!findMax && hand->at(i)->getSuit() == suit  
		         && hand->at(i)->getRank() < c->getRank()){
			c = hand->at(i);
		}// find min card with desired suit
	}
	return c;
}

//find max/min rank regardless of suit
Card * SmartPlayer::findRank(bool findMax) const{
	Card *c = hand->at(0);
	for (int i = 1; i < hand->size(); i++){
		/* since no 2 cards will ever be equal in a player's hand,
		   we do not have to check for equality in the first condition */
		if (findMax && !(*hand->at(i) < *c)){
			c = hand->at(i);
		}//find max Card
		else if (!findMax && *hand->at(i) < *c){
			c = hand->at(i);
		}//find min Card
	}
	return c;
}

