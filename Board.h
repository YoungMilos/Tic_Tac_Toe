#pragma once
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "AssetManager.h"

#include "Settings.h"
#include "Window.h"

extern Window* gWindow;

class Board
{
private:
	SDL_Texture* cell_emtpy;
	SDL_Texture* cell_x;
	SDL_Texture* cell_o;
	SDL_Texture* win_horizontal;
	SDL_Texture* win_down;
	SDL_Texture* win_up;
	SDL_Texture* win_vertical;

	SDL_Rect cell_rect;
	int gameBoard[BOARD_WIDTH][BOARD_HEIGHT];
	int nextMove = O_CELL;
	
	
public:
	Board();
	~Board();
	void renderBoard();
	void move(int x, int y);
	void handleBoardEvent();
	int isWin(int row, int col);
	int winner = 0;
};