#include <vector>
#include <algorithm>
#include <iostream>
#include "CardPile.h"
#include "Card.h"

using namespace std;

const uint32_t CardPile::DefaultRandomSeed = 37;

CardPile::CardPile() : prng(DefaultRandomSeed) {}

CardPile::~CardPile (){/*Do not delete Cards here */}

int CardPile::getHeartsValue() const{
    int heartValue = 0;
    for (int i = 0; i < size() ; i++) {
        heartValue+=at(i)->getHeartsValue(); //get heartsValue of each Card in pile
    }
    return heartValue;
}

void CardPile::setRandomSeed(uint32_t randomSeed) {
	prng.seed(randomSeed);
}

void CardPile::print() const
{
	cout <<"    ";
    for (int i = 0; i < size(); i++)
        cout << *at(i) << " ";
}

void CardPile::shuffle() {
	for (int i = size() - 1; i > 0; i--) {
		const int j = prng(i);
		Card* tmp = at(j);
		at(j) = at(i);
		at(i) = tmp;
	}
}

//removes each Card from the vector
void CardPile::remove(){
	for (int i = 0 ; i < size();){
		erase(i+begin()); 
	}
}
