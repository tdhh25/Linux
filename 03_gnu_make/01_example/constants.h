// constants.h - 定义常量和枚举
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BOARD_SIZE 15
#define WIN_COUNT 5

// 棋子类型
typedef enum {
    EMPTY,
    BLACK,
    WHITE
} Piece;

// 游戏状态
typedef enum {
    PLAYING,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
} GameState;

#endif
