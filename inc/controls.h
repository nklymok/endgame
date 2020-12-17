#pragma once

#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "main.h"
#include "character.h"

enum e_sprite mx_process_input(t_character *player, t_config *config);
