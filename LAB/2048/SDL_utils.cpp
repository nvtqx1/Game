#include "SDL_utils.h"

SDL_Renderer* g_renderer = NULL;
SDL_Window* g_window = NULL;
SDL_Texture* g_background = NULL;
SDL_Texture* g_screenStart = NULL;
SDL_Texture* g_rank = NULL;
SDL_Texture* g_guide = NULL;
SDL_Texture* g_gameOver = NULL;
SDL_Texture* g_object2 = NULL;
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
SDL_Event g_event;
SDL_Texture* score = NULL;
SDL_Texture* best = NULL;

TTF_Font* font = NULL;
SDL_Color textColor = { 170, 105, 35 };
SDL_Color textBest = { 170, 105, 35 };
std::string text;
Mix_Chunk* sound_01 = NULL;
Mix_Music* soundGameOver = NULL;

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
SDL_Texture* LoadImage(std::string file_path)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(file_path.c_str());
    if (loadedSurface != NULL)
    {
        newTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
void ApplySurface(SDL_Texture* src, SDL_Renderer* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_QueryTexture(src, NULL, NULL, &offset.w, &offset.h);
    SDL_RenderCopy(des, src, NULL, &offset);
}


void CleanUp()
{
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
    TTF_Quit();
	Mix_Quit();
	IMG_Quit();

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

    return 1; // Return 1 if everything loaded successfully
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




