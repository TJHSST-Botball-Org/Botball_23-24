#pragma once

class MOVEMENT_SPEED
{
public:
    static constexpr int SLOW = 100;
    static constexpr int DEFAULT = 300;
    static constexpr int FAST = 500;
};

class ROTATION_SPEED
{
public:
    static constexpr int SLOW = 150;
    static constexpr int DEFAULT = 250;
    static constexpr int FAST = 350;
};

class SLIDE_SPEED
{
public:
    static constexpr int SLOW = 50;
    static constexpr int DEFAULT = 100;
    static constexpr int FAST = 150;
};

class SLIDE_POS
{
public:
    static constexpr float BOTTOM = 0.0f;
    static constexpr float TOP = 1.0f;
};

class Roomba
{
private:
    static const int DISTANCE_TO_INCHES = 1;
    static constexpr float ANGLE_TO_TICKS = 25.0f / 90.0f;

    static const int SLIDE_PIN = 0;         // motor
    static const int SLIDE_TOP = 2000;      // ticks
    static const int SLIDE_BOTTOM = 0;      // ticks
    static const int SLOW_DOWN_BUFFER = 50; // distance away from targetPos you should start slowing down
    static const int SLIDE_SLEEP = 100;

    static const int SLIDE_PITCH_PIN = 0; // servo
    static const int SLIDE_PITCH_VERTICAL = 850;
    static const int SLIDE_PITCH_HORIZONTAL = 0;
    static const int SLIDE_PITCH_SLEEP = 500;

    static const int CLAW_PIN = 1; // servo
    static const int CLAW_OPEN = 1228;
    static const int CLAW_CLOSED = 500;
    static const int CLAW_SLEEP = 100; // this is essentially the speed

    static const int TOP_SWITCH = 0;    // digital. This is the switch at the top of the slides
    static const int BOTTOM_SWITCH = 4; // digital. This is the switch at the bottom of the slides

private:
    int lastSlidePos = 0;

private:
    static float lerp(float value, float a1, float b1, float a2, float b2);
    static float scale(float value, float a1, float b1, float a2, float b2);

private:
    bool topPressed();
    bool bottomPressed();

public:
    Roomba();

    void move(int distance, int speed = MOVEMENT_SPEED::DEFAULT); // forward and backwards
    void rotate(int angle, int speed = ROTATION_SPEED::DEFAULT);  // right and left

    /*
    precondition :
        - 0.0 <= percentageUp <= 1.0
    */
    void setSlidePos(float percentageTop, bool startingAtTop, int speed = MOVEMENT_SPEED::DEFAULT);
    void setSlidePitch(float percentageVertical);
    /*
    precondition :
        - 0.0 <= percentageClosed <= 1.0
    */
    void setClawPos(float percentageOpen);
    void closeClaw();
    void openClaw();

    void getNoodle(float percentageUp, int speed = MOVEMENT_SPEED::DEFAULT);
    /*
    precondition :
        - starts at percentup 1.0
    */
    void dropOffNoodle(float percentageUp, int speed = MOVEMENT_SPEED::DEFAULT);
};
