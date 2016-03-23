#include <cassert>
#include <algorithm>
#include "Snake.h"
#include "Point.h"

void Snake::move(WINDOW* window)
{
    if (dead()) {
        return;
    }

    int width, height;
    getmaxyx(window, height, width);
    Point bottomRight{ height, width };

    int len = length();
    Point::Direction direction;

    for (int i = TAIL_INDEX; i < len; i++) {
        Point& point = _points[i];

        if (i == TAIL_INDEX) {
            direction = point.direction;
        }

        auto it = std::find_if(_turns.begin(), _turns.end(), [=](const Point& p) {
            return point.hasEqualCoordinates(p);
        });

        if (it != _turns.end()) {
            direction = it->direction;

            //Remove turning point when last segment of snake has passed through it
            if (i == TAIL_INDEX) {
                _turns.erase(it);
            }
        }

        point.direction = direction;
        switch (direction) {
        case Point::Direction::Right:
            point.addKeepingWithinRange(0, 1, bottomRight);
            break;
        case Point::Direction::Left:
            point.addKeepingWithinRange(0, -1, bottomRight);
            break;
        case Point::Direction::Up:
            point.addKeepingWithinRange(-1, 0, bottomRight);
            break;
        case Point::Direction::Down:
            point.addKeepingWithinRange(1, 0, bottomRight);
            break;
        default:
            break;
        }

        //TODO, just check if it exists - don't need an iterator.
        int count = std::count_if(_points.begin(), _points.end(), [=](const Point& p) {
            return point.hasEqualCoordinates(p);
        });

        if (count > 2) {
            _dead = true;
        }
    }
}

void Snake::draw(WINDOW* window) const
{
    for (int i = TAIL_INDEX; i < length(); i++) {
        const Point& point = _points[i];
        wmove(window, point.y, point.x);
        waddch(window, '0');
    }
}

void Snake::changeSnakeHeadDirection(Point::Direction direction)
{
    Point headCopy = head();

    if (direction != Point::reverseDirectionOf(headCopy.direction)) {
        headCopy.direction = direction;
        _turns.push_back(headCopy);
    }
}