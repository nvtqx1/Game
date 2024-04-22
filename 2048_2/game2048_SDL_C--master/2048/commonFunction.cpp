#include "commonFunction.h"


int boardGame[4][4] = { 0 };
int boardCheck[4][4] = { 0 };
int gameScore = 0;

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
int SCREEN_BPP = 32;


void init_gameBoard()
{
	gameScore = 0;
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			boardGame[i][j] = 0;
		}
	}
	srand(time(NULL));
	int newTile[4];

	newTile[0] = rand() % 4;
	newTile[1] = rand() % 4;
	do {
		newTile[2] = rand() % 4;
		newTile[3] = rand() % 4;
	} while (newTile[0] == newTile[2] || newTile[1] == newTile[3]);

	boardGame[newTile[0]][newTile[1]] = 2;
	boardGame[newTile[2]][newTile[3]] = 2;
}


bool checkGame()
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			if (boardGame[i][j] == 0) 
			{
				return true;
			}
		}
	}
	return false;
}


bool checkGameOver()
{
	if (checkGame() == false) 
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				if (boardGame[i][j] == boardGame[i][j + 1] ||
					boardGame[i][j] == boardGame[i + 1][j]) return false;
			}
		}
	}
	else if (checkGame() == true) return false;
	return true;
}


void addTile()
{
	if (checkGame() == false) return;

	int i, j;
	srand(time(NULL));

	do 
	{
		i = rand() % 4;
		j = rand() % 4;
	} 
	while (boardGame[i][j] != 0);
	int s = rand() % 100;
	if (s > 80) boardGame[i][j] = 4;
	else (boardGame[i][j] = 2);
}

void copyCheck()
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			boardCheck[i][j] = boardGame[i][j];
		}
	}
}

bool checkMove()
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			if (boardCheck[i][j] != boardGame[i][j]) return true;
		}
	}
	return false;
}

void location(int& u, int& v)
{
	if (u == 0 && v == 0) 
	{
		u = 210.5;
		v = 150.5;
	}
	else if (u == 0 && v == 1) 
	{
		u = 317.5;
		v = 150.5;
	}
	else if (u == 0 && v == 2) 
	{
		u = 424.17;
		v = 150.5;
	}
	else if (u == 0 && v == 3) 
	{
		u = 531;
		v = 150.5;
	}
	else if (u == 1 && v == 0) 
	{
		u = 210.5;
		v = 257;
	}
	else if (u == 1 && v == 1) 
	{
		u = 317.5;
		v = 257;
	}
	else if (u == 1 && v == 2) 
	{
		u = 424.17;
		v = 257;
	}
	else if (u == 1 && v == 3) 
	{
		u = 531;
		v = 257;
	}
	else if (u == 2 && v == 0) 
	{
		u = 210.5;
		v = 363.6;
	}
	else if (u == 2 && v == 1) 
	{
		u = 317.5;
		v = 363.6;
	}
	else if (u == 2 && v == 2) 
	{
		u = 424.17;
		v = 363.6;
	}
	else if (u == 2 && v == 3) 
	{
		u = 531;
		v = 363.6;
	}
	else if (u == 3 && v == 0) 
	{
		u = 210.5;
		v = 470.1;
	}
	else if (u == 3 && v == 1) 
	{
		u = 317.5;
		v = 470.1;
	}
	else if (u == 3 && v == 2) 
	{
		u = 424.17;
		v = 470.1;
	}
	else if (u == 3 && v == 3) 
	{
		u = 531;
		v = 470.1;
	}
}