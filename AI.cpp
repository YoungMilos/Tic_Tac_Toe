#include "AI.h"
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

GomokuAI::GomokuAI(int depth) : depth(depth) {}

GomokuAI::~GomokuAI() {}

int GomokuAI::evaluateBoard(int board[BOARD_WIDTH][BOARD_HEIGHT]) {
    int aiScore = checkLines(board, X_CELL);
    int opponentScore = checkLines(board, O_CELL);

    // Thêm các yếu tố đánh giá phụ
    int centerControl = evaluateCenterControl(board);
    return aiScore - opponentScore + centerControl;
}

int GomokuAI::getPossibleMoves(int board[BOARD_WIDTH][BOARD_HEIGHT], vector<pair<int, int>>& moves) {
    static bool visited[BOARD_WIDTH][BOARD_HEIGHT];
    memset(visited, 0, sizeof(visited));
    moves.clear();

    // Tìm các ô trống gần quân cờ hiện có
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            if (board[x][y] != EMPTY_CELL) {
                for (int dx = -2; dx <= 2; dx++) {
                    for (int dy = -2; dy <= 2; dy++) {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (isValidPosition(nx, ny)) {
                            if (board[nx][ny] == EMPTY_CELL && !visited[nx][ny]) {
                                visited[nx][ny] = true;
                                moves.emplace_back(nx, ny);
                            }
                        }
                    }
                }
            }
        }
    }

    // Nếu không tìm thấy ô nào quanh quân cờ
    if (moves.empty()) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            for (int y = 0; y < BOARD_HEIGHT; y++) {
                if (board[x][y] == EMPTY_CELL) {
                    moves.emplace_back(x, y);
                }
            }
        }
    }

    // Sắp xếp theo điểm tiềm năng
    sort(moves.begin(), moves.end(), [&](const auto& a, const auto& b) {
        return quickEvaluate(board, a.first, a.second) > quickEvaluate(board, b.first, b.second);
        });

    return moves.size();
}

int GomokuAI::quickEvaluate(int board[BOARD_WIDTH][BOARD_HEIGHT], int x, int y) {
    int score = 0;
    constexpr int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

    board[x][y] = X_CELL;

    for (const auto& dir : directions) {
        int count = 1;
        bool openEnds[2] = { true, true };

        // Kiểm tra 2 hướng
        for (int side = 0; side < 2; side++) {
            for (int step = 1; step <= 4; step++) {
                int nx = x + (side ? -1 : 1) * dir[0] * step;
                int ny = y + (side ? -1 : 1) * dir[1] * step;

                if (!isValidPosition(nx, ny)) {
                    openEnds[side] = false;
                    break;
                }

                if (board[nx][ny] == X_CELL) count++;
                else if (board[nx][ny] != EMPTY_CELL) {
                    openEnds[side] = false;
                    break;
                }
            }
        }

        // Tính điểm
        if (count >= 5) score += 100000;
        else if (count == 4) score += (openEnds[0] && openEnds[1]) ? 10000 : 1000;
        else if (count == 3) score += (openEnds[0] && openEnds[1]) ? 500 : 100;
        else if (count == 2) score += (openEnds[0] && openEnds[1]) ? 50 : 10;
    }

    board[x][y] = EMPTY_CELL;
    return score;
}

