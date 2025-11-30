#include "screenStart.h"

void screenStart()
{
    bool quit = false;
    int x = 0, y = 0;
    SDL_RenderCopy(g_renderer, g_screenStart, NULL, NULL);
    while (!quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                exit(1);
            }
            else if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (g_event.button.button == SDL_BUTTON_LEFT)
                {
                    x = g_event.button.x;
                    y = g_event.button.y;

                    if ((x > 515) && (x < 770) && (y > 302) && (y < 386))
                    {
                        startGame();
                    }
                    else if ((x > 515) && (x < 770) && (y > 405) && (y < 489))
                    {
                        rank();
                    }
                    else if ((x > 515) && (x < 770) && (y > 508) && (y < 592))
                    {
                        guide();
                    }
                    else if ((x > 515) && (x < 770) && (y > 611) && (y < 695))
                    {
                        exit(1);
                    }
                }
            }
        }
        SDL_RenderPresent(g_renderer);
    }
}



void rank()
{
    bool quit = false;
    int x = 0, y = 0;
    SDL_RenderCopy(g_renderer, g_rank, NULL, NULL);
    printBest();
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
                if (g_event.button.button == SDL_BUTTON_LEFT)
                {
                    x = g_event.button.x;
                    y = g_event.button.y;

                    if ((x > 28) && (x < 163) && (y > 35) && (y < 125))
                    {
                        screenStart();
                    }
                }
            }
            if (g_event.type == SDL_KEYDOWN)
			{
				SDL_RenderCopy(g_renderer, g_guide, NULL, NULL);

				switch (g_event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					 screenStart();
				}
            }
        }
        SDL_RenderPresent(g_renderer);
    }
}



void guide()
{
    bool quit = false;
    int x = 0, y = 0;
    SDL_RenderCopy(g_renderer, g_guide, NULL, NULL);
    while (!quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                exit(1);
            }
            else if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (g_event.button.button == SDL_BUTTON_LEFT)
                {
                    x = g_event.button.x;
                    y = g_event.button.y;

                    if ((x > 28) && (x < 163) && (y > 35) && (y < 125))
                    {
                        screenStart();
                    }
                }

            }
            if (g_event.type == SDL_KEYDOWN)
			{
				SDL_RenderCopy(g_renderer, g_guide, NULL, NULL);

				switch (g_event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					 screenStart();
				}
            }
        }
        SDL_RenderPresent(g_renderer);
    }
}


void printBest()
{
    int n;
    std::ifstream infile;
    infile.open("BestScore.TXT");
    infile >> n;
    infile.close();
    std::string s;
    std::stringstream ss;
    ss << n;
    ss >> s;

    SDL_Color textColor = { 255, 255, 255, 255 }; // Assuming the color of the text is white
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, s.c_str(), textColor);
    if (textSurface == NULL)
    {
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
    SDL_FreeSurface(textSurface); // Don't forget to free the surface after creating the texture

    SDL_Rect renderQuad = { 780, 140, textSurface->w, textSurface->h }; // Assuming you want to render at (780, 140) and the width and height of the texture is the same as the text surface
    SDL_RenderCopy(g_renderer, textTexture, NULL, &renderQuad);

    SDL_DestroyTexture(textTexture); // Don't forget to free the texture
}

