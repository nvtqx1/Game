#include "Game.h"

void startGame()
{
    bool quit = false;
    int x = 0, y = 0;
    SDL_RenderCopy(g_renderer, g_background, NULL, NULL);
    init_gameBoard();
    while (!quit)
    {
        if (Mix_PlayingMusic() == 0){
            Mix_PlayMusic(sound_02, -1);
        }
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
					ApplySurface(g_object2, g_renderer, u, v);
				}
				if (boardGame[i][j] == 4)
				{
					ApplySurface(g_object4, g_renderer, u, v);
				}
				if (boardGame[i][j] == 8)
				{
					ApplySurface(g_object8, g_renderer, u, v);
				}
				if (boardGame[i][j] == 16)
				{
					ApplySurface(g_object16, g_renderer, u, v);
				}
				if (boardGame[i][j] == 32)
				{
					ApplySurface(g_object32, g_renderer, u, v);
				}
				if (boardGame[i][j] == 64)
				{
					ApplySurface(g_object64, g_renderer, u, v);
				}
				if (boardGame[i][j] == 128)
				{
					ApplySurface(g_object128, g_renderer, u, v);
				}
				if (boardGame[i][j] == 256)
				{
					ApplySurface(g_object256, g_renderer, u, v);
				}
				if (boardGame[i][j] == 512)
				{
					ApplySurface(g_object512, g_renderer, u, v);
				}
				if (boardGame[i][j] == 1024)
				{
					ApplySurface(g_object1024, g_renderer, u, v);
				}
				if (boardGame[i][j] == 2048)
				{
					ApplySurface(g_object2048, g_renderer, u, v);
				}
				if (boardGame[i][j] == 4096)
				{
					ApplySurface(g_object4096, g_renderer, u, v);
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
					    Mix_HaltMusic();
						screenStart();
					}
				}
			}
			if (g_event.type == SDL_KEYDOWN)
			{
				SDL_RenderCopy(g_renderer, g_background, NULL, NULL);

				switch (g_event.key.keysym.sym)
				{
				case SDLK_UP: Up();  break;
				case SDLK_DOWN: Down(); break;
				case SDLK_LEFT: Left(); break;
				case SDLK_RIGHT: Right(); break;
                case SDLK_ESCAPE: screenStart(); break;
				case SDLK_m:
                    if (Mix_PlayingMusic() == 0)
                    {
                        Mix_PlayMusic(sound_02, -1);
                    }
                    else
                    {
                        if (Mix_PausedMusic() == 1)
                        {
                            Mix_ResumeMusic();
                        }
                        else
                        {
                            Mix_PauseMusic();
                        }
                    }
                }
				printScore(gameScore);
				if (checkMove() == true)
				{
					if (Mix_PlayChannel(1, sound_01, 0) == -1)
					{
						return;
					}
					addTile();
				}
				if (checkMove() == true && Mix_PausedMusic() == true) Mix_HaltChannel(1);

			}
		}

        SDL_RenderPresent(g_renderer);
    }
}

