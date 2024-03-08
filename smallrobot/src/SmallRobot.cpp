#include "include/SmallRobot.hpp"
#include <kipr/wombat.hpp>

SmallRobot::SmallRobot(int leftWheelPin, int rightWheelPin) {
    this->leftWheelPin = leftWheelPin;
    this->rightWheelPin = rightWheelPin;
}

void SmallRobot::moveAndCorrect(int distance, bool condition=true)
{
    /* 
    Moves forward a certain distance in inches while trying to keep straight, blocking. Clears the pos counter. 
    Will block while distance is not reached AND condition is true.
    */

    /* PSEUDOCODE
    1. Clear counters of both motors
    2. Calculate target counter pos based on distance and wheel radius
    3. Full power both motors
    4. While both motors are not at target counter:
    5.      If one motor counter is ahead of the other, freeze that motor a bit.
            I'm thinking this would probably allow the robot to correct itself if
            one motor is more powerful than the other.
    6. If either motor's pos is beyond the target, stop both motors.
    */

    // 1. Clear counters
    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);

    // 2. Calc target counter pos
    const int targetPos = 

    // 3. Full power both motors
    fd(this->leftWheelPin);
    fd(this->rightWheelPin);

    // 4. while loop
    int leftWheelPos = gmpc(this->leftWheelPin);
    int rightWheelPos = gmpc(this->rightWheelPin);
    while ( leftWheelPos <= targetPos && rightWheelPos <= targetPos && condition)
    {
        // 5. If one motor is more ahead than the other, stop that motor for a bit
        if (leftWheelPos > rightWheelPos)
        {
            freeze(this->leftWheelPin);
            fd(this->rightWheelPin);
        }
        else if (leftWheelPos < rightWheelPos)
        {
            fd(this->leftWheelPin);
            freeze(this->rightWheelPin);
        }
        else
        {
            fd(this->leftWheelPin);
            fd(this->rightWheelPin);
        }

        leftWheelPos = gmpc(this->leftWheelPin);
        rightWheelPos = gmpc(this->rightWheelPin);
    }

    // 6. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::moveForward()
{

}

void SmallRobot::moveBackward()
{

}

void SmallRobot::stopMove()
{

}

void SmallRobot::rotate(int degrees)
{

}

void SmallRobot::turnLeft()
{

}

void SmallRobot::turnRight()
{

}

void SmallRobot::stopTurn()
{

}