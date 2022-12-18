#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 21
#define COLS 80

int main() {
    srand(time(NULL));            /* for random */
    char dog = '@', bone = 'I';
    int c;
    int y = 5, x = 10;			  /* dog position */
    /* bone position */
    int ay = (rand() % (ROWS-2)) + 1;
    int ax = (rand() % (COLS-2)) + 1;
    int score = 0;
    char map[ROWS][COLS];

    initscr();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    do {
        /* print a map */
        for (int  i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                map[i][j] = '#';
                mvaddch(i, j, '#');
            }
        }
        for (int  i = 1; i < ROWS - 1; ++i) {
            for (int j = 1; j < COLS - 1; ++j) {
                map[i][j] = ' ';
                mvaddch(i, j, ' ');
            }
        }

        map[ay][ax] = bone;
        if (c == KEY_UP && map[y-1][x] != '#') y--;
        if (c == KEY_DOWN && map[y+1][x] != '#') y++;
        if (c == KEY_LEFT && map[y][x-1] != '#') x--;
        if (c == KEY_RIGHT && map[y][x+1] != '#') x++;

        /* if the dog eats a bone */
        if ((y == ay) && (x == ax)) {
            ay = (rand() % (ROWS-2)) + 1;
            ax = (rand() % (COLS-2)) + 1;
            ++score;
        }

        mvaddch(ay, ax, bone);
        mvaddch(y, x, dog);
	mvprintw(ROWS, 0, "move - arrows, exit - F1");
        mvprintw(ROWS + 2, 0, "Score: %d", score);
    } while ((c = getch()) != KEY_F(1));
    endwin();
	
    return 0;
}
