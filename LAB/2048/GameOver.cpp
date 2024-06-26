#include "GameOver.h"

void gameOver()
{
    bestScore(gameScore);
    if (Mix_PlayMusic(soundGameOver, -1) == -1)
    {
        return;
    }
    SDL_RenderCopy(g_renderer, g_gameOver, NULL, NULL);
    bool quit = false;
    int x = 0, y = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&g_event))
        {
            if (g_event.type == SDL_QUIT)
            {
                exit(1);
                break;
            }
            if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                Mix_HaltMusic();
                if (g_event.button.button == SDL_BUTTON_LEFT)
                {
                    x = g_event.button.x;
                    y = g_event.button.y;

                    if ((x > 213) && (x < 468) && (y > 583) && (y < 667))
                    {
                        screenStart();
                    }
                    else if ((x > 495) && (x < 786) && (y > 502) && (y < 586))
                    {
                        startGame();
                    }
                    else if ((x > 813) && (x < 1068) && (y > 583) && (y < 667))
                    {
                        exit(1);
                    }
                }
            }
            if (g_event.type == SDL_KEYDOWN)
			{
				//SDL_RenderCopy(g_renderer, g_guide, NULL, NULL);
				switch (g_event.key.keysym.sym)
				{
				case SDLK_ESCAPE:{
                     Mix_HaltMusic();
					 screenStart();
                    }
				}
            }
        }
        SDL_RenderPresent(g_renderer);
    }
}

void bestScore(int k)
{
	int n;
	std::ifstream infile;
	infile.open("BestScore.TXT");
	infile >> n;
	infile.close();
	std::ofstream outfile;
	outfile.open("BestScore.TXT");
	if (k > n)
	{
		outfile << k;
	}
	else outfile << n;
	outfile.close();
}
