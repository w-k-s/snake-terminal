#include "SnakeGame.h"

int main()
{
    SnakeGame game{ 3, SnakeGame::SpeedFactor::Moderate };
    game.run();
}