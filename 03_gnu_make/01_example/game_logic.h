// game_logic.h - 游戏逻辑接口
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "constants.h"
#include "board.h"

int checkWin(const Board* board, int row, int col);
int checkDirection(const Board* board, int row, int col, int dx, int dy);

#endif
