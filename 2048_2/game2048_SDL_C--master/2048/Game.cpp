#include "Game.h"

void startGame()
{
	bool quit = false;
	int x = 0, y = 0;
	ApplySurface(g_background, g_screen, 0, 0);
	init_gameBoard();
	while (!quit)
	{
		if (checkGameOver() == true)
		{
			gameOver();
		}
		for (int i = 0; i < 4; i++) 
		{
			if (checkGameOver() == true)
			{
				break;
			}
			copyCheck();
			for (int j = 0; j < 4; j++)
			{
				int u = i;
				int v = j;
				location(u, v);
				if (boardGame[i][j] == 2) 
				{
					ApplySurface(g_object2, g_screen, u, v);
				}
				if (boardGame[i][j] == 4) 
				{
					ApplySurface(g_object4, g_screen, u, v);
				}
				if (boardGame[i][j] == 8) 
				{
					ApplySurface(g_object8, g_screen, u, v);
				}
				if (boardGame[i][j] == 16) 
				{
					ApplySurface(g_object16, g_screen, u, v);
				}
				if (boardGame[i][j] == 32) 
				{
					ApplySurface(g_object32, g_screen, u, v);
				}
				if (boardGame[i][j] == 64) 
				{
					ApplySurface(g_object64, g_screen, u, v);
				}
				if (boardGame[i][j] == 128) 
				{
					ApplySurface(g_object128, g_screen, u, v);
				}
				if (boardGame[i][j] == 256) 
				{
					ApplySurface(g_object256, g_screen, u, v);
				}
				if (boardGame[i][j] == 512) 
				{
					ApplySurface(g_object512, g_screen, u, v);
				}
				if (boardGame[i][j] == 1024) 
				{
					ApplySurface(g_object1024, g_screen, u, v);
				}
				if (boardGame[i][j] == 2048) 
				{
					ApplySurface(g_object2048, g_screen, u, v);
				}
				if (boardGame[i][j] == 4096) 
				{
					ApplySurface(g_object4096, g_screen, u, v);
				}
			}
		}
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				exit(1);
			}
			if (g_event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (g_event.button.button == SDL_BUTTON_LEFT)
				{
					x = g_event.button.x;
					y = g_event.button.y;

					if ((x > 25) && (x < 137) && (y > 24) && (y < 98))
					{
						screenStart();
					}
				}
			}
			if (g_event.type == SDL_KEYDOWN)
			{
				ApplySurface(g_background, g_screen, 0, 0);

				switch (g_event.key.keysym.sym)
				{
				case SDLK_UP: Up();  break;
				case SDLK_DOWN: Down(); break;
				case SDLK_LEFT: Left(); break;
				case SDLK_RIGHT: Right(); break;
				}
				printScore(gameScore);
				if (checkMove() == true)
				{
					if (Mix_PlayChannel(-1, sound_01, 0) == -1)
					{
						return;
					}
					addTile();
				}
			}
		}
		if (SDL_Flip(g_screen) == -1)
		{
			return;
		}

	}
}