int GomokuAI::minimax(int board[BOARD_WIDTH][BOARD_HEIGHT], int depth, int alpha, int beta, bool isMaximizing) {
    // Kiểm tra terminal state
    if (depth == 0) return evaluateBoard(board);

    vector<pair<int, int>> moves;
    getPossibleMoves(board, moves);

    if (moves.empty()) return evaluateBoard(board);

    // Kiểm tra win move
    int winScore = isMaximizing ? 1000000 - (this->depth - depth) : -1000000 + (this->depth - depth);
    for (const auto& move : moves) {
        board[move.first][move.second] = isMaximizing ? X_CELL : O_CELL;
        if (checkWin(board, move.first, move.second)) {
            board[move.first][move.second] = EMPTY_CELL;
            return winScore;
        }
        board[move.first][move.second] = EMPTY_CELL;
    }

    // Minimax với alpha-beta pruning
    if (isMaximizing) {
        int maxEval = numeric_limits<int>::min();
        for (const auto& move : moves) {
            board[move.first][move.second] = X_CELL;
            int eval = minimax(board, depth - 1, alpha, beta, false);
            board[move.first][move.second] = EMPTY_CELL;

            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else {
        int minEval = numeric_limits<int>::max();
        for (const auto& move : moves) {
            board[move.first][move.second] = O_CELL;
            int eval = minimax(board, depth - 1, alpha, beta, true);
            board[move.first][move.second] = EMPTY_CELL;

            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

pair<int, int> GomokuAI::bestMove(int board[BOARD_WIDTH][BOARD_HEIGHT]) {
    vector<pair<int, int>> moves;
    getPossibleMoves(board, moves);

    if (moves.empty()) return { -1, -1 };

    // Kiểm tra win move
    for (const auto& move : moves) {
        board[move.first][move.second] = X_CELL;
        if (checkWin(board, move.first, move.second)) {
            board[move.first][move.second] = EMPTY_CELL;
            return move;
        }
        board[move.first][move.second] = EMPTY_CELL;
    }

    // Kiểm tra opponent win move
    for (const auto& move : moves) {
        board[move.first][move.second] = O_CELL;
        if (checkWin(board, move.first, move.second)) {
            board[move.first][move.second] = EMPTY_CELL;
            return move;
        }
        board[move.first][move.second] = EMPTY_CELL;
    }

    // Tìm nước đi tốt nhất
    pair<int, int> bestMove = moves[0];
    int bestValue = numeric_limits<int>::min();
    const int maxMoves = min(20, (int)moves.size());

    for (int i = 0; i < maxMoves; i++) {
        const auto& move = moves[i];
        board[move.first][move.second] = X_CELL;
        int moveValue = minimax(board, depth - 1, numeric_limits<int>::min(), numeric_limits<int>::max(), false);
        board[move.first][move.second] = EMPTY_CELL;

        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }

    return bestMove;
}

bool GomokuAI::checkWin(int board[BOARD_WIDTH][BOARD_HEIGHT], int x, int y) {
    constexpr int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };
    int player = board[x][y];

    for (const auto& dir : directions) {
        int count = 1;

        // Đếm 2 hướng
        for (int side = 0; side < 2; side++) {
            for (int step = 1; step < 5; step++) {
                int nx = x + (side ? -1 : 1) * dir[0] * step;
                int ny = y + (side ? -1 : 1) * dir[1] * step;

                if (!isValidPosition(nx, ny) || board[nx][ny] != player) break;
                count++;
            }
        }

        if (count >= 5) return true;
    }

    return false;
}

int GomokuAI::evaluateCenterControl(int board[BOARD_WIDTH][BOARD_HEIGHT]) {
    // Đánh giá kiểm soát trung tâm
    int centerScore = 0;
    int centerX = BOARD_WIDTH / 2;
    int centerY = BOARD_HEIGHT / 2;
    int radius = min(BOARD_WIDTH, BOARD_HEIGHT) / 3;

    for (int x = centerX - radius; x <= centerX + radius; x++) {
        for (int y = centerY - radius; y <= centerY + radius; y++) {
            if (isValidPosition(x, y)) {
                if (board[x][y] == X_CELL) centerScore += 3;
                else if (board[x][y] == O_CELL) centerScore -= 3;
            }
        }
    }

    return centerScore;
}

bool GomokuAI::isValidPosition(int x, int y) {
    return x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT;
}

int GomokuAI::checkLines(int board[BOARD_WIDTH][BOARD_HEIGHT], int player) {
    int score = 0;
    constexpr int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            if (board[x][y] == player) {
                for (const auto& dir : directions) {
                    int count = 1;
                    bool openEnds[2] = { false, false };

                    // Kiểm tra 2 hướng
                    for (int side = 0; side < 2; side++) {
                        for (int step = 1; step <= 4; step++) {
                            int nx = x + (side ? -1 : 1) * dir[0] * step;
                            int ny = y + (side ? -1 : 1) * dir[1] * step;

                            if (!isValidPosition(nx, ny)) {
                                break;
                            }

                            if (board[nx][ny] == player) count++;
                            else {
                                if (board[nx][ny] == EMPTY_CELL) openEnds[side] = true;
                                break;
                            }
                        }
                    }

                    // Tính điểm
                    if (count >= 5) score += 100000;
                    else if (count == 4) score += (openEnds[0] && openEnds[1]) ? 10000 : 1000;
                    else if (count == 3) score += (openEnds[0] && openEnds[1]) ? 500 : 100;
                    else if (count == 2) score += (openEnds[0] && openEnds[1]) ? 50 : 10;
                }
            }
        }
    }

    return score;
}