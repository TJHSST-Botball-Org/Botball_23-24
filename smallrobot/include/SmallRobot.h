#pragma once
#include <kipr/wombat.h>

class SmallRobot
{
private:
    const int wheelRadius = 1; // Both are in inches
    const int wheelDistance = 1; // Distance between the wheels across the robot body; the length of the axle connecting the two wheels if there was an axle
    const int blackLineThreshold; //Light Sensor threshold for a black line
    int leftWheelPin;
    int rightWheelPin;
    int leftLightPin;
    int rightLightPin;
    float posPerOneCm;

public:
    SmallRobot(int leftWheelPin, int rightWheelPin, int leftColorPin = -1, int rightColorPin = -1);

    void moveDistanceAndCorrect(int distance, int ticksPerSecond, bool condition=true, bool debug=false); // Moves for some distance, blocking. Ticks can be 0 to 1500, to go backwards make distance negative.
    void moveDistance(int distance, int ticksPerSecond, bool condition=true); // Same as moveForwardDistanceAndCorrect, but does not correct
    void moveUntilBlackLine(int percentPower);//Blocking, and goes forward until both light sensors see black lines

    void moveContinuous(int percentPower);      // Moves continously forward/backwards. percentPower -100 to 100

    void rotate(int degrees, int percentPower); // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.
    void rotateAndCorrect(int degrees, int percentPower); // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.

    void turnLeftContinuous(int percentPower);          // Turns left continously. Percent power 0-100
    void turnRightContinuous(int percentPower);         // Turns right continously. Percent power 0-100

    void stop(); // Stops all turns and forward/backward movement.

    // TODO: ADD SMALL ROBOT SPECIFIC FUNCTIONS LATER
};