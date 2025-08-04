#include "player.h"

void player_find(const Map* map, Player* player) {
    for (int r = 0; r < map->rows; r++) {
        for (int c = 0; c < map->cols; c++) {
            if (map->grid[r][c] == PLAYER || map->grid[r][c] == PLAYER_ON_TARGET) {
                player->row = r;
                player->col = c;
                return;
            }
        }
    }
}

int player_move(Map* map, Player* player, int drow, int dcol) {
    int new_r = player->row + drow;
    int new_c = player->col + dcol;
    
    // 检查边界
    if (new_r < 0 || new_r >= map->rows || new_c < 0 || new_c >= map->cols)
        return 0;
    
    TileType next = map->grid[new_r][new_c];
    
    // 撞墙
    if (next == WALL)
        return 0;
    
    // 推箱子
    if (next == BOX || next == BOX_ON_TARGET) {
        int box_r = new_r + drow;
        int box_c = new_c + dcol;
        
        // 检查箱子能否推动
        if (box_r < 0 || box_r >= map->rows || box_c < 0 || box_c >= map->cols)
            return 0;
        
        TileType beyond = map->grid[box_r][box_c];
        if (beyond != EMPTY && beyond != TARGET)
            return 0;
        
        // 移动箱子
        if (beyond == TARGET) {
            map->grid[box_r][box_c] = BOX_ON_TARGET;
        } else {
            map->grid[box_r][box_c] = BOX;
        }
        
        // 更新箱子原来的位置
        if (next == BOX_ON_TARGET) {
            map->grid[new_r][new_c] = TARGET;
        } else {
            map->grid[new_r][new_c] = EMPTY;
        }
    }
    
    // 移动玩家
    TileType current = map->grid[player->row][player->col];
    if (current == PLAYER_ON_TARGET) {
        map->grid[player->row][player->col] = TARGET;
    } else {
        map->grid[player->row][player->col] = EMPTY;
    }
    
    if (map->grid[new_r][new_c] == TARGET) {
        map->grid[new_r][new_c] = PLAYER_ON_TARGET;
    } else {
        map->grid[new_r][new_c] = PLAYER;
    }
    
    player->row = new_r;
    player->col = new_c;
    return 1;
}
