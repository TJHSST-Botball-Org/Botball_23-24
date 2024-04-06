#include <iostream>
// #include "include/OpMode.hpp"
#include <SmallRobot.h>

int main()
{
    SmallRobot robot(0, 1, 6.5, 1.375, 1900, 2000, -1, -1, 1, 0);

    robot.openClaw();
    robot.setArmPosition(0, 10);
    // robot.closeClaw();
    // robot.setArmPosition(2047, 1);

    // Step 1: Purple (Altered)
    /*
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
    */

    // UNCOMMENT THIS PART OUT
    // Step 1 : True Purple
    robot.moveDistanceAndCorrect(6.75, 1000);
    robot.rotateAndCorrect(-20, 1000);
    robot.moveDistanceAndCorrect(16.0, 1000);
    robot.rotateAndCorrect(-120, 1000);
    robot.moveDistanceAndCorrect(8.0, 1000);
    robot.rotateAndCorrect(-120, 1000);
    robot.moveDistanceAndCorrect(8.0, 1000);
    robot.rotateAndCorrect(-25, 400);
    robot.moveDistanceAndCorrect(14.0, 400);

    robot.rotateAndCorrect(-35.0, 400);
    robot.moveDistanceAndCorrect(0.5, 400);
    robot.rotateAndCorrect(-35.0, 400);
    robot.moveDistanceAndCorrect(0.5, 400);
    robot.rotateAndCorrect(-35.0, 400);
    robot.moveDistanceAndCorrect(0.5, 400);
    robot.rotateAndCorrect(-30.0, 400);

    robot.moveDistanceAndCorrect(19, 1000);
    robot.openClaw();
    robot.setArmPosition(2047, 10);
    robot.rotateAndCorrect(35.0, 300);

    robot.moveDistanceAndCorrect(35.0, 800);
    robot.rotateAndCorrect(10.0, 400);
    robot.moveDistanceAndCorrect(1.5, 400);

    robot.rotateAndCorrect(-25.0, 400);
    robot.moveDistanceAndCorrect(0.75, 400);
    robot.rotateAndCorrect(-25.0, 400);
    robot.moveDistanceAndCorrect(0.75, 400);

    robot.moveDistanceAndCorrect(4, 1000);
    robot.moveDistanceAndCorrect(-4, 1000);

    /*
    robot.moveDistanceAndCorrect(9.0, 1000);
    robot.rotateAndCorrect(-125.0, 1000);

    robot.moveDistanceAndCorrect(22, 1000);
    robot.rotateAndCorrect(35.0, 750);

    robot.moveDistanceAndCorrect(25.0, 1000);
    robot.rotateAndCorrect(-45.0, 750);

    robot.moveDistanceAndCorrect(6.5, 1000);
    */

    // robot.rotateAndCorrect(90, 750);
    // robot.turnLeftContinuous(750);
    // robot.turnRightContinious(60);

    // msleep(5000);

    // robot.moveUntilBlackLine(50);
    // robot.moveDistanceAndCorrect(30, 700);
    // robot.rotateAndCorrectAndCorrect(-45, 700);
    // robot.moveDistanceAndCorrect(12, 700);

    // Step 2 :Yellow
    // robot.moveDistanceAndCorrect(-20, 750);
    // robot.rotateAndCorrect(135, 700);
    // robot.moveDistanceAndCorrect(-25, 25);
    // robot.moveDistanceAndCorrect(17, 750);
    // robot.moveUntilBlackLine(55);
    // robot.rotateAndCorrect(90, 700);

    disable_servos();

    return 0;
}