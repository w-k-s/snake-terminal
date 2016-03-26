#include "SnakeGame.h"
#include <random>

void SnakeGame::run()
{
    bool quit = false;
    int inputKey;
    _fruitPoint = randomFruitPoint(stdscr);

    move(0, 0);
    while (!quit) {
        inputKey = getch();
        napms(_napTime);
        erase();

        if (fruitHasBeenEaten()) {
            incrementScore();
            _snake.grow(stdscr);
            _fruitPoint = randomFruitPoint(stdscr);
        }

        drawFruit();

        if ((inputKey = getch()) == ERR) {
            _snake.move(stdscr);
            _snake.draw(stdscr);
        }
        else {

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
                quit = true;
                break;

            default:
                // continue in direction
                break;
            }

            _snake.changeDirection(direction);
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

bool SnakeGame::fruitHasBeenEaten() const
{
    return _snake.head().hasEqualCoordinates(_fruitPoint);
}

Point SnakeGame::randomFruitPoint(WINDOW* window)
{
    int y, x;
    getmaxyx(window, y, x);

    std::random_device rd;
    std::mt19937 mt(rd());
    Point p{ 0, 0 };

    do {
        // height width of window returned by getmaxyx is:
        // 0 <= y < height;
        // 0 <= x < width;
        std::uniform_int_distribution<> distY{ 0, y - 1 };
        std::uniform_int_distribution<> distX{ 0, x - 1 };

        p = { distY(mt), distX(mt) };

    } while (_snake.occupies(p));

    return p;
}