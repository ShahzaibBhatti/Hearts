#include "Options.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

int Options::maxScore = 40; //Sets default max score
int Options::seedValue = 37; //Sets default seed
bool Options::seedSet = false; //Seed is originally not set by user
bool Options::deckSet = false; //Deck is originally not set by user
ifstream Options::inFile;

//Sets the default information for the player, default seed is set to 0 because wont be access unless random
string Options::playerList[4][3] = {{"sAlice", "S", "0"}, {"sBob", "S", "0"}, {"sCarole", "S", "0"}, {"sTed", "S", "0"}};

int Options::getMaxScore(){
    return maxScore;
}

int Options::getSeedValue(){
    return seedValue;
}

bool Options::seedEntered(){
    return seedSet;
}

bool Options::deckEntered(){
    return deckSet;
}

//Sets the options for the beginning of the game
void Options::setOptions(int argc, char* argv[])
{
    int tempMaxScore;
    int numberOfPlayersDeclared = 0;
    string letterOptions[] = {"-r", "-s", "-d", "-p", "S", "R", "H"}; //Possible letters for argument equality
    //Goes through the arguments
    for (int i = 1; i < argc; i++ ){
        //Sets the seed
        if (letterOptions[0].compare(argv[i]) == 0){ //Set the seed
            if (argc-1 == i){ //If there are no more arguments
                cerr << "Error, -r requires another argument.  Aborting.\n";
                exit (1);
            }
            if (deckSet){
                cerr << "Aborting; -r must occur before -d on command line if both flags are used.\n";
                exit (1);
            }
            seedValue = atoi(argv[++i]);
            //Set seed to the next parameter
            //This will also make sure that this parameter is skipped next iteration of the forloop
            seedSet = true;
        }
        else if (letterOptions[1].compare(argv[i]) == 0) { //setting maxScore
            if (argc-1 == i){ //If there are no more arguments
                cerr << "Error, -s requires another argument.  Aborting.\n";
                exit (1);
            }
            tempMaxScore = atoi(argv[++i]); //puts maxScore in a temp to check value
            //tempMaxScore will be set to the next input parameter (reason for ++i)
            if (tempMaxScore > 0){
                maxScore = tempMaxScore;
            }
            else{
                cerr << "Error, maxScore must be positive.\n";
                exit(3);
            }
        }
        else if (letterOptions[2].compare(argv[i]) == 0){ //Set the deck for the game
            if (argc - 1 == i){ //If there are no more arguments, stop the program
                cerr << "Error, -d requires another argument.  Aborting.\n";
                exit (1);
            }
            inFile.open(argv[++i]);
            deckSet = true;
            if (inFile.fail()){
                cerr << "Error, couldn't open card deck input file \"" << argv[i] <<"\"\n";
                exit(4);
            }
        }
        else if (letterOptions[3].compare(argv[i]) == 0){ //Set the players for the game
            for (int j = 0; j < 4; j++){
                if (argc-1 == i){
                    cerr << "Error, -p requires another argument.  Aborting.\n";
                    exit (1);
                }
                playerList[j][0] = argv[++i]; //Sets the name of the player
                if (argc-1 == i)
                {
                    cerr << "Error, -p requires another argument.  Aborting.\n";
                    exit (1);
                }
                //Seperated in different ifs because checking for a PRNG if there are no additional parameters may cause problems
                if (letterOptions[4].compare(argv[i+1])==0){ //Smart player
                    i++;
                    playerList[j][1] = "S"; //Sets the type of player
                    playerList[j][0] = "s" + playerList[j][0]; //appends the s to the name
                }
                else if (letterOptions[5].compare(argv[i+1])==0){ //Random player
                    i++;
                    playerList[j][1] = "R"; //Sets the type of player
                    playerList[j][0] = "r" + playerList[j][0]; //appends the r to the name
                    playerList[j][2] = argv[++i];
                }
                else if (letterOptions[6].compare(argv[i+1])==0){ //Human Player
                    i++;
                    playerList[j][1] = "H"; //Sets the type of player
                    playerList[j][0] = "h" + playerList[j][0]; //appends the h to the name
                }
                else{
                    cerr << "Illegal player kind: \"" << argv[i+1] <<"\"/n";
                    exit (5);
                }
                    numberOfPlayersDeclared++;
            }
            if (numberOfPlayersDeclared < 4){ //If there is not enough players, enough parameters were not entered, abort
                cerr << "Error, -p requires another argument.  Aborting.\n";
                exit (1);
            }
        }
    }
}
