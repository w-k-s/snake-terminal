#include "Snake.h"

void Snake::move(WINDOW* window)
{
    int width, height;
    getmaxyx(window, height, width);

    switch (direction) {
    case Right:
        ++head.x;
        break;

    default:
        break;
    }
}

void Snake::draw(WINDOW* window)
{

    int width, height;
    getmaxyx(window, height, width);

    for (int i = 0; i < length; ++i) {
        switch (direction) {
        case Right: {
            int x = head.x - i;
            int y = head.y;

            if (x >= width) {
                x %= width;
            }

            wmove(window, y, x);
            waddch(window, '0');
            break;
        }
        default:
            break;
        }
    }
}

void Snake::changeDirectionAtPoint(Direction direction, const Point& point)
{
}