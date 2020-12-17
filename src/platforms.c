#include "../inc/platforms.h"

//creates string filled with stars
char *stars_string(int len) {
    char *str = (char *) malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        str[i] = '*';
    str[len] = '\0';
    return str;
}

//creates string filled with spaces (to erase platform)
char *space_string(int len) {
    char *str = (char *) malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        str[i] = ' ';
    str[len] = '\0';
    return str;
}

//prints platform and moves in one step up
void print_platform(t_platform *platform, int num, t_config *config) {
     mvwprintw(config->window, platform[num].y, platform[num].x, "%s", platform[num].eraser);
    platform[num].y--;
    if(config->level == RACE00 || config->level == RACE01 || config->level == ENDGAME)
        platform[num].x += rand() % 2 - 1;
    mvwprintw(config->window, platform[num].y, platform[num].x, "%s", platform[num].text);
}

//choose len from level
int platform_len(t_level level) {

    switch (level) {
        case SPRINT00:
            return 16;
        case SPRINT01:
            return 15;
        case SPRINT02:
            return 14;
        case SPRINT03:
            return 13;
        case SPRINT04:
            return 12;
        case SPRINT05:
            return 11;
        case SPRINT06:
            return 10;
        case SPRINT07:
            return 9;
        case RACE00:
            return 9;
        case SPRINT08:
            return 9;
        case SPRINT09:
            return 8;
        case SPRINT10:
            return 7;
        case SPRINT11:
            return 6;
        case RACE01:
            return 6;
        case ENDGAME:
            return 6;
    }
}

//selects string for sub level
char *print_task(t_sub_level sub_level) {
    switch (sub_level) {
        case TASK00:
            return "TASK00";
        case TASK01:
            return "TASK01";
        case TASK02:
            return "TASK02";
        case TASK03:
            return "TASK03";
        case TASK04:
            return "TASK04";
        case TASK05:
            return "TASK05";
        case TASK06:
            return "TASK06";
        case TASK07:
            return "TASK07";
        case TASK08:
            return "TASK08";
        case TASK09:
            return "TASK09";
        case TASK10:
            return "TASK10";
        case TASK11:
            return "TASK11";
    }
}

//selects string for level
char *print_level(t_level level) {
    switch (level) {
        case SPRINT00:
            return "SPRINT00";
        case SPRINT01:
            return "SPRINT01";
        case SPRINT02:
            return "SPRINT02";
        case SPRINT03:
            return "SPRINT03";
        case SPRINT04:
            return "SPRINT04";
        case SPRINT05:
            return "SPRINT05";
        case SPRINT06:
            return "SPRINT06";
        case SPRINT07:
            return "SPRINT07";
        case RACE00:
            return "  RACE00";
        case SPRINT08:
            return "SPRINT08";
        case SPRINT09:
            return "SPRINT09";
        case SPRINT10:
            return "SPRINT10";
        case SPRINT11:
            return "SPRINT11";
        case RACE01:
            return "  RACE01";
        case ENDGAME:
            return " ENDGAME";
    }
}    

//place task name into platform
void place_holder(char *stars, t_sub_level sub_level) {
    int len = strlen(stars);
    //where to put string
    int pos = (len - 6) / 2;
    strncpy(&stars[pos], print_task(sub_level), 6);
}

//generates new platform
void new_platform(t_platform *platform, int num, t_config *config) {
    int len = platform_len(config->level);
    //put string into platform
    platform[num].text = stars_string(len);
    place_holder(platform[num].text, config->sub_level);
    //put eraser for that platform
    platform[num].eraser = space_string(len);
    //put rand coordinates
    platform[num].x = rand() % (config->win_x - len - 2) + 2;
    //with random +-offset
    platform[num].y = config->max_y - 2 +rand()%4 - 2;
}

