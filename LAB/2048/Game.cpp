#include "Game.h"

void startGame()
{
    bool quit = false;
    int x = 0, y = 0;
    SDL_RenderCopy(g_renderer, g_background, NULL, NULL);
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
                SDL_Texture* currentTexture = NULL;
                switch(boardGame[i][j])
                {
                    case 2: currentTexture = g_object2; break;
                    case 4: currentTexture = g_object4; break;
                    case 8: currentTexture = g_object8; break;
                    case 16: currentTexture = g_object16; break;
                    case 32: currentTexture = g_object32; break;
                    case 64: currentTexture = g_object64; break;
                    case 128: currentTexture = g_object128; break;
                    case 256: currentTexture = g_object256; break;
                    case 512: currentTexture = g_object512; break;
                    case 1024: currentTexture = g_object1024; break;
                    case 2048: currentTexture = g_object2048; break;
                    case 4096: currentTexture = g_object4096; break;
                }
                if(currentTexture != NULL)
                {
                    SDL_Rect renderQuad = { u, v, /* width and height of the texture */ };
                    SDL_RenderCopy(g_renderer, currentTexture, NULL, &renderQuad);
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
				SDL_RenderCopy(g_renderer, g_background, NULL, NULL);

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
        SDL_RenderPresent(g_renderer);
    }
}

