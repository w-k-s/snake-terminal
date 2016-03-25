#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#include "Point.h"

#define TAIL_INDEX 0

typedef std::vector<Point> PointVector;

class Snake {
public:
    
private:
    PointVector _points;
    PointVector _turns;
    bool _dead;

    Point bottomRight(WINDOW* window);//WRONG: This does not belong in Snake. Move to NCurses Util?

    bool didBiteItself() const{

        //check if there is a point after the head that is at the same location as head
        //head is at _points.end();
        
        int count = std::count_if(_points.begin(), --_points.end(), [=](const Point& p) {
            return head().hasEqualCoordinates(p);
        });

        return count == 1;
    }

public:
    Snake(UChar length, const Point& tail)
    {
        _points.push_back(tail);
        for(int i= TAIL_INDEX ;i<length - 1; i++){
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

    void changeHeadDirection(Point::Direction direction);
    void move(WINDOW * window);
    void draw(WINDOW * window) const;
    void grow(WINDOW * window);

    friend std::ostream& operator<<(std::ostream& os,const Snake& snake){
         os<<"Points:"<<std::endl;
         for(Point point : snake._points){
            os<<"\t"<<point<<std::endl;
         }
         os<<"Turns:"<<std::endl;;
         for(Point point : snake._turns){
            os<<"\t"<<point<<std::endl;
         }
         os<<"Dead:"<<snake._dead<<std::endl;
         return os;
    }

    bool occupies(const Point& point) const{

        auto it = std::find_if(_points.begin(),_points.end(),[=](const Point& p){
            return point.hasEqualCoordinates(p);
        });

        return it != _points.end();
    }
    
    Point head() const { return _points[length() - 1]; }
    Point tail() const { return _points[0]; }
    
    int length() const { return _points.size(); }

    bool dead() const { return _dead; }

};


#endif