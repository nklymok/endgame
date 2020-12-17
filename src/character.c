#include "../inc/character.h"
#include <unistd.h>

// action: 0 - idle, 1 - right, 2 - left
void mx_draw_character(t_character *player, enum e_sprite move, t_config *config) {
    char *idle[] = {"O",
                    "|",
                    "|"};
    char *right[] = {" >",
                     "/|\\",
                     "/ \\"};
    char *left[] = {" <",
                    "/|\\",
                    "/ \\"};
    char *falling[] = {"\\0/",
                       " | ",
                       "/ \\"};
    char **sprite;

    switch (move) {
        case IDLE:
            sprite = idle;
            break;
        case GO_RIGHT:
            sprite = right;
            break;
        case GO_LEFT:
            sprite = left;
            break;
        case FALLING:
            sprite = falling;
            break;
        default:
            sprite = idle;
    }
    if (is_on_platform(player, config)) {
        if (sprite == right)
            player->inertia += 10000;
        else if (sprite == left)
            player->inertia -= 10000;
        else if (player->inertia < 0)
            player->inertia += 200;
        else if (player->inertia > 0)
            player->inertia -= 200;
        if (sprite == idle && player->inertia != 0) {
            if (player->inertia > 0) sprite = right;
            else sprite = left;
        }
    }
    mvwprintw(config->window, player->y - 1, player->x + 3, "%s", sprite[0]);
    mvwprintw(config->window, player->y, player->x + 3, "%s", sprite[1]);
    mvwprintw(config->window, player->y + 1, player->x + 3, "%s", sprite[2]);
    wrefresh(config->window);
}

void mx_erase_character(t_character *player, t_config *config) {
    char *eraser[] = {"   ",
                      "    ",
                      "    "};
    mvwprintw(config->window, player->y - 1, player->x + 3, "%s", eraser[0]);
    mvwprintw(config->window, player->y, player->x + 3, "%s", eraser[1]);
    mvwprintw(config->window, player->y + 1, player->x + 3, "%s", eraser[2]);
}

bool is_on_platform(t_character *player, t_config *config) {
    int x;
    int y;
    unsigned int platform_char[] = {'T','A','S','K','0','1','2','3','4','5','6','7','8','9','*'};
    int platform_char_len = 15;
    getmaxyx(config->window, y, x);
    for (int i = 0; i < platform_char_len; i++) {
        if (player->y + 2 < y && mvwinch(config->window, player->y + 2, player->x + 3) == platform_char[i]) {
            player->direction = DOWN_OFF;
            return true;
        }
    }
    player->direction = DOWN_ON;
    return false;
}

t_character *mx_initialize_character() {
    int rows;
    int cols;

    getmaxyx(stdscr, rows, cols);
    t_character *player = (t_character *) malloc(sizeof(t_character));
    player->x = rows / 2;
    player->y = cols / 2;
    player->inertia = 0;
    player->direction = DOWN_OFF;
    return player;
}
