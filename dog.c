#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 10
#define COLS 21

int main() {
	srand(time(0));
    char a = '@', bone = 'I';
    int c;
    int y = 5, x = 10; /* dog position */
    int ay = (rand() % 8) + 1, ax = (rand() % 18) + 1; /* bone position */
    int score = 0;
    char map[ROWS][COLS];

    initscr();
    keypad(stdscr, 1);
    noecho();
    curs_set(false);

    do {
        srand(time(0)); /* for random */
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
            ay = (rand() % 8) + 1;
            ax = (rand() % 18) + 1;
            ++score;
        }

        mvaddch(ay, ax, bone);
        mvaddch(y, x, a);
        mvprintw(ROWS + 1, 0, "Score: %d", score);
        mvprintw(ROWS + 2, 0, "move - arrows, exit - F1");
    } while ((c = getch()) != KEY_F(1)); /* escape */
    endwin();
    return 0;
}
