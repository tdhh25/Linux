#include <stdio.h>
#include "game.h"
#include "render.h"

void game_init(Game* game) {
    game->level = 0;
    game->moves = 0;
    game->quit = 0;
    map_init(&game->map);
    map_load_level(&game->map, game->level);
    player_find(&game->map, &game->player);
}

void game_process_input(Game* game) {
    char input;
    printf("Enter move (w/a/s/d/r/q): ");
    scanf(" %c", &input);  // 空格跳过空白字符
    
    int drow = 0, dcol = 0;
    
    switch(input) {
        case 'w': case 'W': drow = -1; break;
        case 's': case 'S': drow = 1; break;
        case 'a': case 'A': dcol = -1; break;
        case 'd': case 'D': dcol = 1; break;
        case 'r': case 'R': 
            map_load_level(&game->map, game->level);
            player_find(&game->map, &game->player);
            game->moves = 0;
            return;
        case 'q': case 'Q': game->quit = 1; return;
        default: return;
    }
    
    if (player_move(&game->map, &game->player, drow, dcol)) {
        game->moves++;
    }
}

void game_run(Game* game) {
    while (!game->quit) {
        render_map(&game->map);
        printf("\nLevel: %d  Moves: %d\n", game->level + 1, game->moves);
        printf("Controls: W=Up, S=Down, A=Left, D=Right, R=Reset, Q=Quit\n");
        
        game_process_input(game);
        
        if (map_is_complete(&game->map)) {
            render_map(&game->map);
            printf("\nLevel Complete! Moves: %d\n", game->moves);
            printf("Press Enter to continue...");
            getchar(); // 清除输入缓冲区
            getchar(); // 等待回车
            
            if (++game->level >= 2) {
                printf("\nYou win! Game Over.\n");
                game->quit = 1;
            } else {
                map_load_level(&game->map, game->level);
                player_find(&game->map, &game->player);
                game->moves = 0;
            }
        }
    }
}
