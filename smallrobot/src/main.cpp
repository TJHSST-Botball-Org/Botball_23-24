#include <iostream>
// #include "include/OpMode.hpp"
#include <SmallRobot.h>

int main()
{

    //Step 1: Purple
    robot.moveDistance(4,50);
    robot.rotate(90,50);
    robot.turnLeftContinuous(50);
    robot.turnRightContinious(60);
    msleep(5000);
    robot.moveUntilBlackLine(50):
    robot.moveDistance(30,45);
    robot.rotate(-45,45);
    robot.moveDistance(12,45);

    //Step 2 :Yellow
    robot.moveDistance(-20,50);
    robot.rotate(135,45);
    robot.moveDistance(-25,25);
    robot.moveDistance(17,50);
    robot.moveUntilBlackLine(55);
    robot.rotate(90,45);

    return 0;
}