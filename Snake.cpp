#include <cassert>
#include <algorithm>
#include "Snake.h"
#include "Point.h"

void Snake::move(WINDOW* window)
{
    int width, height;
    getmaxyx(window, height, width);
    Point bottomRight{ height, width };

    Point::Direction direction;
    for (int i = 0; i < length(); i++) {
        Point& point = _points[i];

        if (i == 0) {
            direction = point.direction;
        }

        auto it = std::find_if(_turns.begin(), _turns.end(), [=](const Point& p) { return point.hasEqualCoordinates(p); });
        if (it != _turns.end()) {
            direction = it->direction;
        }

        point.direction = direction;
        switch (direction) {
        case Point::Direction::Right:
            point.addKeepingWithinRange(0, 1, bottomRight);
            continue;
        case Point::Direction::Left:
            point.addKeepingWithinRange(0, -1, bottomRight);
            continue;
        case Point::Direction::Up:
            point.addKeepingWithinRange(-1, 0, bottomRight);
            continue;
        case Point::Direction::Down:
            point.addKeepingWithinRange(1, 0, bottomRight);
            continue;
        default:
            continue;
        }
    }
}

void Snake::draw(WINDOW* window) const
{
    for (int i = 0; i < length(); i++) {
        const Point& point = _points[i];
        wmove(window, point.y, point.x);
        waddch(window, '0');
    }
}

void Snake::changeSnakeHeadDirection(Point::Direction direction)
{
    Point headCopy = head();
    headCopy.direction = direction;
    _turns.push_back(headCopy);
}

Point Snake::head() const
{
    return _points[length() - 1];
}

int Snake::length() const
{
    return _points.size();
}