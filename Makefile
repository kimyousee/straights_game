CXX = g++
CXXFLAGS = -Wall -O -std=c++0x -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJECTS = main.o DeckGUI.o View.o Card.o Command.o Controller.o Deck.o Model.o Player.o HumanPlayer.o ComputerPlayer.o Table.o Observer.o Subject.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} ${LDFLAGS} -o ${EXEC}

clean:
	rm -rf ${OBJECTS} ${EXEC}

# -include ${DEPENDS}

# CXX = g++
# CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags`
# LDFLAGS=`pkg-config gtkmm-2.4 --libs`

# SRC_DIR = /src/
# OBJ_DIR = /obj/

# CPP_FILES := $(wildcard **/*.cpp)
# OBJ_FILES = $(CPP_FILES:.cpp=.o)
# C_SRC = $(CPP_FILES)
# C_OBJ = $(addprefix $(OBJ_DIR),$(OBJ_FILES))

# DEPENDS = $(OBJ_FILES:.o=.d)
# INC = /src /src/game /src/mvc /src/player
# INC_PARAMS = $(foreach d, $(INC), -I$d)
# EXEC = straights.exe

# all: $(C_SRC) $(EXEC)

# $(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
# 	$(CXX) $(CXXFLAGS) $< -o $@

# $(EXEC) : $(C_OBJ)
# 	$(CXX) $(C_OBJ) $(LDFLAGS) $(INC_PARAMS) -o $@

# clean :
# 	rm -rf $(DEPENDS) $(OBJ_FILES) $(EXEC)

# -include $(DEPENDS)

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
# View.o: View.h View.cpp
# main.o: main.cpp

