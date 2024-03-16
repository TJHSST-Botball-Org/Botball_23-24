#include <iostream>
// #include "include/OpMode.hpp"
#include <SmallRobot.h>

int main()
{
    // Easy Robot Route (All Items on board, Optional: Return to Starting box at the end )
    SmallRobot robot(0, 1, 6.5, 1.375, 1900, 2000);

    robot.rotateAndCorrect((360.0 / 336.0) * 360.0, 750); // 360/336 * wanted degrees

    return 0;
}