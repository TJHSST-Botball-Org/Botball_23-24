#pragma once
#include <kipr/wombat.h>

class SmallRobot
{
private:
    float wheelRadius;   // Both are in inches
    float wheelDistance; // Distance between the wheels across the robot body; the length of the axle connecting the two wheels if there was an axle
    int leftWheelPin;
    int rightWheelPin;
    int leftTicksPerRevolution;
    int rightTicksPerRevolution;
    int leftPosPerOneInch;
    int rightPosPerOneInch;
    int leftLightPin;
    int rightLightPin;

public:
    SmallRobot(int leftWheelPin, int rightWheelPin, float wheelDistance, float wheelRadius, int leftTicksPerRevolution, int rightTicksPerRevolution, int leftColorPin = -1, int rightColorPin = -1);

    void moveDistanceAndCorrect(float distance, int ticksPerSecond, bool condition = true); // Moves for some distance, blocking
    void moveDistance(float distance, int ticksPerSecond, bool condition = true);           // Same as moveForwardDistanceAndCorrect, but does not correct

    void moveContinuous(int percentPower); // Moves continously forward/backwards. percentPower -100 to 100
    void moveUntilBlackLine(int percentPower);//Blocking, and goes forward until both light sensors see black lines

    void rotateAndCorrect(int degrees, int ticksPerSecond, bool condition = true); // Rotates a certain amount of degrees clockwise and corrects. Accepts values from -360 to 360. Blocking.
    void rotate(int degrees, int percentPower, bool condition = true);             // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.

    void turnLeftContinuous(int percentPower);  // Turns left continously. Percent power 0-100
    void turnRightContinuous(int percentPower); // Turns right continously. Percent power 0-100

    void stop(); // Stops all turns and forward/backward movement.

    // TODO: ADD SMALL ROBOT SPECIFIC FUNCTIONS LATER
};