#include "SmartPlayer.h"
#include "Player.h"
#include "Card.h"
#include "CardPile.h"
#include "Trick.h"
#include "HumanPlayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(string playerName):Player(playerName){}

HumanPlayer::~HumanPlayer(){}

Card* HumanPlayer::throwOff(){
	return lead(); //both lead and throwOff is the same for a human player
}

void HumanPlayer::printHand() const{
  cout << "Human player ";
  printName();
  cout << " has these cards:\n";
  Player::printHand(); //call parent method
}

/* read in a valid Card (does not check if it is in the player's hand)
   returns When last entered string is valid */
string HumanPlayer::readValidString(){
    
    string cs = "";
    while (true){
        cout << "\nWhat card would you like to play, ";
        printName();
        cout << "? ";
        cin >> cs; //read Card
        
        if (Card::stringIsALegalCard(cs))
            break; //break When Card is valid
            
    	cout << cs << " is not a card";
	}
	return cs;
}

Card* HumanPlayer::followSuit(Card::Suit leadSuit, Card::Rank trump){
	
	Card c;
	printHand(); //show player's hand
	string cs = readValidString();
	c = Card(cs); //make the card the player wants to play

	//here we check of the lead card has the same suit and that the player has it
	while (c.getSuit() != leadSuit || !hasCard(&c)){
	    if (!hasCard(&c)){
	    	cout << c << " is not in your hand\n"; //not in hand
	    }
	    else{ //otherwise it the player had the card, then it was the wrong suit
            cout << "You have at least one ";
            if (leadSuit == Card::Spades)
                cout << "S";
            if (leadSuit == Card::Diamonds)
                cout << "D";
            if (leadSuit == Card::Clubs)
                cout << "C";
            if (leadSuit == Card::Hearts)
                cout << "H";
            cout << "; you must follow suit!";
	    }
        cs = readValidString(); //read another valid string
		c = Card(cs);
	}
	return findCard(c); //we then find the card in the hand when all checks are done

}

/* almost exact copy of followSuit for a human player,
   except we do not check the suit */
Card* HumanPlayer::lead(){
    
    Card c;
	printHand();
	string cs = readValidString();
	c = Card(cs);
	
	//just check if player has the card
	while (!hasCard(&c)){
	    cout << c << " is not in your hand\n";
        cs = readValidString(); //if not, then read in another vaid string to test
		c = Card(cs);
	}
	return findCard(c); 
}
