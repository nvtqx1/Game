#include "SDL_utils.h"

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Surface* g_screenStart = NULL;
SDL_Surface* g_rank = NULL;
SDL_Surface* g_guide = NULL;
SDL_Surface* g_gameOver = NULL;
SDL_Surface* g_object2 = NULL;
SDL_Surface* g_object4 = NULL;
SDL_Surface* g_object8 = NULL;
SDL_Surface* g_object16 = NULL;
SDL_Surface* g_object32 = NULL;
SDL_Surface* g_object64 = NULL;
SDL_Surface* g_object128 = NULL;
SDL_Surface* g_object256 = NULL;
SDL_Surface* g_object512 = NULL;
SDL_Surface* g_object1024 = NULL;
SDL_Surface* g_object2048 = NULL;
SDL_Surface* g_object4096 = NULL;
SDL_Event g_event;
SDL_Surface* score = NULL;
SDL_Surface* best = NULL;
TTF_Font* font = NULL;
SDL_Color textColor = { 170, 105, 35 };
SDL_Color textBest = { 170, 105, 35 };
std::string text;
Mix_Chunk* sound_01 = NULL;
Mix_Music* soundGameOver = NULL;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (g_screen == NULL)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	SDL_WM_SetCaption("2048", NULL);
	return true;
}

SDL_Surface* LoadImage(std::string file_path)
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);

		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}

void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}

void CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_background);
	SDL_FreeSurface(g_screenStart);
	SDL_FreeSurface(g_rank);
	SDL_FreeSurface(g_guide);
	SDL_FreeSurface(score);
	SDL_FreeSurface(best);
	TTF_CloseFont(font);
	TTF_Quit();
	Mix_FreeChunk(sound_01);
	Mix_FreeMusic(soundGameOver);
	Mix_CloseAudio();
	SDL_Quit();
}

int Loadfile()
{
	g_background = LoadImage("ImageGame/background.png");
	if (g_background == NULL)
	{
		return 0;
	}

	g_screenStart = LoadImage("ImageGame/screenStart.png");
	if (g_screenStart == NULL)
	{
		return 0;
	}

	g_rank = LoadImage("ImageGame/rank.png");
	if (g_rank == NULL)
	{
		return 0;
	}

	g_guide = LoadImage("ImageGame/guide.png");
	if (g_guide == NULL)
	{
		return 0;
	}

	g_gameOver = LoadImage("ImageGame/gameOver.png");
	if (g_gameOver == NULL)
	{
		return 0;
	}

	g_object2 = LoadImage("ImageGame/2.png");
	if (g_object2 == NULL)
	{
		return 0;
	}
	g_object4 = LoadImage("ImageGame/4.png");
	if (g_object4 == NULL)
	{
		return 0;
	}
	g_object8 = LoadImage("ImageGame/8.png");
	if (g_object8 == NULL)
	{
		return 0;
	}
	g_object16 = LoadImage("ImageGame/16.png");
	if (g_object16 == NULL)
	{
		return 0;
	}
	g_object32 = LoadImage("ImageGame/32.png");
	if (g_object32 == NULL)
	{
		return 0;
	}
	g_object64 = LoadImage("ImageGame/64.png");
	if (g_object64 == NULL)
	{
		return 0;
	}
	g_object128 = LoadImage("ImageGame/128.png");
	if (g_object128 == NULL)
	{
		return 0;
	}
	g_object256 = LoadImage("ImageGame/256.png");
	if (g_object256 == NULL)
	{
		return 0;
	}
	g_object512 = LoadImage("ImageGame/512.png");
	if (g_object512 == NULL)
	{
		return 0;
	}
	g_object1024 = LoadImage("ImageGame/1024.png");
	if (g_object1024 == NULL)
	{
		return 0;
	}
	g_object2048 = LoadImage("ImageGame/2048.png");
	if (g_object2048 == NULL)
	{
		return 0;
	}

	g_object4096 = LoadImage("ImageGame/4096.png");
	if (g_object4096 == NULL)
	{
		return 0;
	}

	font = TTF_OpenFont("FontText/fast99.ttf", 90);
	if (font == NULL)
	{
		return 0;
	}

	sound_01 = Mix_LoadWAV("Sound/medium.wav");
	if (sound_01 == NULL)
	{
		return 0;
	}

	soundGameOver = Mix_LoadMUS("Sound/SoundGameOver.wav");
	if (soundGameOver == NULL)
	{
		return 0;
	}
}

void printScore(int k)
{
	std::stringstream s;
	s << k;
	s >> text;
	score = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (score == NULL)
	{
		return;
	}
	ApplySurface(score, g_screen, 915, 110);
}


