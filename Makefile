CXX = g++
CXXFLAGS = -Wall -O -MMD -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
CPP_FILES := $(wildcard **/*.cpp) 
OBJ_FILES := main.o src/Command.o
DEPENDS = $(OBJ_FILES:.o=.d)
INC = /src /src/game /src/mvc /src/player
INC_PARAMS = $(foreach d, $(INC), -I$d)
EXEC = straights.exe

$(EXEC) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INC_PARAMS) $(OBJ_FILES) -o $(EXEC)

clean :
	rm -rf $(DEPENDS) $(OBJ_FILES) $(EXEC)

-include $(DEPENDS)

# Card.o: game/Card.h game/Card.cpp
# Deck.o: game/Deck.h game/Deck.cpp
# Table.o: game/Table.h game/Table.cpp
# Command.o: Command.h Command.cpp
# Player.o: player/Player.h player/Player.cpp
# HumanPlayer.o: player/HumanPlayer.h player/HumanPlayer.cpp
# ComputerPlayer.o: player/ComputerPlayer.h player/ComputerPlayer.cpp
# Model.o: mvc/Model.h mvc/Model.cpp
# Subject.o: 
# Controller.o:
# View.o:
# main.o:

