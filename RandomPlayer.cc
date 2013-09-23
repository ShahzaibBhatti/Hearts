#include "RandomPlayer.h"
#include "Player.h"
#include "Card.h"
#include "CardPile.h"
#include <iostream>

using namespace std;

RandomPlayer::RandomPlayer(string playerName, uint32_t seed): Player(playerName), prng(seed) {}

RandomPlayer::~RandomPlayer(){}

Card * RandomPlayer::throwOff(){
  return lead();//for a random player, lead is the same as throwOff
}

Card * RandomPlayer::followSuit(Card::Suit leadSuit, Card::Rank trump){
	int numSuits =0;
	for (int i = 0; i < hand->size(); i++){
		if (hand->at(i)->getSuit() == leadSuit)
			numSuits++; //count number of leadSuit cards in hand
	}
	//min value of numSuits is 1, since we know we have at least one leadSuit in the hand

	int nthSuit = prng(0, numSuits-1); 
	//generate a random number from 0 to number of suits-1, call it n

	for (int i = 0; nthSuit>=0; i++){
		if (hand->at(i)->getSuit() == leadSuit){
			nthSuit--;
			if (nthSuit ==-1) //nth suit
				return hand->at(i);
		}//if
	}//for
}

Card* RandomPlayer::lead(){
	return hand->at(prng(0, hand->size()-1)); //generate a random number between 0 and size of hand -1
}
