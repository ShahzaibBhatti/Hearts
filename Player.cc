#include "Player.h"
#include "Card.h"
#include "CardPile.h"
#include <iostream>
using namespace std;

Player::Player(string playerName): name(playerName), score(0), hand(new CardPile()) {}

Player::~Player(){delete hand;}
//delete hand since we allocated memory for CardPile

Card* Player::playCard(Card::Suit leadSuit, Card::Rank trump){
	
	for (int i =0; i < hand->size(); i++){
		if (hand->at(i)->getSuit() == leadSuit){
			Card *c = followSuit(leadSuit, trump); 
			//at least one of the same suit in the hand
			removeCard(c); //remove card from hand
			return c;
		}
	}
	Card *c = throwOff(); //no same suits, run throwOff algorithm
	removeCard(c); //remove card from hand
	return c;
}
Card* Player::playCard(){

    Card *c = findCard(Card::TwoOfClubs); //check if we have 2 of clubs

    if (c==NULL)
    c = lead();//play a lead card (not 2 of clubs)

	removeCard(c); //remove card from hand
	return c;
}

void Player::dealCard(Card* dealtCard){
	hand->push_back(dealtCard); //adds a card to the back of the hand 
}

void Player::printName() const{
	cout << name;
}

void Player::increaseScore(unsigned int heartsValue){
	score +=heartsValue; 
}

unsigned int Player::getScore() const{
	return score;
}

void Player::printScore() const{
	cout << score;
}

void Player::removeCard(Card *c){
	for (int i = 0 ; i< hand->size(); i++){
		if (*hand->at(i) == *c){
			hand->erase(i+hand->begin());//remove ith index (which is a pointer to a card) from hand
			//Careful, we must not delete the removed card!
			break;
		}
	}
}

void Player::printHand() const{
	hand->print();
}

bool Player::hasTwoOfClubs() const{
	if (findCard(Card::TwoOfClubs)) //find TwoOfClubs
		return true;
	else
		return false;
}

bool Player::hasCard(Card* c) const{ //external use function
	if (findCard( *c) == NULL)
		return false;
	else
		return true;
}

Card * Player::findCard(Card c) const{ //internl use function
	for (int i = 0 ; i < hand->size(); i++){
		if (*hand->at(i)== c)
			return hand->at(i);
	}
	return NULL;
}
