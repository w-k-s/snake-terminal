#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <sstream>

#include "Snake.h"
#include "Point.h"

#define NAP_FACTOR 25
#define INITIAL_SNAKE_LENGTH 3

class SnakeGame {

private:
    Snake _snake;
    Point _fruitPoint;
    uchar _score = 0;
    uchar _scoreIncrement = 0;
    int _napTime = 0;
    WINDOW* gameWindow;
    WINDOW* scoreWindow;
    std::ostringstream _debug;

    void drawFruit() const;
    Point randomFruitPoint(WINDOW* window);
    bool fruitHasBeenEaten() const;

public:
    enum class Speed : uchar {
        InsanelyFast = 1,
        VeryFast = 2,
        Fast = 3,
        Moderate = 4,
        Slow = 5,
    };

    SnakeGame(Speed speed)
        : _snake{ INITIAL_SNAKE_LENGTH, Point{ 0, 0 } }
        , _fruitPoint{ 0, 0 }
    {

        uchar uSpeed = static_cast<uchar>(speed);
        _scoreIncrement = static_cast<uchar>(Speed::Slow) - uSpeed + 1;
        _napTime = NAP_FACTOR * uSpeed;

        initscr();
        initWindows();
        cbreak(); // disable character buffering
        noecho(); // don't print input keys
        keypad(stdscr, TRUE); // let getch() return special keys e.g. up,down
        nodelay(stdscr, TRUE);
    }

    ~SnakeGame()
    {
        delwin(scoreWindow);
        delwin(gameWindow);
        endwin();
    }

    void run();
    void drawScoreWindow() const;
    void initWindows();
    void incrementScore()
    {
        _score += _scoreIncrement;
    }
};

#endif