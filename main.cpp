#include <curses.h>
#include <iostream>
#include "Point.h"
#include "Snake.h"

int main()
{
    initscr();
    cbreak(); // disable character buffering
    noecho(); // don't print input characters
    keypad(stdscr, TRUE); // let getch() to detecte special keys e.g. up,down
    nodelay(stdscr, TRUE);

    int inputKey;
    bool userDidQuitGame;
    Snake snake{ 4, Point{ 0, 0 } };

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