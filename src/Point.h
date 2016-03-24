#ifndef POINT_H
#define POINT_H
#include <cassert>
#include <iostream>
#include <string>
#include <sstream> 
#include <stdexcept>

typedef unsigned char UChar;

struct Point {
	
	enum class Direction : char{
        Up = 'U',
        Down = 'D',
        Left = 'L',
        Right = 'R'
    };

    UChar y;
    UChar x;
    Direction direction;
    
    Point(int y, int x, Direction direction=Direction::Right)
        : y{ static_cast<UChar>(y) }
        , x{ static_cast<UChar>(x) }
        , direction{direction}
    {
    }

    Point(UChar y, UChar x, Direction direction=Direction::Right)
    	: y{y}
    	, x{x}
    	, direction{direction}
    {}

    Point pointByAddingPoint(int aY, int anX){
    	int newY = y + aY;
    	int newX = x + anX;

    	if(newX <0 || newX > UCHAR_MAX || newY <0 || newY > UCHAR_MAX){
    		std::ostringstream oss;
    		oss << "Adding y: "<<aY<<", x: "<<anX<<" to "<<*this<<" results in unsigned char overflow";
    		throw std::overflow_error(oss.str());
    	}

    	return Point(newY,newX, direction);
    }

    void addKeepingWithinRange(int aY,int anX,const Point& bottomRight) noexcept{
    	int newY = y + aY;
    	int newX = x + anX;

    	if(newY < 0){
    		newY = bottomRight.y;
    	}else if (newY >= bottomRight.y){
    		newY %= bottomRight.y;	
    	}

    	if(newX < 0){
    		newX = bottomRight.x;
    	}else if(newX >= bottomRight.x){
    		newX %= bottomRight.x;
    	}

    	y = static_cast<UChar>(newY);
    	x = static_cast<UChar>(newX);
    }

    friend inline bool operator==(const Point& lhs, const Point& rhs){ 
        return lhs.y == rhs.y 
        && lhs.x == rhs.x 
        && lhs.direction == rhs.direction;
    }   

    friend inline bool operator!=(const Point& lhs, const Point& rhs){ 
        return !(lhs == rhs); 
    }

    bool hasEqualCoordinates(const Point& point) const noexcept{
    	return x == point.x && y == point.y;
    }

    static Point::Direction reverseDirectionOf(Point::Direction direction){
    	switch(direction){
    		case Direction::Up:
    			return Direction::Down;
    		case Direction::Down:
    			return Direction::Up;
    		case Direction::Left:
    			return Direction::Right;
    		case Direction::Right:
    			return Direction::Left;
    		default:
                assert(false);
    	}
    }

    friend std::ostream& operator<<(std::ostream& os,const Point& point){
    	 os<<"y: "<<static_cast<unsigned>(point.y);
    	 os<<", x: "<<static_cast<unsigned>(point.x);
    	 os<<" ("<<static_cast<char>(point.direction)<<")";
    	 return os;
    }
};

#endif