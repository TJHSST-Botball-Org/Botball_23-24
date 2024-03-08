#include "include/SmallRobot.hpp"
#include <kipr/wombat.hpp>

SmallRobot::SmallRobot(int leftWheelPin, int rightWheelPin) {
    this->leftWheelPin = leftWheelPin;
    this->rightWheelPin = rightWheelPin;
}

void SmallRobot::move(int distance)
{
    /* Moves forward a certain distance in inches, blocking. */

    int leftInitialPos = gmpc(this->leftWheelPin);
    int rightInitialPos = gmpc(this->rightWheelPin);

    int leftDeltaPos =  

    int targetPos = 
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