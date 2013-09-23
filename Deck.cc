#include "Deck.h"
#include "CardPile.h"
#include "Card.h"
#include <stdlib.h>
#include<iostream>
using namespace std;

//appended all cards into onestring to make a 'deckString'
const string fullDeck = "2S3S4S5S6S7S8S9STSJSQSKSAS2D3D4D5D6D7D8D9DTDJDQDKDAD2C3C4C5C6C7C8C9CTCJCQCKCAC2H3H4H5H6H7H8H9HTHJHQHKHAH";
const int FULL_DECK_SIZE = fullDeck.length()/2; //ensure above is divisible by 2

Deck::Deck (): CardPile() {}


//Deck is responsible for deleting the Cards
Deck::~Deck(){}


void Deck::generate(){
    for (int i = 0; i < FULL_DECK_SIZE ; i++ ){
        Card *drawnCard = new Card(fullDeck.substr (i*2,2));//start from (i*2)th character and generate card length 2
        push_back(drawnCard);
    }
    playingWithAFullDeck();//check just in case
}

/*  Full Deck Criteria:
	(1) Every card in deck is valid
	(2) There are 52 cards in the deck
	(3) No 2 cards are the same

if reading in a Deck, we have already checked that each card is a valid card */
bool Deck::playingWithAFullDeck () const{

    for (int i = 0; i < size(); i++){
        for (int j = i + 1; j < size(); j++){
            if (*at(i) == *at(j)){//check every card against every other card to see if any are duplicated
                cerr <<"Error, incomplete deck.  Aborting." <<endl;
                for (int k = 0; k < 52; k++){
                    if (k==0)
                        cerr << "    ";
                    cerr << *at(k) << " ";
                }
                cerr << "\n";
                exit(2);
            }
        }//for
    }//for

    if (size()!=FULL_DECK_SIZE){
    	cerr << "Error,  is not a legal card. Aborting.\n";
        exit(2);
    }
    return true;
}

void  Deck::remove(){
	for (int i = 0 ; i < size();){
	    delete(at(i));
		erase(i+begin());
	}
}

extern istream& operator>> (istream& in, Deck& deck){
    int numCards = 0;
    string cardString;
    Card *c;
    while (in >> cardString) //keep reading cards
    {
        if (!Card::stringIsALegalCard(cardString)){ //check that each card is a legal
            cerr << "Error, " << cardString << " is not a legal card. Aborting.\n";
            exit (1);
        }
        c = new Card(cardString);
        deck.push_back(c);
        numCards++;
    }

    deck.playingWithAFullDeck(); //exits (2) if not a full deck
    return in;
}
