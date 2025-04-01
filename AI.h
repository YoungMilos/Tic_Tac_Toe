#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include "Settings.h"

#define WIN_LENGTH 5

using namespace std;

class GomokuAI {
public:
    GomokuAI(int depth);
	~GomokuAI();
    int evaluateBoard(int board[BOARD_WIDTH][BOARD_HEIGHT]);
    int minimax(int board[BOARD_WIDTH][BOARD_HEIGHT], int depth, int alpha, int beta, bool maximizingPlayer);
    int getPossibleMoves(int board[BOARD_WIDTH][BOARD_HEIGHT], vector<pair<int, int>>& moves);
    pair<int, int> bestMove(int board[BOARD_WIDTH][BOARD_HEIGHT]);
    bool isValidPosition(int x, int y);
	int checkLines(int board[BOARD_WIDTH][BOARD_HEIGHT], int player);
	bool checkWin(int board[BOARD_WIDTH][BOARD_HEIGHT], int x, int y);
	int quickEvaluate(int board[BOARD_WIDTH][BOARD_HEIGHT], int x, int y);
	int evaluateCenterControl(int board[BOARD_WIDTH][BOARD_HEIGHT]);
private:
    int depth;
};