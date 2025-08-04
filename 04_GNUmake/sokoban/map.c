#include "map.h"

void map_init(Map* map) {
    map->rows = 0;
    map->cols = 0;
}

int map_load_level(Map* map, int level) {
    // 硬编码两个关卡
    static const char* levels[] = {
        // Level 1
        "############"
        "#         ##"
        "#  ###  $ ##"
        "#  $@#   ##"
        "## $ #  ####"
        " ##.   ##"
        "  ##.  #"
        "   #####",
        
        // Level 2
        "  #####    "
        "###   #    "
        "# $@  #    "
        "# $$  #    "
        "#  ## #####"
        "## . .   #"
        " # . .   #"
        " ########"
    };
    
    int num_levels = sizeof(levels)/sizeof(levels[0]);
    if (level < 0 || level >= num_levels) 
        return 0;
    
    const char* data = levels[level];
    int idx = 0;
    map->rows = 0;
    map->cols = 0;
    
    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            if (!data[idx]) break;
            
            switch(data[idx++]) {
                case '#': map->grid[r][c] = WALL; break;
                case ' ': map->grid[r][c] = EMPTY; break;
                case '$': map->grid[r][c] = BOX; break;
                case '.': map->grid[r][c] = TARGET; break;
                case '@': map->grid[r][c] = PLAYER; break;
                case '*': map->grid[r][c] = BOX_ON_TARGET; break;
                case '+': map->grid[r][c] = PLAYER_ON_TARGET; break;
                default: continue; // 跳过无效字符
            }
            
            if (c >= map->cols) map->cols = c + 1;
        }
        if (map->cols > 0) map->rows = r + 1;
        if (!data[idx]) break;
    }
    return 1;
}

int map_is_complete(const Map* map) {
    for (int r = 0; r < map->rows; r++) {
        for (int c = 0; c < map->cols; c++) {
            if (map->grid[r][c] == BOX) 
                return 0; // 还有未完成的箱子
        }
    }
    return 1;
}
