#include "control.h"

void Up()
{
	for (int j = 0; j < 4; j++) 
	{
		int t = 0;
		for (int i = 0; i < 4; i++) 
		{
			if (boardGame[i][j] != 0) 
			{
				boardGame[t][j] = boardGame[i][j];
				t++;
			}
		}
		for (int i = t; i < 4; i++) boardGame[i][j] = 0;
	}

	for (int j = 0; j < 4; j++) 
	{
		int t = 0;
		for (int i = 0; i < 4; i++) 
		{
			if (boardGame != 0) 
			{
				if (boardGame[i][j] == boardGame[i + 1][j]) 
				{
					boardGame[t][j] = 2 * boardGame[i][j];
					gameScore += boardGame[t][j];
					t++;
					i++;
				}
				else 
				{
					boardGame[t][j] = boardGame[i][j];
					t++;
				}
			}
		}
		for (int i = t; i < 4; i++) boardGame[i][j] = 0;
	}
}


void Down()
{
	for (int j = 0; j < 4; j++) 
	{
		int t = 3;
		for (int i = 3; i >= 0; i--) 
		{
			if (boardGame[i][j] != 0) 
			{
				boardGame[t][j] = boardGame[i][j];
				t--;
			}
		}
		for (int i = t; i >= 0; i--) boardGame[i][j] = 0;
	}

	for (int j = 0; j < 4; j++) 
	{
		int t = 3;
		for (int i = 3; i >= 0; i--) 
		{
			if (boardGame != 0) {
				if (boardGame[i][j] == boardGame[i - 1][j]) 
				{
					boardGame[t][j] = 2 * boardGame[i][j];
					gameScore += boardGame[t][j];
					t--;
					i--;
				}
				else 
				{
					boardGame[t][j] = boardGame[i][j];
					t--;
				}
			}
		}
		for (int i = t; i >= 0; i--) boardGame[i][j] = 0;
	}
}

void Left()
{
	for (int i = 0; i < 4; i++) 
	{
		int t = 0;
		for (int j = 0; j < 4; j++) 
		{
			if (boardGame[i][j] != 0) 
			{
				boardGame[i][t] = boardGame[i][j];
				t++;
			}
		}
		for (int j = t; j < 4; j++) boardGame[i][j] = 0;
	}

	for (int i = 0; i < 4; i++) 
	{
		int t = 0;
		for (int j = 0; j < 4; j++) 
		{
			if (boardGame[i][j] != 0) 
			{
				if (boardGame[i][j] == boardGame[i][j + 1]) 
				{
					boardGame[i][t] = 2 * boardGame[i][j];
					gameScore += boardGame[i][t];
					j++;
					t++;
				}
				else 
				{
					boardGame[i][t] = boardGame[i][j];
					t++;
				}
			}
		}
		for (int j = t; j < 4; j++) boardGame[i][j] = 0;
	}
}


void Right()
{
	for (int i = 0; i < 4; i++) 
	{
		int t = 3;
		for (int j = 3; j >= 0; j--) 
		{
			if (boardGame[i][j] != 0) 
			{
				boardGame[i][t] = boardGame[i][j];
				t--;
			}
		}
		for (int j = t; j >= 0; j--) boardGame[i][j] = 0;
	}

	for (int i = 0; i < 4; i++) 
	{
		int t = 3;
		for (int j = 3; j >= 0; j--) 
		{
			if (boardGame[i][j] != 0) 
			{
				if (boardGame[i][j] == boardGame[i][j - 1]) 
				{
					boardGame[i][t] = 2 * boardGame[i][j];
					gameScore += boardGame[i][t];
					j--;
					t--;
				}
				else 
				{
					boardGame[i][t] = boardGame[i][j];
					t--;
				}
			}
		}
		for (int j = t; j >= 0; j--) boardGame[i][j] = 0;
	}
}