#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef struct {
    int row;
    int col;
} Player;

void player_find(const Map* map, Player* player);
int player_move(Map* map, Player* player, int drow, int dcol);

#endif
