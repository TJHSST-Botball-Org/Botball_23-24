#include <iostream>
// #include "include/OpMode.hpp"
#include <SmallRobot.h>

int main()
{
    SmallRobot robot(0, 1, 6.5, 1.375, 1900, 2000, -1, -1, 1, 0);

    // Move it out of the starting box
    robot.moveDistanceAndCorrect(-20.0, 1300);

    // Move the claw up
    robot.openClaw();
    robot.setArmPosition(0, 6);

    // Rotate towards the moonbase
    robot.rotateAndCorrect(-56, 400);

    // Move towards the moonbase
    robot.moveDistanceAndCorrect(-12.75, 750);

    // Lower the claw
    robot.setArmPosition(340, 5);

    // Grab the cube
    robot.closeClaw();

    // Lift the cube up
    robot.setArmPosition(0, 5);

    // Go forward
    robot.moveDistanceAndCorrect(2, 300);

    // Turn Right
    robot.rotateAndCorrect(20.0, 750);

    // Go Forward
    robot.moveDistanceAndCorrect(10, 800);

    // Face away from the moonbase, get the rock
    robot.rotateAndCorrect(-45.0, 750);

    // GO forward and collect first rock in plow
    robot.moveDistanceAndCorrect(5, 800);

    // Turn left a bit to go south
    robot.rotateAndCorrect(-11.0, 650);

    // Go forward and collect first rock in plow
    robot.moveDistanceAndCorrect(15, 800);

    // Do a 180 degree turn counter clockwise without hitting the roomba and while keeping the rock
    robot.rotateAndCorrect(-160.0, 650);

    // Go forward and collect 4 pom poms
    robot.moveDistanceAndCorrect(4, 800);

    // Turn right toward the other pom poms
    robot.rotateAndCorrect(30.0, 650);

    // Go forward and collect 4 more pom poms
    robot.moveDistanceAndCorrect(8.5, 800);

    // Turn left to turn toward 2nd rock
    robot.rotateAndCorrect(-35.0, 650);

    // Go forward
    robot.moveDistanceAndCorrect(5, 800);

    // Lower Arm to lower cube to lower center of gravity to lower shakyness
    robot.setArmPosition(1000, 3);

    // move forward
    robot.moveDistanceAndCorrect(4, 800);

    // Do a slow turn right to keep the pom poms

    // Do a small turn right
    robot.rotateAndCorrect(20.0, 450);
    // Go forward a little
    robot.moveDistanceAndCorrect(1.5, 200);
    // Do a small turn right
    robot.rotateAndCorrect(25.0, 450);
    // Go forward a little
    robot.moveDistanceAndCorrect(1.5, 200);
    // Turn right to align with black line
    robot.rotateAndCorrect(40.0, 450);

    // Go forward and collect 3rd rock and 3 orange pom poms
    robot.moveDistanceAndCorrect(39, 800);

    // Turn left to move everything into scrapyard
    robot.rotateAndCorrect(-50.0, 650);

    // Go forward and place everything in scrapyard
    robot.moveDistanceAndCorrect(7, 800);

    // Go backward out of scrapyard to release everything in the scrapyard
    robot.moveDistanceAndCorrect(-9, 800);

    // Do a 180 degree turn to get into position to drop the yellow cube in the scrapyard
    robot.rotateAndCorrect(-210.0, 650);

    // Move back a little to avoid dropping the cube on the rocks and stuff
    robot.moveDistanceAndCorrect(-2, 800);

    // Open the hand to release the cube
    robot.openClaw();

    // reset hand and arm to start position
    //
    //

    // Speed up the code next

    disable_servos();

    return 0;
}