//initialization of all platforms
t_platform *initialize_platforms(t_config *config) {
    //allocate N structs
    t_platform *platforms = malloc(sizeof(t_platform) * (config->num_platforms));
    //initialize all platforms
    int offset = 0;
    for (int i = 0; i < config->num_platforms; i++) {
        new_platform(platforms, i, config);
        platforms[i].y -= offset;
        offset += (config->max_y)/(config->num_platforms);
    }
    return platforms;
}

//prints and updates all platforms
void update_platforms(t_platform *platforms, t_config *config) {
    for (int i = 0; i < config->num_platforms; i++) {
        print_platform(platforms, i, config);
        //if platform is on top, make new platforms
        if (platforms[i].y < 5) {
            new_platform(platforms, i, config);
            if (config->sub_level == TASK11) {
                config->sub_level = TASK00;
                if (config->level < ENDGAME)
                    config->level++;
                else {
                    config->win = true;
                }
                config->platform_speed -= 10;
            } else {
                config->sub_level++;
                config->score += (float) 200 / config->platform_speed * 100;
            }
        }
    }
}

//prints status bar
void status_bar(t_config *config) {
    //print level
        mvwprintw(config->window, 2, 4, "Level: %s", print_level(config->level));
    //print sub_level
        mvwprintw(config->window, 3, 4, "Sub-level: %s", print_task(config->sub_level));
    //print speed
        mvwprintw(config->window, 2, config->win_x - 25, "Speed: %.0f%%", (float)200/config->platform_speed*100);
    //print score
        mvwprintw(config->window, 3, config->win_x - 25, "Score: %.2f", config->score);
    mvwhline(config->window, 4, 0, '-', config->win_x);
}

/*----- HOW TO USE IN MAIN PLAY FUNCTION-----*/
void play(t_config *config) {
    clear();
    t_character *player = mx_initialize_character();
    //spawn place
    player->x = config->win_x/2;
    player->y = 5;

    //make window
    config->window = newwin(config->max_y, config->win_x, 0, (config->max_x - config->win_x)/2);
    wclear(config->window);
    //initialize platforms at start
    t_platform *platforms = initialize_platforms(config);
    //first platform
    platforms[5].x = config->win_x/2 - 3;

    //main infinite loop
    while (1) {
        //prints status bar
        status_bar(config);

        /*----- HERE ALL CONTROL ROUTINE CAN BE PLACED ------*/
        mx_erase_character(player, config);
        //handle wall jumps
        if (player->x > config->win_x)
            player->x = 1;
        if (player->x < 1)
            player->x = config->win_x + player->x;
        mx_draw_character(player, mx_process_input(player, config), config);

        //lose shit (if over max y or above status bar)
        if (player->y > config->max_y)
            config->win = -1;
        /*----- HERE ALL CONTROL ROUTINE CAN BE PLACED ------*/
    //print all platforms
        if (config->ticker % config->platform_speed == 0) {
            if (is_on_platform(player, config)) {
                mx_erase_character(player, config);
                player->y--;
            }
            update_platforms(platforms, config);
            wrefresh(config->window);
        }

    //prints status bar
    status_bar(config);
    //draw box
    box(config->window, 0, 0);
    wrefresh(config->window);

        //update system tick
        config->ticker++;
        usleep(SYSTEM_TICK);

        //end game -win
        if(config->win == 1){
            wclear(config->window);
            mvwprintw(config->window, config->max_y / 2, config->win_x / 2, "YOU WIN");
            mvwprintw(config->window, config->max_y / 2 + 2, config->win_x / 2 - 5, "Your score: %.2f", config->score);
            wrefresh(config->window);
            sleep(3);
            getch();
            return;
        }

    // end game -lose
        if(config->win == -1){
            wclear(config->window);
            mvwprintw(config->window, config->max_y / 2, config->win_x / 2, "F&#K!");
            mvwprintw(config->window, config->max_y / 2 + 2, config->win_x / 2 - 5, "Your score: %.2f", config->score);
            wrefresh(config->window);
            sleep(3);
            getch();
            return;
        }

        //end game exit to main menu
        if(config->win == 2){
            wclear(config->window);
            wrefresh(config->window);
            return;
        }
    }
}
