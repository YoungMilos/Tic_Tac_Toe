#pragma once
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "AssetManager.h"
#include "AI.h"
#include "Settings.h"
#include "Window.h"

extern Window* gWindow;
extern bool gSoundOn;

class Board
{
private:
	SDL_Texture* cell_emtpy;
	SDL_Texture* win_horizontal;
	SDL_Texture* win_down;
	SDL_Texture* win_up;
	SDL_Texture* win_vertical;
	int gameBoard[BOARD_WIDTH][BOARD_HEIGHT];
	GomokuAI* gomokuAI;
	SDL_Rect cell_rect;
	Mix_Chunk* moveSound;
public:
	bool isGamePVE;
	bool moved = false;
	SDL_Texture* cell_x;
	SDL_Texture* cell_o;
	void getGameBoard(int** board)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			for (int j = 0; j < BOARD_HEIGHT; j++)
			{
				board[i][j] = gameBoard[i][j];
			}
		}
	}
	Board();
	~Board();
	void renderBoard();
	void move(int x, int y);
	void handleBoardEvent();
	void reset();
	int isWin(int row, int col);
	int winner = 0;
	SDL_Rect rect;
	SDL_Texture* win_case;
	int nextMove = O_CELL;
};