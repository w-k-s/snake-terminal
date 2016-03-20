#include "SnakeGame.h"

void SnakeGame::run()
{
    int inputKey;
    move(0, 0);
    while (!_quit) {
        inputKey = getch();
        napms(100);
        erase();
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