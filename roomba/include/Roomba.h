#pragma once

class Roomba
{
public:
    enum class MOVEMENT_SPEED
    {
        SLOW = 100,
        DEFAULT = 300,
        FAST = 500,
    };
    enum class ROTATION_SPEED
    {
        SLOW = 150,
        DEFAULT = 250,
        FAST = 350,
    };
    enum class SLIDE_SPEED
    {
        SLOW = 10,
        DEFAULT = 20,
        FAST = 30,
    };

private:
    static const int DISTANCE_TO_INCHES = 1;

    static const int SLIDE_PIN = 0;         // motor
    static const int SLIDE_TOP = 150;       // ticks
    static const int SLIDE_BOTTOM = 0;      // ticks
    static const int SLOW_DOWN_BUFFER = 50; // distance away from targetPos you should start slowing down

    static const int SLIDE_PITCH_PIN = 0; // servo
    static const int SLIDE_PITCH_UP = 100;
    static const int SLIDE_PITCH_DOWN = 0;
    static const int SLIDE_PITCH_SLEEP = 500;

    static const int CLAW_PIN = 1; // servo
    static const int CLAW_OPEN = 100;
    static const int CLAW_CLOSED = 0;
    static const int CLAW_SLEEP = 100; // this is essentially the speed

    static const int SWITCH_PIN = 0; // digital

private:
    int lastSlidePos = 0;

private:
    static float lerp(float value, float a1, float b1, float a2, float b2);

public:
    Roomba();

    void move(int distance, Roomba::MOVEMENT_SPEED speed = Roomba::MOVEMENT_SPEED::DEFAULT); // forward and backwards
    void rotate(int angle, Roomba::ROTATION_SPEED speed = Roomba::ROTATION_SPEED::DEFAULT);  // right and left

    /*
    precondition :
        - 0.0 <= percentageUp <= 1.0
    */
    void setSlidePos(float percentageTop, Roomba::SLIDE_SPEED speed = Roomba::SLIDE_SPEED::DEFAULT);
    void setSlidePitch(float percentageUp);
    /*
    precondition :
        - 0.0 <= percentageClosed <= 1.0
    */
    void setClawPos(float percentageOpen);
    bool switchPressed();
};