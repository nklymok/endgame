#include "../inc/main.h"

void mx_setup_environment() {
        initscr();
        clear();
        noecho();
        curs_set(0);
        srand(time(NULL));
        cbreak();
        nodelay(stdscr, true);
        keypad(stdscr, TRUE);
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
}
