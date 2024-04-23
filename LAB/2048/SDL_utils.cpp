#include "SDL_utils.h"

SDL_Renderer* g_renderer = NULL;
SDL_Window* g_window = NULL;
SDL_Texture* g_background = NULL;
SDL_Texture* g_screenStart = NULL;
SDL_Texture* g_rank = NULL;
SDL_Texture* g_guide = NULL;
SDL_Texture* g_gameOver = NULL;
/*SDL_Texture* g_object2 = NULL;
SDL_Texture* g_object4 = NULL;
SDL_Texture* g_object8 = NULL;
SDL_Texture* g_object16 = NULL;
SDL_Texture* g_object32 = NULL;
SDL_Texture* g_object64 = NULL;
SDL_Texture* g_object128 = NULL;
SDL_Texture* g_object256 = NULL;
SDL_Texture* g_object512 = NULL;
SDL_Texture* g_object1024 = NULL;
SDL_Texture* g_object2048 = NULL;
SDL_Texture* g_object4096 = NULL;
*/
SDL_Event g_event;
/*SDL_Texture* score = NULL;
SDL_Texture* best = NULL;
*/
TTF_Font* font = NULL;
SDL_Color textColor = { 170, 105, 35 };
SDL_Color textBest = { 170, 105, 35 };
std::string text;
Mix_Chunk* sound_01 = NULL;
Mix_Music* soundGameOver = NULL;

class LTexture
{
public:
	LTexture();
	~LTexture();
	bool LoadImage(std::string path);
	void free();
	void render(int x, int y);
	int getWidth();
	int getHeight();
	#if defined(SDL_TTF_MAJOR_VERSION)

		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	#endif
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};
LTexture g_object2, g_object4, g_object8, g_object16, g_object32, g_object64, g_object128,g_object256, g_object512, g_object1024, g_object2048, g_object4096;
LTexture g_Background;
LTexture g_score, g_best;

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

//Destruction
LTexture::~LTexture()
{
	free();
}

//Load image from file
bool LTexture::LoadImage(std::string path)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}
void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
//Upload image to window at given coordinates
void LTexture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(g_renderer, mTexture, NULL, &renderQuad);
}

//Take the size
int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

//Load an image from a text
#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif
bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false;
    }

    g_window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL)
    {
        return false;
    }

    if (TTF_Init() != 0)
    {
        return false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    {
        return false;
    }

    return true;
}
void CleanUp()
{
	g_object2.free();
	g_object4.free();
	g_object8.free();
	g_object16.free();
	g_object32.free();
	g_object64.free();
	g_object128.free();
	g_object256.free();
	g_object512.free();
	g_object1024.free();
	g_object2048.free();
	g_object4096.free();
	g_Background.free();
	g_score.free();
	g_best.free();
	SDL_DestroyTexture(g_rank);
    SDL_DestroyTexture(g_guide);
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	Mix_FreeMusic(soundGameOver);
	Mix_FreeChunk(sound_01);
	TTF_CloseFont(font);
	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
    /*
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyTexture(g_background);
    SDL_DestroyTexture(g_screenStart);
    SDL_DestroyTexture(g_rank);
    SDL_DestroyTexture(g_guide);
    SDL_DestroyTexture(score);
    SDL_DestroyTexture(best);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_FreeChunk(sound_01);
    Mix_FreeMusic(soundGameOver);
    Mix_CloseAudio();
    SDL_Quit();
    */
}



bool Loadfile()
{
    bool success = true;
    g_background = LoadImage("ImageGame/background.png");
    g_screenStart = LoadImage("ImageGame/screenStart.png");
    g_rank = LoadImage("ImageGame/rank.png");
    g_guide = LoadImage("ImageGame/guide.png");
    g_gameOver = LoadImage("ImageGame/gameOver.png");
    g_object2 = LoadImage("ImageGame/2.png");
    g_object4 = LoadImage("ImageGame/4.png");
    g_object8 = LoadImage("ImageGame/8.png");
    g_object16 = LoadImage("ImageGame/16.png");
    g_object32 = LoadImage("ImageGame/32.png");
    g_object64 = LoadImage("ImageGame/64.png");
    g_object128 = LoadImage("ImageGame/128.png");
    g_object256 = LoadImage("ImageGame/256.png");
    g_object512 = LoadImage("ImageGame/512.png");
    g_object1024 = LoadImage("ImageGame/1024.png");
    g_object2048 = LoadImage("ImageGame/2048.png");
    g_object4096 = LoadImage("ImageGame/4096.png");
    font = TTF_OpenFont("FontText/fast99.ttf", 90);
    sound_01 = Mix_LoadWAV("Sound/medium.wav");
    soundGameOver = Mix_LoadMUS("Sound/SoundGameOver.wav");
    return success;
    /*
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

    return 1; // Return 1 if everything loaded successfully
    */
}


void printScore(int k)
{
    std::stringstream s;
    s << k;
    std::string text = s.str();

    SDL_Color textColor = { 255, 255, 255, 255 }; // Assuming the color of the text is white
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
    SDL_FreeSurface(textSurface); // Don't forget to free the surface after creating the texture

    SDL_Rect renderQuad = { 915, 110, textSurface->w, textSurface->h }; // Assuming you want to render at (915, 110) and the width and height of the texture is the same as the text surface
    SDL_RenderCopy(g_renderer, textTexture, NULL, &renderQuad);

    SDL_DestroyTexture(textTexture); // Don't forget to free the texture
}




