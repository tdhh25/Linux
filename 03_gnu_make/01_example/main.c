// main.c - 主程序入口
#include <stdio.h>
#include "board.h"
#include "game_state.h"
#include "input.h"

int main() {
    GameStateManager game;
    initGame(&game);
    
    printf("欢迎来到五子棋游戏！\n");
    printf("黑棋(X)先行，白棋(O)后行\n");
    printf("输入行号和列号落子（例如：7 7）\n");
    
    while (game.state == PLAYING) {
        printBoard(&game.board);
        
        // 提示当前玩家
        printf("\n当前状态: %s\n", getGameStateName(game.state));
        printf("当前玩家: %s\n", getPlayerName(game.currentPlayer));
        
        // 获取玩家输入
        int row, col;
        if (!getPlayerMove(&row, &col)) {
            continue;
        }
        
        // 更新游戏状态
        updateGameState(&game, row, col);
    }
    
    // 游戏结束，显示结果
    printBoard(&game.board);
    printf("\n游戏结束！%s\n", getGameStateName(game.state));
    
    return 0;
}
