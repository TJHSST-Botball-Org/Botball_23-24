#include <iostream>
// #include "include/OpMode.hpp"
#include <SmallRobot.h>

int main()
{
    // Easy Robot Route (All Items on board, Optional: Return to Starting box at the end )
    SmallRobot robot(0, 1, 6, 2);

    robot.moveDistanceAndCorrect(6, 750);

    return 0;
}