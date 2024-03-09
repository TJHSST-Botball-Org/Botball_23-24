#include <iostream>
#include <SmallRobot.h>
#include "include/OpMode.hpp"

int main()
{
    SmallRobot robot(0, 3);

    robot.moveContinuous(100);
}