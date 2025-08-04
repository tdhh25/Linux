#include <stdio.h>
#include "render.h"

void render_map(const Map* map) {
    printf("\n");
    for (int r = 0; r < map->rows; r++) {
        for (int c = 0; c < map->cols; c++) {
            switch(map->grid[r][c]) {
                case WALL:        printf("■ "); break;
                case EMPTY:       printf("  "); break;
                case BOX:         printf("□ "); break;
                case TARGET:      printf(". "); break;
                case BOX_ON_TARGET: printf("★ "); break;
                case PLAYER:      printf("♀ "); break;
                case PLAYER_ON_TARGET: printf("♀ "); break; // 简化显示
                default:          printf("? "); break;
            }
        }
        printf("\n");
    }
}
