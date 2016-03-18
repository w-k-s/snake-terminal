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
    bool userDidQuitGame = false;
    Snake snake{ 3, Point{ 0, 0 } };
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
            int y, x;
            getyx(stdscr, y, x);
            Point::Direction direction = Point::Direction::Right;
            switch (inputKey) {
            case KEY_DOWN:
                direction = Point::Direction::Down;
                break;
            case KEY_RIGHT:
                direction = Point::Direction::Right;
                break;
            case KEY_UP:
                direction = Point::Direction::Up;
                break;
            case KEY_LEFT:
                direction = Point::Direction::Left;
                break;
            default:
                //continue in direction
                break;
            }

            snake.changeSnakeHeadDirection(direction);
            snake.move(stdscr);
            snake.draw(stdscr);
        }

        doupdate();
    }

    endwin();
}