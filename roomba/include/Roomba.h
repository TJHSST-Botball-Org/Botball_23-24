#pragma once

class MOVEMENT_SPEED
{
public:
    static constexpr int SLOW = 100;
    static constexpr int DEFAULT = 200;
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
    static constexpr int SLOW = 500;
    static constexpr int DEFAULT = 1000;
    static constexpr int FAST = 1250;
};

class SLIDE_POS
{
public:
    static constexpr float BOTTOM = 0.0f;
    static constexpr float TOP = 1.0f;
};

class Color
{
    static constexpr int BLACK = 1000;
};

class Roomba
{
public:
    static const int LIGHT_PIN = 0;

private:
    static const int DISTANCE_TO_INCHES = 1;
    static constexpr float ANGLE_TO_TICKS = 25.0f / 90.0f;

    static const int SLIDE_PIN = 0;         // motor
    static const int SLIDE_TOP = 4512;      // ticks
    static const int SLIDE_BOTTOM = 0;      // ticks
    static const int SLOW_DOWN_BUFFER = 50; // distance away from targetPos you should start slowing down
    static const int SLIDE_SLEEP = 2000;

    static const int SLIDE_PITCH_PIN = 0; // servo
    static const int SLIDE_PITCH_VERTICAL = 800;
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
    void moveTillBump(bool both = false, int speed = MOVEMENT_SPEED::DEFAULT);
    void rotate(int angle, int speed = ROTATION_SPEED::DEFAULT); // right and left

    /*
  precondition :
      - 0.0 <= percentageUp <= 1.0
      - Slides go up and go down to the correct percentage
      - Starts from the top
  */
    void setSlidePos(float percentageTop, int speed = MOVEMENT_SPEED::DEFAULT);
    void setSlidePitch(float percentageVertical); // 1.0f is vertical 0.0f is horizontal
    /*
    precondition :
        - 0.0 <= percentageClosed <= 1.0
    */
    void setClawPos(float percentageOpen);
    void closeClaw();
    void openClaw();

    /*
     * Precondition :
     *    - Claw should be open
     */
    void getNoodle(float percentageUp, int speed = SLIDE_SPEED::DEFAULT);
    /*
    precondition :
        - Starts from the top
    */
    void dropOffNoodle(float percentageUp, int speed = SLIDE_SPEED::DEFAULT);
};
