CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++0x
OBJECTS = main.o Card.o Command.o Controller.o Deck.o Model.o Player.o HumanPlayer.o ComputerPlayer.o Table.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights.exe

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}