#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"

typedef struct {
    Map map;
    Player player;
    int level;
    int moves;
    int quit;
} Game;

void game_init(Game* game);
void game_run(Game* game);
void game_process_input(Game* game);

#endif
