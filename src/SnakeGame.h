#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <sstream>

#include "Snake.h"
#include "Point.h"

#define NAP_FACTOR 25

class SnakeGame{

private:
	Snake _snake;
	Point _fruitPoint;
	uchar _score = 0;
	uchar _scoreIncrement = 0;
	int _napTime = 0;
	//std::ostringstream _debug;

	void drawFruit() const;
	Point randomFruitPoint(WINDOW * window) ;
	bool fruitHasBeenEaten() const;

public:
	enum class SpeedFactor: uchar{
		InsanelyFast = 1,
		VeryFast = 2,
		Fast = 3,
		Moderate = 4,
		Slow = 5,
	};

	SnakeGame(uchar snakeLength,SpeedFactor speedFactor):_snake{ snakeLength, Point{ 0, 0 } },_fruitPoint{0,0}{
		
		uchar uSpeedFactor = static_cast<uchar>(speedFactor);
		_scoreIncrement = static_cast<uchar>(SpeedFactor::InsanelyFast) - uSpeedFactor + 1;
		_napTime = NAP_FACTOR * uSpeedFactor;

		initscr();
	    cbreak(); // disable character buffering
	    noecho(); // don't print input keys
	    keypad(stdscr, TRUE); // let getch() return special keys e.g. up,down
	    nodelay(stdscr, TRUE);
	}

	~SnakeGame(){
		endwin();
		std::cout<<"Increment: "<<static_cast<unsigned>(_scoreIncrement)<<","<<" Score: "<<static_cast<unsigned>(_score)<<std::endl;
	}

	void run();
	void incrementScore(){
		_score += _scoreIncrement;
	}
};

#endif