#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include "Point.h"

class PointTestSuite : public CxxTest::TestSuite
{
public:

    void testPointByAddingPointSuccess(void)
    {
        Point p1{2,2};
        Point p2{3,5};
        Point sum{5,7};

        TS_ASSERT_EQUALS(p1.pointByAddingPoint(p2.y,p2.x), sum);
    }

    void testPointByAddingPointUnderflow(void){

        Point p1{2,2};

        TS_ASSERT_THROWS(p1.pointByAddingPoint(-5,-5),std::overflow_error);
    }

    void testPointByAddingPointOverflow(void){
        Point p1{254,254};
        
        TS_ASSERT_THROWS(p1.pointByAddingPoint(2,2),std::overflow_error);
    }

    void testAddKeepingWithinRangeOverflow(void){
        
        Point p1{98,98};
        Point bottomRight{100,100};
        p1.addKeepingWithinRange(3,3,bottomRight);

        TS_ASSERT_EQUALS(p1.y,1);
        TS_ASSERT_EQUALS(p1.x,1);
    }

    void testAddKeepingWithinRangeUnderflow(void){

        Point p1{3,3};
        Point bottomRight{100,100};

        p1.addKeepingWithinRange(-4,-4,bottomRight);

        TS_ASSERT_EQUALS(p1.y,100);//negative points should appear at edge
        TS_ASSERT_EQUALS(p1.x,100);
    }

    void testHasEqualCoordinatesWhenTrue(void){
        Point p1{2,2};
        Point p2{2,2};

        TS_ASSERT_EQUALS(p1.hasEqualCoordinates(p2),true);
    }

    void testHasEqualCoordinatesWhenFalse(void){
        Point p1{2,2};
        Point p2{3,3};

        TS_ASSERT_EQUALS(p1.hasEqualCoordinates(p2),false);
    }

    void testReverseDirection(void){

        TS_ASSERT_EQUALS(Point::reverseDirectionOf(Point::Direction::Left),Point::Direction::Right);
        TS_ASSERT_EQUALS(Point::reverseDirectionOf(Point::Direction::Right),Point::Direction::Left);
        TS_ASSERT_EQUALS(Point::reverseDirectionOf(Point::Direction::Up),Point::Direction::Down);
        TS_ASSERT_EQUALS(Point::reverseDirectionOf(Point::Direction::Down),Point::Direction::Up);
    }
};