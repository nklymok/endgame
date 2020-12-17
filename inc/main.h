#pragma once

#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include "character.h"
#include "controls.h"

void mx_setup_environment();

void mx_test_platforms(t_character *player);

void mx_show_menu();
