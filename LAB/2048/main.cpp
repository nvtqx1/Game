#include "screenStart.h"
#include "Game.h"

#undef main

int main(int arc, char* argv[]) {
	if (Init() == false)
	{
		return 0;
	}
	if(Loadfile() == true){
	screenStart();
	CleanUp();
	}
	return 0;
}
