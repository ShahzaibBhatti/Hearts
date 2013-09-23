Hearts
======

A modified version of Hearts played on terminal

Made as the final project for cs246 (Object Oriented Software Development in C++)

Developers: 
- Shahzaib Bhatti
- Daniyal Khan

Upto 4 players!

Running Instructions:
======================
1. If the Hearts file is not in the repository, run the makefile to compile it by running: "make".
2. Otherwise allow the Hearts file to be executed by running "chmod a+x Hearts"
3. use the command ./Hearts to run the game


Command Line Options
=======================
If you run the file without any options, each move in the game will be conducted by an AI.
You can specify a players as such:
  ./hearts -p [name_1] [player_type_1] [name_2] [player_type_2] [name_3] [player_type_3] [name_4] [player_type_4]
where: 
- [player_type] 'H', 'S', 'R' which represent human, smart and random players respectively 
- [name_x] is the name of the player. 
  - Players will have the character representing their type appended to the front of their name
- you do not need to enter all 4 players but if you do, you must specify their type

Gameplay:  
===============
- During you turn, unlike traditional Hearts, you can play any card in your hand 
- You play your selected card by typing the card in and hitting enter
- The game follows the traditional rules of hearts, with this exception
- As a house rule to this game, the jack of diamonds and queen of spades have no effect
