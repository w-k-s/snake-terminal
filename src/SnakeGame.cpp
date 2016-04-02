#include "SnakeGame.h"
#include <random>

#define LINES_SCORE_WINDOW 3

void SnakeGame::initWindows()
{
    int y, x;
    getmaxyx(stdscr, y, x);

    scoreWindow = newwin(LINES_SCORE_WINDOW, x, 0, 0);
    gameWindow = newwin(y - LINES_SCORE_WINDOW, x, LINES_SCORE_WINDOW, 0);
}

void SnakeGame::run()
{
    bool quit = false;
    int inputKey;
    _fruitPoint = randomFruitPoint(gameWindow);

    wmove(gameWindow, 0, 0);
    while (!quit) {
        inputKey = getch();
        napms(_napTime);
        wclear(gameWindow);

        if (fruitHasBeenEaten()) {
            incrementScore();
            _snake.grow(gameWindow);
            _fruitPoint = randomFruitPoint(gameWindow);
        }

        drawFruit();
        drawScoreWindow();

        if ((inputKey = getch()) == ERR) {
            _snake.move(gameWindow);
            _snake.draw(gameWindow);
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
            _snake.move(gameWindow);
            _snake.draw(gameWindow);
        }

        wrefresh(scoreWindow);
        wrefresh(gameWindow);
    }
}

void SnakeGame::drawFruit() const
{
    wmove(gameWindow, _fruitPoint.y, _fruitPoint.x);
    waddch(gameWindow, '$');
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

void SnakeGame::drawScoreWindow() const
{
    int y, x;
    getmaxyx(scoreWindow, y, x);

    std::ostringstream oss;

    if (_snake.dead()) {
        oss << "GAME OVER. ";
    }

    oss << "Score: " << static_cast<int>(_score);

    mvwprintw(scoreWindow, 0, 0, oss.str().c_str());

    std::string line;
    line.assign(x, '-');

    mvwprintw(scoreWindow, LINES_SCORE_WINDOW - 1, 0, line.c_str());
}