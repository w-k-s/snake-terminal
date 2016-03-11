#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>
#include "Point.h"

class Snake {
	enum Direction{
		Up,
		Down,
		Left,
		Right
	};
private:
    int length;
    Point head;
    Direction direction;

public:
    Snake(int length, Point head, Direction direction = Direction::Right)
        : length{ length }
        , head{ head }
        , direction{ direction }
    {
    }

    void changeDirectionAtPoint(Direction direction, const Point& point);
    void move(WINDOW * window);
    void draw(WINDOW * window);
};


#endif