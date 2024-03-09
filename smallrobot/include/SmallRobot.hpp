#pragma once
#include <kipr/wombat.hpp>

class SmallRobot
{
private:
    const int wheelRadius = 1; // Both are in inches
    const int wheelDistance = 1; // Distance between the wheels across the robot body; the length of the axle connecting the two wheels if there was an axle
    int leftWheelPin;
    int rightWheelPin;
    float posPerOneCm;

public:
    SmallRobot(int leftWheelPin, int rightWheelPin);

    void moveDistanceAndCorrect(int distance, int percentPower, bool condition=true); // Moves for some distance, blocking
    void moveDistance(int distance, int percentPower, bool condition=true); // Same as moveForwardDistanceAndCorrect, but does not correct


    void moveForwardContinuous();      // Moves continously forward
    void moveBackwardContinuous();         // Moves contiously backwards

    void rotate(int degrees, int percentPower); // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.
    void rotateAndCorrect(int degrees, int percentPower); // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.

    void turnLeftContinuous(int percentPower=100);          // Turns left continously
    void turnRightContinuous(int percentPower=100);         // Turns right continously

    void freeze(); // Stops all turns and forward/backward movement.

    // TODO: ADD SMALL ROBOT SPECIFIC FUNCTIONS LATER
};