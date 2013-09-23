#include <iostream>
#include <string>
#include <cassert>
#include <map>
#include <fstream>
#include "CardPile.h"
#include "Deck.h"
#include <stdlib.h>
#include "Card.h"
#include "Options.h"
#include "Player.h"
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "Trick.h"

//A variation on the game of hearts as defined by Assignment 6
//Shahzaib Bhatti, Daniyal Khan

using namespace std;

int main (int argc, char* argv[]) {
    const int NUMBER_OF_PLAYERS = 4;
    //Will start on round 1, end on round 13
    const int NUMBER_OF_HANDS_MIN = 1;
    const int NUMBER_OF_HANDS_MAX = 13;

    vector<Player*> listOfPlayers; //Holds all the players in a vector, known to be maxSize of NUMBER_OF_PLAYERS
    int currentHand = 1; //Keeps track of the rounds and sets the first to one
    int currentPlayer; //Keeps track of the current player being operated on
    bool playGame = true;

    //Creates the neccessary cardpiles not associated to players for the game
    Options::setOptions(argc, argv); //parse command line inputs
    Deck *gameDeck = new Deck();
    Trick *trick = new Trick(); //Tricks are for kids

    //If a seed was set in the options, change the seed for the gamedeck, done here to avoid class interaction
    if (Options::seedEntered())
        gameDeck->setRandomSeed(Options::getSeedValue());


    //Create the players as set by the user, Smart be default
    for (int j = 0; j < 4; j++){
        if (Options::playerList[j][1] == "R"){ //random player
            Player *tmpPlayer = new RandomPlayer(Options::playerList[j][0], (atoi(Options::playerList[j][2].c_str())));
            listOfPlayers.push_back(tmpPlayer);
        }
        else if (Options::playerList[j][1] == "H"){ //human player
            Player *tmpPlayer = new HumanPlayer(Options::playerList[j][0]);
            listOfPlayers.push_back(tmpPlayer);
        }
        else{ //smart player
            Player *tmpPlayer = new SmartPlayer(Options::playerList[j][0]);
            listOfPlayers.push_back(tmpPlayer);
        }
    }
    while (playGame){
        if (Options::deckEntered() && currentHand == 1)
            Options::inFile >> *gameDeck; //If a deck was entered, ONLY use that order the first round
        else
            gameDeck->generate();
        gameDeck->shuffle();
        if (currentHand ==1)
            cout <<  "\n\n";
        cout << "At the beginning of hand " << currentHand << ", here is the deck:\n";
        gameDeck->print();
        cout << "\n";

        //Deal the cards to the players
        for (int i = 0; i < 52; i++){
            /* deal to all players start at player number (i%4)*/
            listOfPlayers.at(((i%4 + (currentHand%4+3)%4)%4))->dealCard(gameDeck->at(51-i));
        } //Note: ((i%4 + (currentHand%4+3)%4)%4) Takes care of the rotating player each round

        //Prints the hand for each player
        cout << "\n\nHere are the hands for each player at the start of hand number " << currentHand << "\n\n";
        for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
            listOfPlayers.at(i)->printName();
            cout << " has these cards:\n";
            listOfPlayers.at(i)->Player::printHand();
            cout << "\n\n";
            //Whoever has the two of clubs, set them to the starting player
            if (listOfPlayers.at(i)->hasTwoOfClubs())
                currentPlayer = i;
        }

        //Play a round of the game (will always be 13 hands)
        for (int i = NUMBER_OF_HANDS_MIN; i <= NUMBER_OF_HANDS_MAX; i++){
            cout << "\nNow starting round " << i << " of hand " << currentHand << "\n";
            //Player is told to play lead
            Card* c = listOfPlayers.at(currentPlayer)->playCard();
            trick->addCard(c); //Adds the card from the hand to the trick
            cout << "  ";
            listOfPlayers.at(currentPlayer)->printName();
            if (i == NUMBER_OF_HANDS_MIN)
                cout << " has " << *c << " and leads with it" << "\n";
            else
                cout << " led " << *c << "\n";

            for (int j = 1; j < NUMBER_OF_PLAYERS; j++){
                Card * trump = trick->getTrumpCard(); //the trump card of the trick

                //Player is told to play a card depending on lead, follow suit, or throw off
                Card* c = listOfPlayers.at((currentPlayer+j)%4)->playCard(trump->getSuit(), trump->getRank());
                trick->addCard(c); //Adds the card from the hand to the trick
                cout << "  ";
                listOfPlayers.at((currentPlayer+j)%4)->printName();

                if (c->getSuit() == trump->getSuit())
                    cout << " followed suit with " << *c << "\n";
                else
                    cout << " threw off " << *c << "\n";
            }

            //Find out who has the trump card
            for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
                if (trick->at(i) == trick->getTrumpCard()){
                    currentPlayer = (currentPlayer+i)%4; //currentPlayer can be >0, mod4 to prevent exceeding 3
                    break;
                }
            }

            //Declares the winner of the trick
            cout << "  ";
            listOfPlayers.at(currentPlayer)->printName();
            cout << " won the trick and added the following cards:\n";
            trick->print();
            cout << "\n";
            listOfPlayers.at(currentPlayer)->increaseScore(trick->getHeartsValue()); //Adds to the players score
            trick->remove(); //removes all cards fom trick (does not delete them)
        }

        //Prints out the score for each player
        cout << "\nAt the end of hand " << currentHand++ << ", the score is:\n";
        for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
            cout << "    ";
            listOfPlayers.at(i)->printName();
            cout << "  ";
            listOfPlayers.at(i)->printScore();
            cout << "\n";
        }

        cout << "\n";
        gameDeck->remove(); //Empties the deck and deletes the cards

        //Check if the game is over, ie. someone reached the max score
        for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
            if (listOfPlayers.at(i)->getScore() >= Options::getMaxScore())
                playGame = false;
        }
        if (playGame)
            cout << "\n";
    }


    cout << "The game is over.\n";
    //Find out who exceeded the score limit
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
        if (listOfPlayers.at(i)->getScore() >= Options::getMaxScore()){
            currentPlayer = i;
            break; //Will always break
        }
    }

    listOfPlayers.at(currentPlayer)->printName();
    cout << " has exceeded " << Options::getMaxScore() << " points.\n";
    cout << "The winner is ";

    currentPlayer = NUMBER_OF_PLAYERS - 1; //Sets the last player as winner be default
    //Changes the winner to someone to the left of this player depending on who has a lower score
    for (int i = NUMBER_OF_PLAYERS - 1; i >= 0; i--){
        if (listOfPlayers.at(i)->getScore() <= listOfPlayers.at(currentPlayer)->getScore())
            currentPlayer = i;
    }
    listOfPlayers.at(currentPlayer)->printName();
    cout << "\n";

    //Removes all allocated memory
    delete (gameDeck);
    delete (trick);
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++)
        delete (listOfPlayers.at(i));
}
