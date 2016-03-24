#include <cassert>
#include <algorithm>
#include "Snake.h"
#include "Point.h"

void Snake::move(WINDOW* window)
{
    if (dead()) {
        return;
    }

    Point bounds = bottomRight(window);

    int theLength = length();
    Point::Direction direction;

    for (int i = TAIL_INDEX; i < theLength; i++) {
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

        //TODO, just check if it exists - don't need an iterator.
        int count = std::count_if(_points.begin(), _points.end(), [=](const Point& p) {
            return point.hasEqualCoordinates(p);
        });

        if (count > 2) {
            _dead = true;
        }
    }
}

void Snake::grow(WINDOW* window)
{

    Point newTail = tail();
    Point bounds = bottomRight(window);

    switch (newTail.direction) {
    case Point::Direction::Right:
        newTail.addKeepingWithinRange(0, -1, bounds);
        _points.insert(_points.begin(), newTail);
        break;
    case Point::Direction::Left:
        newTail.addKeepingWithinRange(0, 1, bounds);
        _points.insert(_points.begin(), newTail);
        break;
    case Point::Direction::Up:
        newTail.addKeepingWithinRange(1, 0, bounds);
        _points.insert(_points.begin(), newTail);
        break;
    case Point::Direction::Down:
        newTail.addKeepingWithinRange(-1, 0, bounds);
        _points.insert(_points.begin(), newTail);
        break;
    default:
        assert(false);
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