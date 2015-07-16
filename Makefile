CXX = g++
CXXFLAGS = -Wall -O -std=c++0x -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJECTS = main.o DeckGUI.o View.o Card.o Command.o Controller.o Deck.o Model.o Player.o HumanPlayer.o ComputerPlayer.o Table.o Observer.o Subject.o StartGameDialogBox.o DialogBox.o

# OBJECTS = models/model.o \
# 			views/view.o \
# 			main.o \

# DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} ${LDFLAGS} -o ${EXEC}

clean:
	rm -rf ${OBJECTS} ${EXEC}

# Card.o: Card.h Card.cpp
# Deck.o: Deck.h Deck.cpp
# DeckGUI.o: DeckGUI.h DeckGUI.cpp
# Table.o: Table.h Table.cpp
# Command.o: Command.h Command.cpp
# Player.o: Player.h Player.cpp
# HumanPlayer.o: HumanPlayer.h HumanPlayer.cpp
# ComputerPlayer.o: ComputerPlayer.h ComputerPlayer.cpp
# Model.o: Model.h Model.cpp
# Subject.o: Subject.h Subject.cpp
# Observer.o: Observer.h Observer.cpp
# Controller.o: Controller.h Controller.cpp
# View.o: DeckGUI.h Observer.h Subject.h Model.h View.h View.cpp
# main.o: main.cpp

