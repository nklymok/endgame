#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <stdbool.h>
#include "structs.h"

enum e_sprite {
    IDLE,
    GO_RIGHT,
    GO_LEFT,
    FALLING
};

enum e_direction {
    DOWN_ON,
    DOWN_OFF
};

typedef struct s_character {
    int x;
    int y;
    int inertia;
    char** sprite;
    enum e_direction direction;
}               t_character;

void mx_draw_character(t_character *player, enum e_sprite move, t_config *config);

void mx_erase_character(t_character *player, t_config *config);

bool is_on_platform(t_character *player, t_config *config);

t_character *mx_initialize_character();
