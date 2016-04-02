#include "Snake.h"
#include "SnakeGame.h"
#include "cmdline.h"

#define SCAST_INT(X) static_cast<int>(X)

void parseArguments(int argc, char** argv, SnakeGame::Speed& speed)
{
    cmdline::parser parser;

    parser.add<int>("speed", 's', "Speed of the snake: Fast = 1, Slow = 5.", false,
        SCAST_INT(SnakeGame::Speed::Moderate),
        cmdline::range(SCAST_INT(SnakeGame::Speed::InsanelyFast), SCAST_INT(SnakeGame::Speed::Slow)));

    parser.parse_check(argc, argv);

    uchar _speed = (uchar) parser.get<int>("speed");
    speed = static_cast<SnakeGame::Speed>(_speed);
}

int main(int argc, char** argv)
{
    SnakeGame::Speed speed;

    parseArguments(argc, argv, speed);

    SnakeGame game{ speed };
    game.run();
}