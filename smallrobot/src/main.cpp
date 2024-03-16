#include <iostream>
// #include "include/OpMode.hpp"
#include <SmallRobot.h>

int main()
{
    SmallRobot robot(0, 1, 6.5, 1.375, 1900, 2000);

    // Step 1: Purple
    robot.moveDistanceAndCorrect(16.0, 1000);
    robot.rotateAndCorrect(-285, 1000);
    
    robot.moveDistanceAndCorrect(9.0, 1000);
    robot.rotateAndCorrect(-95.0, 1000);
    
    robot.moveDistanceAndCorrect(22.0, 1000);
    robot.rotateAndCorrect(-90.0, 1000);
    
    robot.moveDistanceAndCorrect(9.0, 1000);
    robot.rotateAndCorrect(90.0, 1000);
    
    robot.moveDistanceAndCorrect(31.0, 1000);
    robot.rotateAndCorrect(-45.0, 750);
    
    robot.moveDistanceAndCorrect(5.0, 1000);
    
    
    
    //robot.rotateAndCorrect(90, 750);
    //robot.turnLeftContinuous(750);
    //robot.turnRightContinious(60);
    
    //msleep(5000);
    
    // robot.moveUntilBlackLine(50);
    //robot.moveDistanceAndCorrect(30, 700);
    //robot.rotateAndCorrectAndCorrect(-45, 700);
    //robot.moveDistanceAndCorrect(12, 700);

    // Step 2 :Yellow
    //robot.moveDistanceAndCorrect(-20, 750);
    //robot.rotateAndCorrect(135, 700);
    //robot.moveDistanceAndCorrect(-25, 25);
    //robot.moveDistanceAndCorrect(17, 750);
    // robot.moveUntilBlackLine(55);
    //robot.rotateAndCorrect(90, 700);

    return 0;
}