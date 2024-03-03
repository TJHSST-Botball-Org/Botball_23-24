#pragma once
#include <kipr/wombat.hpp>

class SmallRobot
{
private:
    const int wheelRadius = 1;

public:
    void move(int distance); // Moves for some distance, blocking
    void moveForward();      // Moves continously forward
    void moveBack();         // Moves contiously backwards
    void stopMove();

    void rotate(int degrees); // Rotates a certain amount of degrees clockwise. Accepts values from -360 to 360. Blocking.
    void turnLeft();          // Turns left continously
    void turnRight();         // Turns right continously
    void stopTurn();

    // TODO: ADD SMALL ROBOT SPECIFIC FUNCTIONS LATER
}