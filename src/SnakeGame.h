#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

#include "Snake.h"
#include "Point.h"

class SnakeGame{
private:
	Snake _snake;
	Point _fruitPoint;
	bool _quit;
	int _score;

	void drawFruit() const;
	Point&& randomFruitPoint() const;
	bool fruitHasBeenEaten() const;

public:
	SnakeGame():_snake{ 3, Point{ 0, 0 } },_fruitPoint{0,0}{
		initscr();
	    cbreak(); // disable character buffering
	    noecho(); // don't print input keys
	    keypad(stdscr, TRUE); // let getch() return special keys e.g. up,down
	    nodelay(stdscr, TRUE);
	}

	~SnakeGame(){
		endwin();
	}

	void run();
};

#endif