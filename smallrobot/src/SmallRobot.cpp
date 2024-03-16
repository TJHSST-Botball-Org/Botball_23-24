#include "../include/SmallRobot.h"
#include <kipr/wombat.h>
#include <cmath>

SmallRobot::SmallRobot(int leftWheelPin, int rightWheelPin, int wheelDistance, int wheelRadius)
{
    this->leftWheelPin = leftWheelPin;
    this->rightWheelPin = rightWheelPin;
    this->wheelDistance = wheelDistance;
    this->wheelRadius = wheelRadius;

    this->posPerOneInch = 1500 / (2.0 * 3.14159265358979323846 * this->wheelRadius);
}

void SmallRobot::moveDistanceAndCorrect(int distance, int ticksPerSecond, bool condition)
{
    /*
    Moves forward a certain distance in inches while trying to keep straight, blocking.
    Will block while distance is not reached AND condition is true.

    distance: distance in inches, negative to go backwards
    ticksPerSecond: number between 0 and 1500, the power percent to use. Recommend anything below 1000 for best accuracy (say 700)
    */

    /* PSEUDOCODE

    When doing if statements, we want any distance values and ticks per seconds to be positive.

    Then, when actually moving the motors, we can change the speeds of them to be negative if we want to move backwards.

    We will use a multiplier variable to set whether or not to make the speeds negative.

    DO NOT ACTUALLY CHANGE WHETHER THE ARGUMENTS ARE NEGATIVE OR POSITIVE, USE ABS VALUES FUNCTIONS

    1. Set the multiplier depending on whether or not distance is negative
    2. Calculate target *counter* position based on inch distance and wheel radius as well as the current counter value.
    3. Create two variables that store the speed of the two motors. Make them equal to ticksPerSecond. These variables are always positive.
    4. Create two variables that store the position of the two motors. These variables are updated in the while loop.
       Position counters can be negative; they are essentially just a better name for the gmpc function
    5. Set the speed of both motors to the speed times the multiplier.
    6. While (absolute value of current counter position is less than absolute value of target counter position):
    7.      Update the position counters
    8.      If abs(one motor counter) > abs(other motor counter), decrease the faster motor's speed by the difference.
            Since the speed is always positive, you can just subtract the speed by the difference; no fidling with the multiplier
            When you finally actually run the method to change the motor speed, then you multiply the speed by the multiplier.
    9. If either motor's pos is beyond the target position, stop both motors, end method.
    */

    // 1. Set up the multiplier
    int multiplier = 1;

    if (distance < 0)
    {
        multiplier *= -1;
    }

    // 2. Calc target counter pos
    const int leftWheelTargetPos = distance * this->posPerOneInch + gmpc(this->leftWheelPin);
    const int rightWheelTargetPos = distance * this->posPerOneInch + gmpc(this->rightWheelPin);

    // 3. Store the SPEED (not velocity, because they never go negative) of the two motors.
    int leftWheelSpeed = ticksPerSecond;
    int rightWheelSpeed = ticksPerSecond;

    // 4. Create variables that store the positions of the two motors. These counters can be negative.
    int leftWheelPosition = gmpc(this->leftWheelPin);
    int rightWheelPosition = gmpc(this->rightWheelPin);

    // 5. Set both motors velocity by setting it to speed times the multiplier.
    move_at_velocity(this->leftWheelPin, leftWheelSpeed * multiplier);
    move_at_velocity(this->rightWheelPin, rightWheelSpeed * multiplier);

    // 6. While loop
    while (std::abs(leftWheelPosition) <= std::abs(leftWheelTargetPos) && std::abs(rightWheelPosition) <= std::abs(rightWheelTargetPos) && condition)
    {
        // 7. Update position counters
        int leftWheelPosition = gmpc(this->leftWheelPin);
        int rightWheelPosition = gmpc(this->rightWheelPin);

        // 8. If one wheel position is greater than the other, decrease the speed of the ahead motor by the difference
        // REMEMBER TO USE ABSOLUTE VALUE OF THE POSITIONS
        if (std::abs(leftWheelPosition) > std::abs(rightWheelPosition))
        {
            leftWheelSpeed = ticksPerSecond - (std::abs(leftWheelPosition) - std::abs(rightWheelPosition));
            rightWheelSpeed = ticksPerSecond;
        }
        else if (std::abs(leftWheelPosition) < std::abs(rightWheelPosition))
        {
            leftWheelSpeed = ticksPerSecond;
            rightWheelSpeed = ticksPerSecond - (std::abs(rightWheelPosition) - std::abs(leftWheelPosition));
        }
        else
        {
            leftWheelSpeed = ticksPerSecond;
            rightWheelSpeed = ticksPerSecond;
        }

        // Finally give commands to motors to move at the speed
        move_at_velocity(this->leftWheelPin, leftWheelSpeed * multiplier);
        move_at_velocity(this->rightWheelPin, rightWheelSpeed * multiplier);
    }

    // 6. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::moveDistance(int distance, int percentPower, bool condition)
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
    const int targetPos = distance * this->posPerOneInch;

    // 3. Power both motors
    motor_power(this->leftWheelPin, percentPower);
    motor_power(this->rightWheelPin, percentPower);

    // 4. while loop
    int leftWheelPos = std::abs(gmpc(this->leftWheelPin));
    int rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    while (leftWheelPos <= targetPos && rightWheelPos <= targetPos && condition)
    {
        leftWheelPos = std::abs(gmpc(this->leftWheelPin));
        rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    }

    // 5. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::moveContinuous(int percentPower)
{
    motor_power(this->leftWheelPin, percentPower);
    motor_power(this->rightWheelPin, percentPower);
}

void SmallRobot::rotateAndCorrect(int degrees, int percentPower)
{
    /*
    Rotates forward a certain amount of degrees clockwise while correcting for inherent motor power differences, blocking. Clears the pos counter.

    degrees: degrees to rotate clockwise. Use negative numbers to rotate counterclockwise.
    percentPower: number between 0 and 100, the power percent to use
    */

    /* PSEUDOCODE
    1. Clear counters, change percentPowers
    2. Calculate target counter pos based on degrees and wheel distance
    3. Power both motors
    4. While both motors are not at target counter:
    5.      If one motor counter is ahead of the other, freeze that motor a bit.
            I'm thinking this would probably allow the robot to correct itself if
            one motor is more powerful than the other.
    6. If either motor's pos is beyond the target, stop both motors.
    */

    // 1. Clear counters, change percentPower
    int leftPercentPower = percentPower;
    int rightPercentPower = percentPower;

    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);

    if (degrees < 0)
    {
        leftPercentPower *= -1;
    }
    else
    {
        rightPercentPower *= -1;
    }

    // 2. Calc target counter pos
    const int targetPos = (std::abs(degrees) / 360.0) * (2.0 * 3.14159265358979323846 * this->wheelDistance) * this->posPerOneInch;

    // 3. Power both motors
    motor_power(this->leftWheelPin, leftPercentPower);
    motor_power(this->rightWheelPin, rightPercentPower);

    // 4. while loop
    int leftWheelPos = std::abs(gmpc(this->leftWheelPin));
    int rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    while (leftWheelPos <= targetPos && rightWheelPos <= targetPos)
    {
        // 5. If one motor is more ahead than the other, stop that motor for a bit

        // Using freeze because docs say it has brake??? Not exactly sure if there's like a powerful brake but it would work regardless
        if (leftWheelPos > rightWheelPos)
        {
            freeze(this->leftWheelPin);
            motor_power(this->rightWheelPin, rightPercentPower);
        }
        else if (leftWheelPos < rightWheelPos)
        {
            motor_power(this->leftWheelPin, leftPercentPower);
            freeze(this->rightWheelPin);
        }
        else
        {
            motor_power(this->leftWheelPin, leftPercentPower);
            motor_power(this->rightWheelPin, rightPercentPower);
        }

        leftWheelPos = std::abs(gmpc(this->leftWheelPin));
        rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    }

    // 6. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::rotate(int degrees, int percentPower)
{
    // 1. Clear counters, change percentPower
    int leftPercentPower = percentPower;
    int rightPercentPower = percentPower;

    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);

    if (degrees < 0)
    {
        leftPercentPower *= -1;
    }
    else
    {
        rightPercentPower *= -1;
    }

    // 2. Calc target counter pos
    const int targetPos = (std::abs(degrees) / 360.0) * (2.0 * 3.14159265358979323846 * this->wheelDistance) * this->posPerOneInch;

    // 3. Power both motors
    motor_power(this->leftWheelPin, leftPercentPower);
    motor_power(this->rightWheelPin, rightPercentPower);

    // 4. while loop
    int leftWheelPos = std::abs(gmpc(this->leftWheelPin));
    int rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    while (leftWheelPos <= targetPos && rightWheelPos <= targetPos)
    {
        leftWheelPos = std::abs(gmpc(this->leftWheelPin));
        rightWheelPos = std::abs(gmpc(this->rightWheelPin));
    }

    // 5. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::turnLeftContinuous(int percentPower)
{
    motor_power(this->leftWheelPin, -1 * percentPower);
    motor_power(this->rightWheelPin, percentPower);
}

void SmallRobot::turnRightContinuous(int percentPower)
{
    motor_power(this->leftWheelPin, percentPower);
    motor_power(this->rightWheelPin, -1 * percentPower);
}

void SmallRobot::stop()
{
    /* Stops all turns and forward/backward movement */
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}