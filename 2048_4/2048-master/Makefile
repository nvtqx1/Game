CFLAGS=-c -std=c++11 -g -Wno-narrowing -I./src/SDL/ `sdl2-config --cflags`
LFLAGS=-o 2048
LIBS=`sdl2-config --libs` -lSDL2_ttf

all:
	g++ $(CFLAGS) src/Animation/Merge.cpp src/Animation/Move.cpp src/Animation/Spawn.cpp src/Definitions/Definitions.cpp src/Definitions/NumberedRect.cpp src/Definitions/Rect.cpp src/Game/Game.cpp src/Main.cpp src/Program/Program.cpp src/Stats/Stats.cpp src/Window/GameWindow.cpp src/Window/StatsWindow.cpp src/Window/Window.cpp
	g++ $(LFLAGS) Merge.o Move.o Spawn.o Definitions.o NumberedRect.o Rect.o Game.o Main.o Program.o Stats.o GameWindow.o StatsWindow.o Window.o $(LIBS)

clean:
	rm -f *.o

cleanall:
	rm -f *.o 2048
