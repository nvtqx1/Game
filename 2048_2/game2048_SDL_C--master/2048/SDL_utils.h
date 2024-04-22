#pragma once
#ifndef SDL_UTILS_H_
#define SDL_UTILS_H_

#include <Windows.h>
#include <sstream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "commonFunction.h"

extern SDL_Surface* g_screen;
extern SDL_Surface* g_background;
extern SDL_Surface* g_screenStart;
extern SDL_Surface* g_rank;
extern SDL_Surface* g_guide;
extern SDL_Surface* g_gameOver;
extern SDL_Surface* g_object2;
extern SDL_Surface* g_object4;
extern SDL_Surface* g_object8;
extern SDL_Surface* g_object16;
extern SDL_Surface* g_object32;
extern SDL_Surface* g_object64;
extern SDL_Surface* g_object128;
extern SDL_Surface* g_object256;
extern SDL_Surface* g_object512;
extern SDL_Surface* g_object1024;
extern SDL_Surface* g_object2048;
extern SDL_Surface* g_object4096;
extern SDL_Event g_event;
extern SDL_Surface* score;
extern SDL_Surface* best;
extern TTF_Font* font;
extern SDL_Color textColor;
extern SDL_Color textBest;
extern std::string text;
extern Mix_Chunk* sound_01;
extern Mix_Music* soundGameOver;

bool Init();
SDL_Surface* LoadImage(std::string file_path);
void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
void CleanUp();
int Loadfile();
void printScore(int k);
#endif