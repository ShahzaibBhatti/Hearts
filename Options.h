#ifndef _OPTIONS_H__
#define _OPTIONS_H__
#include <iostream>
#include <fstream>

using namespace std;

class Options{
	public:
	static ifstream inFile; //Holds the file with the cards if sent in as a parameter
	static string playerList[4][3]; //Holds the players in game
	static int getMaxScore(); //Returns the maxScore
	static int getSeedValue(); //returns the seed value that was sent in as a parameter
	static bool seedEntered(); //Returns true if a seed was entered
	static bool deckEntered(); //Returns true if a deck file was submitted
	static void setOptions(int argc, char* argv[]); //Sets the options to be called at the beginning of the game

	private:
	static bool seedSet; //True if a seed has been set
	static bool deckSet; //True if a deck file was submitted
	static int maxScore; //Holds the max score to win the game
	static int seedValue; //if submitted, holds a seed value
};

#endif
