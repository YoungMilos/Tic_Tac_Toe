#include "Board.h"
#include <vector>

using namespace std;

Board::Board()
{
	moveSound = AssetManager::getInstance()->getSoundBuffer("button_click_sound.wav");
	cell_emtpy = AssetManager::getInstance()->getTexture("cell_empty.png");
	cell_x = AssetManager::getInstance()->getTexture("cell_x.png");
	cell_o = AssetManager::getInstance()->getTexture("cell_o.png");
	win_up = AssetManager::getInstance()->getTexture("win_up.png");
	win_down = AssetManager::getInstance()->getTexture("win_down.png");
	win_horizontal = AssetManager::getInstance()->getTexture("win_horizontal.png");
	win_vertical = AssetManager::getInstance()->getTexture("win_vertical.png");
	cell_rect.w = 40;
	cell_rect.h = 40;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			gameBoard[i][j] = 0;
		}
	}
}

Board::~Board()
{
}

void Board::reset()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            gameBoard[i][j] = 0;
        }
    }
    winner = 0;
}

void Board::renderBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			cell_rect.x = i * 40 + BOARD_X;
			cell_rect.y = j * 40 + BOARD_Y;
			if (gameBoard[i][j] == 0)
			{
				SDL_RenderCopy(gWindow->getRenderer(), cell_emtpy, NULL, &cell_rect);
			}
			else if (gameBoard[i][j] == 1)
			{
				SDL_RenderCopy(gWindow->getRenderer(), cell_x, NULL, &cell_rect);
			}
			else
			{
				SDL_RenderCopy(gWindow->getRenderer(), cell_o, NULL, &cell_rect);
			}
		}
	}
}

void Board::move(int col, int row)
{
	if (row >= 0 && row < BOARD_HEIGHT && col >= 0 && col < BOARD_WIDTH && gameBoard[col][row] == EMPTY_CELL)
	{
		Mix_PlayChannel(-1, moveSound, 0);
		gameBoard[col][row] = nextMove;
		nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
	}
}

void Board::handleBoardEvent()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	x -= BOARD_X;
	y -= BOARD_Y;
	if (x >= 0 && x < BOARD_WIDTH * 40 && y >= 0 && y < BOARD_HEIGHT * 40)
	{
		move(x / 40, y / 40);
		renderBoard();
        cout << "oke" << endl;


		winner = isWin(x / 40, y / 40);
	}
}

int Board::isWin(int col, int row)
{
    int x, y, cnt;
    vector <pair<int, int>> moved;

	//SDL_Rect rect;


    // kiểm tra chéo xuống
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (col + 1 < BOARD_WIDTH && row + 1 < BOARD_HEIGHT && gameBoard[x + 1][y + 1] == gameBoard[col][row]) {
        x++;
        y++;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (col - 1 >= 0 && row - 1 >= 0 && gameBoard[x - 1][y - 1] == gameBoard[col][row]) {
        x--;
        y--;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt >= 5) {
		rect.x = moved[moved.size() - 1].first * 40 + BOARD_X;
	    rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y;
		rect.w = 200;
		rect.h = 200;
        SDL_RenderCopy(gWindow->getRenderer(), win_down, NULL, &rect);
   
		win_case = win_down;
		
        return nextMove;
    }
    
    // kiểm tra ngang
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (col + 1 < BOARD_WIDTH && gameBoard[x + 1][y] == gameBoard[col][row]) {
        x++;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (col - 1 >= 0 && gameBoard[x - 1][y] == gameBoard[col][row]) {
        x--;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt >= 5) {
		rect.x = moved[moved.size() - 1].first * 40 + BOARD_X;
		rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y - 80;
		rect.w = 200;
		rect.h = 200;
		//SDL_RenderCopy(gWindow->getRenderer(), win_horizontal, NULL, &rect);
        
		win_case = win_horizontal;

        return nextMove;
    }

    // kiểm tra dọc
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (row + 1 < BOARD_HEIGHT && gameBoard[x][y + 1] == gameBoard[col][row]) {
        y++;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (row - 1 >= 0 && gameBoard[x][y - 1] == gameBoard[col][row]) {
        y--;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt >= 5) {
        rect.x = moved[moved.size() - 1].first * 40 + BOARD_X - 80;
        rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y;
        rect.w = 200;
        rect.h = 200;
       // SDL_RenderCopy(gWindow->getRenderer(), win_vertical, NULL, &rect);
		win_case = win_vertical;

        return nextMove;
    }

    // kiểm tra chéo lên
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (col + 1 < BOARD_WIDTH && row - 1 >= 0 && gameBoard[x + 1][y - 1] == gameBoard[col][row]) {
        x++;
        y--;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (col - 1 >= 0 && row + 1 < BOARD_HEIGHT && gameBoard[x - 1][y + 1] == gameBoard[col][row]) {
        x--;
        y++;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt >= 5) {
        rect.x = moved[moved.size() - 1].first * 40 + BOARD_X;
        rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y - 160;
        rect.w = 200;
        rect.h = 200;
        //SDL_RenderCopy(gWindow->getRenderer(), win_up, NULL, &rect);
		win_case = win_up;

        return nextMove;
    }
    

    return 0;
}
