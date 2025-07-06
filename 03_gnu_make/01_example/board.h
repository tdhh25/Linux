// board.h - 棋盘操作接口
#ifndef BOARD_H
#define BOARD_H

#include "constants.h"

// 棋盘结构
typedef struct {
    Piece grid[BOARD_SIZE][BOARD_SIZE];
    int pieceCount;
} Board;

void initBoard(Board* board);
void printBoard(const Board* board);
int isValidMove(const Board* board, int row, int col);
int placePiece(Board* board, int row, int col, Piece player);
int isBoardFull(const Board* board);

#endif
