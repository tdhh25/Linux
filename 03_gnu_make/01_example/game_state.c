// game_state.c - 游戏状态管理实现
#include "game_state.h"
#include "game_logic.h"
#include "board.h"

// 初始化游戏
void initGame(GameStateManager* game) {
    initBoard(&game->board);
    game->currentPlayer = BLACK;
    game->state = PLAYING;
}

// 切换玩家
void switchPlayer(GameStateManager* game) {
    game->currentPlayer = (game->currentPlayer == BLACK) ? WHITE : BLACK;
}

// 更新游戏状态
void updateGameState(GameStateManager* game, int row, int col) {
    if (game->state != PLAYING) return;
    
    if (placePiece(&game->board, row, col, game->currentPlayer)) {
        if (checkWin(&game->board, row, col)) {
            game->state = (game->currentPlayer == BLACK) ? BLACK_WIN : WHITE_WIN;
        } 
        else if (isBoardFull(&game->board)) {
            game->state = DRAW;
        }
        else {
            switchPlayer(game);
        }
    }
}

// 获取玩家名称
const char* getPlayerName(Piece player) {
    switch (player) {
        case BLACK: return "黑棋(X)";
        case WHITE: return "白棋(O)";
        default: return "无玩家";
    }
}

// 获取游戏状态名称
const char* getGameStateName(GameState state) {
    switch (state) {
        case PLAYING: return "游戏中";
        case BLACK_WIN: return "黑棋获胜";
        case WHITE_WIN: return "白棋获胜";
        case DRAW: return "平局";
        default: return "未知状态";
    }
}
