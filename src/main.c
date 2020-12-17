#include "../inc/main.h"


void play(t_config *config);

int main() {

    mx_setup_environment();
    
    //default config
    t_config *config = (t_config *) malloc(sizeof(t_config));
    config->level = SPRINT00;
    config->sub_level = TASK00;
    config->platform_speed = 200;
    config->ticker = 0;
    getmaxyx(stdscr, config->max_y, config->max_x);
    config->num_platforms = 8;
    config->win = 0;
    config->score = 0;
    config->win_x = 100;

    mx_show_menu(config);

    endwin();
}
