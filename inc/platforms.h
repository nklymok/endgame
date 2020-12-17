#pragma once

#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "character.h"
#include "controls.h"
#include "structs.h"

//defines
#define SYSTEM_TICK 1000

//prototypes

//creates string filled with stars
char *stars_string(int len);
//creates string filled with spaces (to erase platform)
char *space_string(int len);
//prints platform and moves in one step up
void print_platform(t_platform *platform, int num, t_config *config);
//choose len from level
int platform_len(t_level level);
//selects string for sub level
char *print_task(t_sub_level sub_level);
//place task name into platform
void place_holder(char *stars, t_sub_level sub_level);
//generates new platform
void new_platform(t_platform *platform, int num, t_config *config);
//initialization of all platforms
t_platform *initialize_platforms (t_config *config);
//initialization of all platforms
t_platform *initialize_platforms (t_config *config);
//prints and updates all platforms
void update_platforms(t_platform *platforms, t_config *config);
//play
void play(t_config *config);
