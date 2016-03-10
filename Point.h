#ifndef POINT_H
#define POINT_H

struct Point {
    int x;
    int y;
    Point(int x, int y)
        : x{ x }
        , y{ y }
    {
    }
};

#endif