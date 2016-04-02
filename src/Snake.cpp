#include <cassert>
#include <algorithm>
#include "Snake.h"
#include "Point.h"

const uchar Snake::MinLength = 3;
const uchar Snake::MaxLength = 100;

void Snake::move(WINDOW* window)
{
    if (dead()) {
        return;
    }

    Point bounds = bottomRight(window);
    Point::Direction newDirection;

    for (int i = TAIL_INDEX; i < length(); i++) {
        Point& point = _points[i];

        if (i == TAIL_INDEX) {
            newDirection = point.direction;
        }

        // if current point is a turn point, update value of newDirection.
        auto it = std::find_if(_turns.begin(), _turns.end(), [=](const Point& p) {
            return point.hasEqualCoordinates(p);
        });

        if (it != _turns.end()) {
            newDirection = it->direction;

            // Remove turning point when last segment of snake has passed through it
            if (i == TAIL_INDEX) {
                _turns.erase(it);
            }
        }

        point.direction = newDirection;
        switch (point.direction) {
        case Point::Direction::Right:
            point.addKeepingWithinRange(0, 1, bounds);
            break;
        case Point::Direction::Left:
            point.addKeepingWithinRange(0, -1, bounds);
            break;
        case Point::Direction::Up:
            point.addKeepingWithinRange(-1, 0, bounds);
            break;
        case Point::Direction::Down:
            point.addKeepingWithinRange(1, 0, bounds);
            break;
        default:
            assert(false);
            break;
        }
    }

    if (didBiteItself()) {
        _dead = true;
    }
}

void Snake::grow(WINDOW* window)
{
    if (length() == MaxLength) {
        // continue playing game with snake at max length.
        return;
    }

    Point newTail = tail();
    Point bounds = bottomRight(window);

    switch (newTail.direction) {
    case Point::Direction::Right:
        newTail.addKeepingWithinRange(0, -1, bounds);
        break;
    case Point::Direction::Left:
        newTail.addKeepingWithinRange(0, 1, bounds);
        break;
    case Point::Direction::Up:
        newTail.addKeepingWithinRange(1, 0, bounds);
        break;
    case Point::Direction::Down:
        newTail.addKeepingWithinRange(-1, 0, bounds);
        break;
    default:
        assert(false);
    }

    _points.insert(_points.begin(), newTail);
}

void Snake::draw(WINDOW* window) const
{
    for (int i = TAIL_INDEX; i < length(); i++) {
        const Point& point = _points[i];
        wmove(window, point.y, point.x);
        waddch(window, '0');
    }
}

void Snake::changeDirection(Point::Direction direction)
{
    Point theHead = head();

    if (direction != Point::reverseDirectionOf(theHead.direction)) {
        theHead.direction = direction;
        _turns.push_back(theHead);
    }
}

Point Snake::bottomRight(WINDOW* window)
{
    int width, height;
    getmaxyx(window, height, width);
    return { height, width };
}