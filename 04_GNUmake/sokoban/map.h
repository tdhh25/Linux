#ifndef MAP_H
#define MAP_H

#define MAX_ROWS 10
#define MAX_COLS 15

typedef enum {
    EMPTY,
    WALL,
    BOX,
    TARGET,
    BOX_ON_TARGET,
    PLAYER,
    PLAYER_ON_TARGET
} TileType;

typedef struct {
    int rows;
    int cols;
    TileType grid[MAX_ROWS][MAX_COLS];
} Map;

void map_init(Map* map);
int map_load_level(Map* map, int level);
int map_is_complete(const Map* map);

#endif
