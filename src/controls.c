/*
    Controls function, A,S,D and "Space"
*/

#include "../inc/controls.h"

enum e_sprite switch_movement(int ch, t_character *player, t_config *config) {
    enum e_sprite sprite = IDLE;
    switch (ch) {
        case 'q':
            config->win = 2;
        case KEY_UP: {
            if (!is_on_platform(player, config))
                return FALLING;
            player->direction = DOWN_OFF;
            player->y -= 10;
            break;
        }
        mvwinsch(config->window, 10, 5, (char)ch);
        wrefresh(config->window);
        case 'z':
        case 'Z':
            if (!is_on_platform(player, config))
                return FALLING;
            player->x -= 15;
            player->y -= 10;
            break;
        case 'C':
        case 'c':
            if (!is_on_platform(player, config))
                return FALLING;
            player->x += 15;
            player->y -= 10;
            break;
        case KEY_RIGHT:
            //Clear character
            player->x++;
            sprite = GO_RIGHT;
            break;
        case KEY_LEFT:
            //Clear character
            player->x--;
            sprite = GO_LEFT;
            break;
        case KEY_DOWN:
            //Clear character
            if (config->ticker % 100 == 0)
                player->y++;
            sprite = IDLE;
            break;
        default:
            player->direction = DOWN_ON;
            sprite = IDLE;
            break;
    }
    return sprite;
}

enum e_sprite mx_process_input(t_character *player, t_config *config) {
    // body center is player->y, legs are player->y + 1, under legs - player->y + 2
    if (config->ticker % 25 != 0) {
        if (player->direction == DOWN_OFF)
            return IDLE;
        else {
            return FALLING;
        }
    }
    if (!is_on_platform(player, config)) {
        player->y++;
        return switch_movement(getch(), player, config);
    } else {
        player->direction = DOWN_OFF;
    }

    return switch_movement(getch(), player, config);
}
