#include "SnakeGame.h"
#include <random>

void SnakeGame::run()
{
    int inputKey;
    _fruitPoint = randomFruitPoint();

    move(0, 0);
    while (!_quit) {
        inputKey = getch();
        napms(100);
        erase();

        if (fruitHasBeenEaten()) {
            _snake.grow(stdscr);
            _fruitPoint = randomFruitPoint();
            ++_score;
        }

        drawFruit();

        if ((inputKey = getch()) == ERR) {
            _snake.move(stdscr);
            _snake.draw(stdscr);
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
            case 'q':
                _quit = true;
                break;

            default:
                //continue in direction
                break;
            }

            _snake.changeSnakeHeadDirection(direction);
            _snake.move(stdscr);
            _snake.draw(stdscr);
        }

        doupdate();
    }
}

void SnakeGame::drawFruit() const
{
    move(_fruitPoint.y, _fruitPoint.x);
    addch('$');
}

/**
*@return true if Snake's head is at the position of the fruit.
*
*/
bool SnakeGame::fruitHasBeenEaten() const
{
    return _snake.head().hasEqualCoordinates(_fruitPoint);
}

Point&& SnakeGame::randomFruitPoint() const
{
    int y, x;
    getmaxyx(stdscr, y, x);

    std::random_device rd;
    std::mt19937 mt(rd());
    Point p{ 0, 0 };
    do {
        std::uniform_int_distribution<> distY{ 0, y };
        std::uniform_int_distribution<> distX{ 0, x };

        p = { distY(mt), distX(mt) };
    } while (_snake.occupies(p));

    return std::move(p);
}