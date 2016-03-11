#include <curses.h>
#include <iostream>
#include "Point.h"
#include "Snake.h"

int main()
{
    initscr();
    cbreak(); // disable character buffering
    noecho(); // don't print input keys
    keypad(stdscr, TRUE); // let getch() return special keys e.g. up,down
    nodelay(stdscr, TRUE);

    int inputKey;
    bool userDidQuitGame;
    Snake snake{ 4, Point{ 3, 0 } };
    move(0, 0);
    while (!userDidQuitGame) {
        inputKey = getch();

        napms(100);
        erase();
        if ((inputKey = getch()) == ERR) {
            snake.move(stdscr);
            snake.draw(stdscr);
        }
        else {
            snake.move(stdscr);
            snake.draw(stdscr);
        }

        doupdate();
    }

    endwin();
}