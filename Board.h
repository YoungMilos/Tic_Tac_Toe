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
	SDL_Texture* win_horizontal;
	SDL_Texture* win_down;
	SDL_Texture* win_up;
	SDL_Texture* win_vertical;
	

	SDL_Rect cell_rect;
	int gameBoard[BOARD_WIDTH][BOARD_HEIGHT];
	

	Mix_Chunk* moveSound;
public:
	bool moved = false;
	SDL_Texture* cell_x;
	SDL_Texture* cell_o;

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