#include <string>
#include <cassert>
#include <iostream>
#include "Card.h"
#include <stdlib.h>

using namespace std;

const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);


/** Constructors/Destructors **/

Card::Card() : rank(Ace), suit(Spades) {}

Card::Card(Rank r, Suit s): rank(r), suit(s){}

Card::Card(string sCard){
  int index =0;
  while(sCard.at(0) != Card::RankName.at(index)){index++;}
  rank = (Rank)index; //type convert from int to enum Rank

  index=0;
  while (sCard.at(1) !=Card::SuitName.at(index)){index++;}
  suit = (Suit)index; //type convert from int to enum Suit
}

Card::~Card(){/* no memory allocated for object */}

/** Accessor functions **/

Card::Rank Card::getRank() const{
  return rank;
}

Card::Suit Card::getSuit() const {
  return suit;
}

//calculate hearts value on the fly
int Card::getHeartsValue() const{
  if (*this == Card::QueenOfSpades){
      return 13;
  }
  else if(getSuit() == Card::Hearts){
        return 1;
  }
  else return 0;
}

/** Static Functions **/

/* string is legal iff:
   (1) 1st character is in Card::RankName, and
   (2) 2nd character is in Card::SuitName
   (3) must have onky 2 characters */
bool Card::stringIsALegalCard(string str){

  //if we find an occurence in Suit/Rank strings
  if (Card::RankName.find_first_of(str.at(0)) !=string::npos &&
      Card::SuitName.find_first_of(str.at(1)) !=string::npos &&
    str.size() == 2){
    return true;
  }
  else{
    return false;
  }
}

/** Comparison **/

bool operator==(const Card &c1, const Card &c2){
  //field wise comparison
  return (c1.getRank() == c2.getRank() && c1.getSuit() == c2.getSuit());
}

bool operator< (const Card &c1, const Card &c2){
  //if ranks for are equal we compare suits
  if (c1.getRank() == c2.getRank() && c1.getSuit() < c2.getSuit()){
    return true;
  }
  //otherwise we just compare ranks
  else
    return (c1.getRank() < c2.getRank());
}

/** Input/Output **/

ostream& operator<< (ostream &out, const Card &c){
  //enum types Rank and Suit are treated as integral types here
  out << Card::RankName.at(c.getRank()) << Card::SuitName.at(c.getSuit());
  return out;
}

istream& operator>> (istream& in, Card &c){
  string s;
  in >>s;
  int index =0;
  while(s.at(0) != Card::RankName.at(index)){index++;}
  c.rank = (Card::Rank)index; //type convert from int to enum Rank

  index=0;
  while (s.at(1) !=Card::SuitName.at(index)){index++;}
  c.suit = (Card::Suit)index; //type convert from int to enum Suit

  return in;
}
