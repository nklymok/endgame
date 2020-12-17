#include "about_us.h"



void print_name(char *filename, int x_pos, int y_pos, int rows, int cols) {
    FILE * fp;
    fp = fopen(filename, "r");
    char **buffer = malloc(sizeof(char*) * rows);
    char **image = malloc(sizeof(char*) * rows);
    for (int i = 0; i < rows; i++) {
        buffer[i] = malloc(sizeof(char) * (cols + 1));
        image[i] = malloc(sizeof(char) * (cols + 1));
        for (int sym = 0; sym < cols+1; sym++) {
            buffer[i][sym] = '\0';
            image[i][sym] = '\0';
        }
    }
    //read file
    for (int i = 0; i < 6; i++)
        fread(buffer[i], cols, sizeof(char), fp);
    fclose(fp);
    //print file
    for(int i = 0; i < cols; i++) {
            for(int j = 0; j < rows; j++) {
                move(j + y_pos, cols - i + x_pos);
                clrtoeol();
                strncpy(image[j], buffer[j], i);
                mvprintw(j + y_pos, cols - i + x_pos, "%s", image[j]);
            }
            refresh();
            usleep(SNAP_DELAY);
        }
    //free routine
    for (int i = 0; i < rows; i++) {
        free(buffer[i]);
        free(image[i]);
        buffer[i] = NULL;
        image[i] = NULL;
    }
    free(buffer);
    free(image);
    buffer = NULL;
    image = NULL;
}

void about_us(void) {
    clear();
    attrset(A_NORMAL);
    print_name("./resources/ostepura.txt", 0, 0, 6, 75);
    sleep(DELAY);
    print_name("./resources/pchernushe.txt", 0, 8, 6, 91);
    sleep(DELAY);
    print_name("./resources/vbuhryi.txt", 0, 16, 6, 67);
    sleep(DELAY);
    print_name("./resources/nklymok.txt", 0, 24, 6, 67);
    sleep(DELAY);
    print_name("./resources/abakaliuk.txt", 0, 32, 6, 83);
    sleep(DELAY);
    attrset(A_BLINK);
    mvprintw(40, 40, "Press any key to exit to main menu.");
    refresh();
    sleep(DELAY*3);
}
