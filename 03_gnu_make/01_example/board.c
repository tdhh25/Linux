// board.c - 棋盘操作实现
#include <stdio.h>
#include "board.h"
#include "constants.h"

// 初始化棋盘
void initBoard(Board* board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->grid[i][j] = EMPTY;
        }
    }
    board->pieceCount = 0;
}

// 打印棋盘
void printBoard(const Board* board) {
    // 打印列号
    printf("   ");
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        // 打印行号
        printf("%2d ", i);
        
        for (int j = 0; j < BOARD_SIZE; j++) {
            char c;
            switch (board->grid[i][j]) {
                case BLACK: c = 'X'; break;
                case WHITE: c = 'O'; break;
                default: c = '.'; break;
            }
            printf(" %c ", c);
        }
        printf("\n");
    }
}

// 检查移动是否有效
int isValidMove(const Board* board, int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && 
            col >= 0 && col < BOARD_SIZE && 
            board->grid[row][col] == EMPTY);
}

// 放置棋子
int placePiece(Board* board, int row, int col, Piece player) {
    if (!isValidMove(board, row, col)) {
        return 0;
    }
    
    board->grid[row][col] = player;
    board->pieceCount++;
    return 1;
}

// 检查棋盘是否已满
int isBoardFull(const Board* board) {
    return board->pieceCount >= BOARD_SIZE * BOARD_SIZE;
}
