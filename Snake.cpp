#include "Snake.h"

void Snake::move(WINDOW* window)
{
    int width, height;
    getmaxyx(window, height, width);

    ++tail.x;
    if (tail.x >= width) {
        tail.x = 0;
    }
}

void Snake::draw(WINDOW* window)
{
    wmove(window, tail.y, tail.x);

    int width, height;
    getmaxyx(window, height, width);

    for (int i = 0; i < length; ++i) {

        int cursorX, cursorY;
        getyx(window, cursorY, cursorX);

        if (cursorX <= width) {
            waddch(window, '0');
        }
    }
}