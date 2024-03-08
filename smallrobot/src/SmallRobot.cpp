#include "include/SmallRobot.hpp"
#include <kipr/wombat.hpp>
#include <cmath>

SmallRobot::SmallRobot(int leftWheelPin, int rightWheelPin) {
    this->leftWheelPin = leftWheelPin;
    this->rightWheelPin = rightWheelPin;

    this->posPerOneCm = 1500 / (2.0*3.14159265358979323846*this->wheelRadius);
}

void SmallRobot::moveDistanceAndCorrect(int distance, int percentPower, bool condition=true)
{
    /* 
    Moves forward a certain distance in inches while trying to keep straight, blocking. Clears the pos counter. 
    Will block while distance is not reached AND condition is true.

    distance: distance in inches, negative to go backwards
    percentPower: number between 0 and 100, the power percent to use
    */

    /* PSEUDOCODE
    1. Clear counters, change percentPower
    2. Calculate target counter pos based on distance and wheel radius
    3. Full power both motors
    4. While both motors are not at target counter:
    5.      If one motor counter is ahead of the other, freeze that motor a bit.
            I'm thinking this would probably allow the robot to correct itself if
            one motor is more powerful than the other.
    6. If either motor's pos is beyond the target, stop both motors.
    */

    // 1. Clear counters, change percentPower
    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);

    if (distance < 0)
    {
        percentPower *= -1;
        distance *= -1;
    }

    // FROM HERE ON FORWARDS distance WILL BE POSITIVE, AND percentPower IS IN THE CORRECT DIRECTION

    // 2. Calc target counter pos
    const int targetPos = distance * this->posPerOneCm;

    // 3. Power both motors
    motor_power(this->leftWheelPin, percentPower);
    motor_power(this->rightWheelPin, percentPower);

    // 4. while loop
    int leftWheelPos = std::abs(gmpc(this->leftWheelPin));
    int rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    while ( leftWheelPos <= targetPos && rightWheelPos <= targetPos && condition)
    {
        // 5. If one motor is more ahead than the other, stop that motor for a bit

        // Using freeze because docs say it has brake??? Not exactly sure but it would work regardless
        if (leftWheelPos > rightWheelPos)
        {
            freeze(this->leftWheelPin);
            motor_power(this->rightWheelPin, percentPower);
        }
        else if (leftWheelPos < rightWheelPos)
        {
            motor_power(this->leftWheelPin, percentPower);
            freeze(this->rightWheelPin);
        }
        else
        {
            motor_power(this->leftWheelPin, percentPower);
            motor_power(this->rightWheelPin, percentPower);
        }

        leftWheelPos = std::abs(gmpc(this->leftWheelPin));
        rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    }

    // 6. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::moveDistance(int distance, int percentPower, bool condition=true)
{
    // 1. Clear counters
    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);

    if (distance < 0)
    {
        percentPower *= -1;
        distance *= -1;
    }

    // FROM HERE ON FORWARDS distance WILL BE POSITIVE, AND percentPower IS IN THE CORRECT DIRECTION


    // 2. Calc target counter pos
    const int targetPos = distance * this->posPerOneCm;

    // 3. Power both motors
    motor_power(this->leftWheelPin, percentPower);
    motor_power(this->rightWheelPin, percentPower);

    // 4. while loop
    int leftWheelPos = std::abs(gmpc(this->leftWheelPin));
    int rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    while ( leftWheelPos <= targetPos && rightWheelPos <= targetPos && condition)
    {
        leftWheelPos = std::abs(gmpc(this->leftWheelPin));
        rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    }

    // 5. If either motor's pos is beyond the target, stop both motors.
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