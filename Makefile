CXX = g++                                     # compiler
CXXFLAGS = -g -Wall -MMD                      # compiler flags
MAKEFILE NAME = ${firstword ${MAKEFILE LIST}} # makefile name

OBJECTS1 = p3driver.o Deck.o CardPile.o Card.o Player.o HumanPlayer.o SmartPlayer.o RandomPlayer.o Options.o Trick.o       # object files forming executable
EXEC1 = Hearts                        # executable name

OBJECTS = ${OBJECTS1}
EXECS = ${EXEC1}
DEPENDS = ${OBJECTS:.o=.d}                    # substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC1} : ${OBJECTS1}                        # link step
	${CXX} ${CXXFLAGS} $^ -o $@           # make sure there is a tab at the start of this line

${OBJECTS} : ${MAKEFILE NAME}                 # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}                           # include *.d files containing program dependences

clean :                                       # remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}