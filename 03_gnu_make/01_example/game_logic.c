// game_logic.c - 游戏逻辑实现
#include "game_logic.h"
#include "constants.h"

// 检查指定方向是否有连续棋子
int checkDirection(const Board* board, int row, int col, int dx, int dy) {
    Piece player = board->grid[row][col];
    int count = 1; // 当前位置已有1个棋子
    
    // 正向检查
    for (int i = 1; i < WIN_COUNT; i++) {
        int r = row + dx * i;
        int c = col + dy * i;
        
        if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE || 
            board->grid[r][c] != player) {
            break;
        }
        count++;
    }
    
    // 反向检查
    for (int i = 1; i < WIN_COUNT; i++) {
        int r = row - dx * i;
        int c = col - dy * i;
        
        if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE || 
            board->grid[r][c] != player) {
            break;
        }
        count++;
    }
    
    return count >= WIN_COUNT;
}

// 检查是否获胜
int checkWin(const Board* board, int row, int col) {
    if (board->pieceCount < WIN_COUNT * 2 - 1) 
        return 0;
    
    // 检查四个方向
    int directions[4][2] = {
        {1, 0},   // 垂直
        {0, 1},   // 水平
        {1, 1},   // 右下
        {1, -1}   // 左下
    };
    
    for (int d = 0; d < 4; d++) {
        if (checkDirection(board, row, col, directions[d][0], directions[d][1])) {
            return 1;
        }
    }
    
    return 0;
}
