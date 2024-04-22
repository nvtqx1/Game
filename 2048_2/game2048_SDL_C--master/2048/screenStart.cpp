#include "screenStart.h"

void screenStart()
{
	bool quit = false;
	int x = 0, y = 0;
	ApplySurface(g_screenStart, g_screen, 0, 0);
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
		if (SDL_Flip(g_screen) == -1)
		{
			return;
		}
	}
}

void rank()
{
	bool quit = false;
	int x = 0, y = 0;
	ApplySurface(g_rank, g_screen, 0, 0);
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
		}
		if (SDL_Flip(g_screen) == -1)
		{
			return;
		}
	}
}

void guide()
{
	bool quit = false;
	int x = 0, y = 0;
	ApplySurface(g_guide, g_screen, 0, 0);
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
		}
		if (SDL_Flip(g_screen) == -1)
		{
			return;
		}
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
	best = TTF_RenderText_Solid(font, s.c_str(), textBest);
	if (best == NULL)
	{
		return;
	}
	ApplySurface(best, g_screen, 780, 140);
}