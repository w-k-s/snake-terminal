#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>
#include "Point.h"

class Snake {
private:
    int length;
    Point tail;

public:
    Snake(int length, Point tail)
        : length{ length }
        , tail{ tail }
    {
    }

    void move(WINDOW * window);
    void draw(WINDOW * window);
};


#endif