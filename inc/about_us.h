#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SNAP_DELAY 30000
#define DELAY 1

void print_name(char *filename, int x_pos, int y_pos, int rows, int cols);
void about_us(void);
