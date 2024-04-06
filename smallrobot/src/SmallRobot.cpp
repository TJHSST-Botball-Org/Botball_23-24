#include "../include/SmallRobot.h"
#include <kipr/wombat.h>
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846;

SmallRobot::SmallRobot(int leftWheelPin, int rightWheelPin, float wheelDistance, float wheelRadius, int leftTicksPerRevolution, int rightTicksPerRevolution, int leftLightPin, int rightLightPin, int clawServoPin, int armServoPin)
{
    this->leftWheelPin = leftWheelPin;
    this->rightWheelPin = rightWheelPin;
    this->wheelDistance = wheelDistance;
    this->wheelRadius = wheelRadius;
    this->leftTicksPerRevolution = leftTicksPerRevolution;
    this->rightTicksPerRevolution = rightTicksPerRevolution;

    this->leftLightPin = leftLightPin;
    this->rightLightPin = rightLightPin;

    this->leftPosPerOneInch = leftTicksPerRevolution / (2.0 * PI * this->wheelRadius);
    this->rightPosPerOneInch = rightTicksPerRevolution / (2.0 * PI * this->wheelRadius);

    this->clawServoPin = clawServoPin;
    this->armServoPin = armServoPin;

    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);
}

void SmallRobot::moveDistanceAndCorrect(float distance, int ticksPerSecond, bool condition)
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

    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);

    // 1. Set up the multiplier
    int multiplier = 1;

    if (distance < 0)
    {
        multiplier *= -1;
    }

    // 2. Calc target counter pos

    const int leftWheelTargetPos = distance * this->leftPosPerOneInch + gmpc(this->leftWheelPin);
    const int rightWheelTargetPos = distance * this->rightPosPerOneInch + gmpc(this->rightWheelPin);

    // 3. Store the SPEED (not velocity, because they never go negative) of the two motors.
    int leftWheelSpeed = ticksPerSecond;
    int rightWheelSpeed = ticksPerSecond;

    // 4. Create variables that store the positions of the two motors. These counters can be negative.
    int leftWheelPosition = gmpc(this->leftWheelPin);
    int rightWheelPosition = gmpc(this->rightWheelPin);

    // 5. Set both motors velocity by setting it to speed times the multiplier.
    move_at_velocity(this->leftWheelPin, 100 * multiplier);
    move_at_velocity(this->rightWheelPin, 100 * multiplier);

    // 6. While loop
    while (std::abs(leftWheelPosition) <= std::abs(leftWheelTargetPos) && std::abs(rightWheelPosition) <= std::abs(rightWheelTargetPos) && condition)
    {
        // 7. Update position counters
        leftWheelPosition = gmpc(this->leftWheelPin);
        rightWheelPosition = gmpc(this->rightWheelPin);

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

    // 9. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::moveDistance(float distance, int ticksPerSecond, bool condition)
{
    /*
    Moves forward a certain distance in inches, blocking.
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
    8. If either motor's pos is beyond the target position, stop both motors, end method.
    */

    // 1. Set up the multiplier
    int multiplier = 1;

    if (distance < 0)
    {
        multiplier *= -1;
    }

    // 2. Calc target counter pos
    const int leftWheelTargetPos = distance * this->leftPosPerOneInch + gmpc(this->leftWheelPin);
    const int rightWheelTargetPos = distance * this->rightPosPerOneInch + gmpc(this->rightWheelPin);

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
        leftWheelPosition = gmpc(this->leftWheelPin);
        rightWheelPosition = gmpc(this->rightWheelPin);
    }

    // 8. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

// void SmallRobot::moveUntilBlackLine(int percentPower){

//     cmpc(this->leftWheelPin);
//     cmpc(this->rightWheelPin);

//     motor_power(this->leftWheelPin, percentPower);
//     motor_power(this->rightWheelPin, percentPower);
//     while(analog(leftLightPin)<blackLineThreshold and analog(leftLightPin)<blackLineThreshold){

//     }
//     freeze(this->leftWheelPin);
//     freeze(this->rightWheelPin);
// }
void SmallRobot::rotateAndCorrect(int degrees, int ticksPerSecond, bool condition)

{

    /* PSEUDOCODE

    When doing if statements, we want any degrees or distance values and ticks per seconds to be positive.

    Then, when actually moving the motors, we can change the speeds of them to be negative if we want to move backwards.

    We will use two multiplier variables, one for each motor, to set whether or not to make the speeds negative.

    In addition, since we are rotating, one motor needs to go a negative distance, while another needs to go a positive distance.
    So, we will use the two multiplier variables to affect the target position counters as well.

    DO NOT ACTUALLY CHANGE WHETHER THE ARGUMENTS ARE NEGATIVE OR POSITIVE, USE ABS VALUES FUNCTIONS

    1. Set the multipliers for each motor depending on whether or not degrees is negative
    2. Calculate target *counter* position based.
       Formula: ((degree/360) * circle circumference) * posPerInch * motor's multiplier;
    3. Create two variables that store the speed of the two motors. Make them equal to ticksPerSecond. These variables are always positive.
    4. Create two variables that store the position of the two motors. These variables are updated in the while loop.
       Position counters can be negative; they are essentially just a better name for the gmpc function
    5. Set the speed of both motors to the speed times the motor's corresponding multiplier.
    6. While (absolute value of current counter position is less than absolute value of target counter position):
    7.      Update the position counters
    8.      If abs(one motor counter) > abs(other motor counter), decrease the faster motor's speed by the difference.
            Since the speed is always positive, you can just subtract the speed by the difference; no fidling with the multiplier
            When you finally actually run the method to change the motor speed, then you multiply the speed by the multiplier.
    9. If either motor's pos is beyond the target position, stop both motors, end method.
    */

    cmpc(this->leftWheelPin);
    cmpc(this->rightWheelPin);

    // 1. Set up the multipliers
    int leftMultiplier = 1;
    int rightMultiplier = -1;

    if (degrees < 0)
    {
        leftMultiplier = -1;
        rightMultiplier = 1;
    }

    // 2. Calc target counter pos
    const float circleCircumference = PI * this->wheelDistance;

    const int leftWheelTargetPos = (std::abs(degrees) / 360.0) * circleCircumference * leftPosPerOneInch * leftMultiplier + gmpc(this->leftWheelPin);
    const int rightWheelTargetPos = (std::abs(degrees) / 360.0) * circleCircumference * rightPosPerOneInch * rightMultiplier + gmpc(this->rightWheelPin);

    // 3. Store the SPEED (not velocity, because they never go negative) of the two motors.
    int leftWheelSpeed = ticksPerSecond;
    int rightWheelSpeed = ticksPerSecond;

    // 4. Create variables that store the positions of the two motors. These counters can be negative.
    int leftWheelPosition = gmpc(this->leftWheelPin);
    int rightWheelPosition = gmpc(this->rightWheelPin);

    // 5. Set both motors velocity by setting it to speed times the multiplier.
    move_at_velocity(this->leftWheelPin, leftWheelSpeed * leftMultiplier);
    move_at_velocity(this->rightWheelPin, rightWheelSpeed * rightMultiplier);

    std::cout << "\n"
              << leftWheelPosition << " " << leftWheelTargetPos << "\n"
              << std::flush;
    std::cout << "\n"
              << rightWheelPosition << " " << rightWheelTargetPos << "\n"
              << std::flush;

    // 6. While loop
    bool loopCondition = true;

    std::cout << loopCondition << "\n"
              << std::flush;

    while (loopCondition)
    {
        if (degrees > 0)
        {
            loopCondition = leftWheelPosition <= leftWheelTargetPos && rightWheelPosition >= rightWheelTargetPos && condition;
        }
        else
        {
            loopCondition = leftWheelPosition >= leftWheelTargetPos && rightWheelPosition <= rightWheelTargetPos && condition;
        }

        // 7. Update position counters
        leftWheelPosition = gmpc(this->leftWheelPin);
        rightWheelPosition = gmpc(this->rightWheelPin);

        // 8. If one wheel position is greater than the other, decrease the speed of the ahead motor by the difference
        // REMEMBER TO USE ABSOLUTE VALUE OF THE POSITIONS
        if (std::abs(std::abs(leftWheelPosition) - std::abs(leftWheelPosition)) > std::abs(std::abs(rightWheelPosition) - std::abs(rightWheelPosition)))
        {
            leftWheelSpeed = ticksPerSecond - (std::abs(std::abs(leftWheelPosition) - std::abs(leftWheelPosition)) - std::abs(std::abs(rightWheelPosition) - std::abs(rightWheelPosition)));
            rightWheelSpeed = ticksPerSecond;
        }
        else if (std::abs(std::abs(leftWheelPosition) - std::abs(leftWheelPosition)) < std::abs(std::abs(rightWheelPosition) - std::abs(rightWheelPosition)))
        {
            leftWheelSpeed = ticksPerSecond - (std::abs(std::abs(rightWheelPosition) - std::abs(rightWheelPosition)) - std::abs(std::abs(leftWheelPosition) - std::abs(leftWheelPosition)));
            rightWheelSpeed = ticksPerSecond;
        }
        else
        {
            leftWheelSpeed = ticksPerSecond;
            rightWheelSpeed = ticksPerSecond;
        }

        // Finally give commands to motors to move at the speed
        move_at_velocity(this->leftWheelPin, leftWheelSpeed * leftMultiplier);
        move_at_velocity(this->rightWheelPin, rightWheelSpeed * rightMultiplier);
    }

    // 8. If either motor's pos is beyond the target, stop both motors.
    freeze(this->leftWheelPin);
    freeze(this->rightWheelPin);
}

void SmallRobot::rotate(int degrees, int percentPower, bool condition)
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
    // TODO: USE TWO DIFFERENT TARGET POS
    const int targetPos = (std::abs(degrees) / 360.0) * (2.0 * 3.14159265358979323846 * this->wheelDistance) * this->leftPosPerOneInch;

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

void SmallRobot::openClaw()
{
    enable_servo(this->clawServoPin);
    set_servo_position(this->clawServoPin, 500);
    disable_servo(this->clawServoPin);
}

void SmallRobot::closeClaw()
{
    enable_servo(this->clawServoPin);
    set_servo_position(this->clawServoPin, 0);
    disable_servo(this->clawServoPin);
}

void SmallRobot::setArmPosition(int pos, int speed)
{
    enable_servo(this->armServoPin);

    bool isGoingUp = pos > get_servo_position(this->armServoPin);

    while (true)
    {
        if (isGoingUp && pos <= get_servo_position(this->armServoPin))
            break;
        if (!isGoingUp && pos >= get_servo_position(this->armServoPin))
            break;

        if (isGoingUp)
        {
            set_servo_position(this->armServoPin, get_servo_position(this->armServoPin) + speed)
        }
        else
        {
            set_servo_position(this->armServoPin, get_servo_position(this->armServoPin) - speed)
        }

        msleep(1);
    }

    set_servo_position(this->armServoPin, pos);

    disable_servo(this->armServoPin);
}