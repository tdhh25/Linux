// game_state.h - 游戏状态管理
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "constants.h"
#include "board.h"

// 游戏状态结构
typedef struct {
    Board board;
    Piece currentPlayer;
    GameState state;
} GameStateManager;

void initGame(GameStateManager* game);
void switchPlayer(GameStateManager* game);
void updateGameState(GameStateManager* game, int row, int col);
const char* getPlayerName(Piece player);
const char* getGameStateName(GameState state);

#endif
