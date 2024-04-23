#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <time.h>

extern int boardGame[4][4];
extern int boardCheck[4][4];
extern int gameScore;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;

void init_gameBoard();
bool checkGame();
bool checkGameOver();
void addTile();
void copyCheck();
bool checkMove();
void location(int& u, int& v);


#endif