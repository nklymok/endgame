#pragma once

#include <stdbool.h>
#include <ncurses.h>

//levels enum
typedef enum e_level {
    SPRINT00,
    SPRINT01,
    SPRINT02,
    SPRINT03,
    SPRINT04,
    SPRINT05,
    SPRINT06,
    SPRINT07,
    RACE00,
    SPRINT08,
    SPRINT09,
    SPRINT10,
    SPRINT11,
    RACE01,
    ENDGAME
}             t_level;

//sub-levels enum
typedef enum e_sub_level {
    TASK00,
    TASK01,
    TASK02,
    TASK03,
    TASK04,
    TASK05,
    TASK06,
    TASK07,
    TASK08,
    TASK09,
    TASK10,
    TASK11,
}             t_sub_level;

//platform object
typedef struct  s_platform {
    int x;
    int y;
    char *text;
    char *eraser;
    bool real;
    int time_to_live;
}               t_platform;

//config structure
typedef struct  s_config {
    t_level level;
    t_sub_level sub_level;
    int platform_speed;
    int max_x;
    int max_y;
    int win_x;
    long ticker;
    int num_platforms;
    float score;
    int win;
    WINDOW *window;
}                  t_config;
