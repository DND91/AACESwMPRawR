CC := mingw32-g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -g
# SFML_INCLUDE = -I/home/dnd91/.local/include
# SFML_LIBS = -L/home/dnd91/.local/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio

#BOOST_INCLUDE = -I/var/db/pkg/dev-libs/boost-1.52.0-r6/
BOOST_INCLUDE = -I/c/libs/boost_1_54_0

GAME_SOURCES = game.cpp RawR.cpp StandardRawR.cpp
GAME_EXE_NAME = game
GAME_OBJECTS = $(GAME_SOURCES:.cpp=.o)
GAME_PATH = ./game/
GAME_BUILD_PATH = ./build/
GAME_OBJ_PATH = ./obj/

GAME_SRC = $(addprefix $(GAME_PATH),$(GAME_SOURCES))
GAME_OBJ =$(addprefix $(GAME_OBJ_PATH),$(GAME_OBJECTS))
GAME_EXE =$(addprefix $(GAME_BUILD_PATH),$(GAME_EXE_NAME))

game : $(GAME_EXE)

$(GAME_EXE) : $(GAME_OBJ)
	$(CC) $(CFLAGS)  -o $@ $(GAME_OBJ)
	#$(CC) $(CFLAGS)  -o $@ $(GAME_OBJ) $(SFML_LIBS) -lstdc++
	
$(GAME_OBJ_PATH)%.o: $(GAME_PATH)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(BOOST_INCLUDE)
	#$(CC) $(CFLAGS) -c -o $@ $< $(SFML_INCLUDE) $(BOOST_INCLUDE)
