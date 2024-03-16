#pragma once
#include <kipr/wombat.h>

class SmallRobot
{
private:
    const int wheelRadius;   // Both are in inches
    const int wheelDistance; // Distance between the wheels across the robot body; the length of the axle connecting the two wheels if there was an axle
    int leftWheelPin;
    int rightWheelPin;
    float posPerOneInch;

public:
    SmallRobot(int leftWheelPin, int rightWheelPin, int wheelDistance, int wheelRadius);

    void moveDistanceAndCorrect(int distance, int ticksPerSecond, bool condition = true); // Moves for some distance, blocking
    void moveDistance(int distance, int percentPower, bool condition = true);             // Same as moveForwardDistanceAndCorrect, but does not correct

    void moveContinuous(int percentPower); // Moves continously forward/backwards. percentPower -100 to 100

    void rotate(int degrees, int percentPower);           // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.
    void rotateAndCorrect(int degrees, int percentPower); // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.

    void turnLeftContinuous(int percentPower);  // Turns left continously. Percent power 0-100
    void turnRightContinuous(int percentPower); // Turns right continously. Percent power 0-100

    void stop(); // Stops all turns and forward/backward movement.

    // TODO: ADD SMALL ROBOT SPECIFIC FUNCTIONS LATER
};