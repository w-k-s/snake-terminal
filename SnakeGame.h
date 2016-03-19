#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

#include "Snake.h"
#include "Point.h"

class SnakeGame{
private:
	Snake _snake;
	bool _quit;
public:
	SnakeGame():_snake{ 10, Point{ 0, 0 } }{
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