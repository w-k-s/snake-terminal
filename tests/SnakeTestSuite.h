#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include "Snake.h"

class SnakeTestSuite : public CxxTest::TestSuite
{
public:

    void testSnakeOccupies(void){
        Snake snake{10,{10,10}};
        
        TS_ASSERT_EQUALS(snake.occupies({10,13}),true);
        TS_ASSERT_EQUALS(snake.occupies({11,13}),false);
    }

    void testSnakeHeadTail(){
        Snake snake{10,{0,0}};
        Point expectedHead{0,9,Point::Direction::Right};
        Point expectedTail{0,0,Point::Direction::Right};

        TS_ASSERT_EQUALS(snake.head(),expectedHead);
        TS_ASSERT_EQUALS(snake.tail(),expectedTail);
    }
};