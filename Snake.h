#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#include "Point.h"

typedef std::vector<Point> PointVector;

class Snake {
public:
    
private:
    int _length;
    PointVector _points;
    PointVector _turns;

public:
    Snake(int length, const Point& tail)
        :_length{length}
    {
        _points.push_back(tail);
        for(int i=0;i<_length - 1; i++){
            Point& lastPoint = _points[i];
            switch(tail.direction){
                case Point::Direction::Right:
                    _points.push_back(lastPoint.pointByAddingPoint(0,1));
                    break;
                case Point::Direction::Left:
                    _points.push_back(lastPoint.pointByAddingPoint(0,-1));
                    break;
                case Point::Direction::Up:
                    _points.push_back(lastPoint.pointByAddingPoint(-1,0));
                    break;
                case Point::Direction::Down:
                    _points.push_back(lastPoint.pointByAddingPoint(1,0));
                    break;
            }
        }
    };

    void changeSnakeHeadDirection(Point::Direction direction);
    void move(WINDOW * window);
    void draw(WINDOW * window) const;
    Point head() const;
    int length() const;

    friend std::ostream& operator<<(std::ostream& os,const Snake& snake){
         os<<"Points:"<<std::endl;
         for(Point point : snake._points){
            os<<"\t"<<point<<std::endl;
         }
         os<<"Turns:"<<std::endl;;
         for(Point point : snake._turns){
            os<<"\t"<<point<<std::endl;
         }
         return os;
    }
};


#endif