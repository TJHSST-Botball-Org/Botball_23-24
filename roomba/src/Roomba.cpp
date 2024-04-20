#include <kipr/wombat.h>
// #include "../kipr/wombat.h"
#include <Roomba.h>
#include <iostream>

Roomba::Roomba()
{
    create_connect();
}

float Roomba::lerp(float value, float a1, float b1, float a2, float b2)
{
    // First, find the normalized position of 'value' within the range [a1, b1]
    float t = (value - a1) / (b1 - a1);

    // Then, map this normalized position (t) to the new range [a2, b2]
    return a2 + t * (b2 - a2);
}
float Roomba::scale(float value, float a1, float b1, float a2, float b2)
{
    return value * (b2 - a2) / (b1 - a1);
}

bool Roomba::topPressed()
{
    return get_digital_value(TOP_SWITCH) == 1;
}
bool Roomba::bottomPressed()
{
    std::cout << get_digital_output(BOTTOM_SWITCH) << std::endl;
    return get_digital_value(BOTTOM_SWITCH) == 1;
}

void Roomba::move(int distance, int speed)
{
    distance = -distance;                             // front of the roomba is the back so that is why reverse
    distance = distance * Roomba::DISTANCE_TO_INCHES; // scales the ticks to inches

    set_create_distance(0);
    if (distance > 0)
    {
        while (-get_create_distance() < distance)
            create_drive_direct(speed, speed);
    }
    else
    {
        while (get_create_distance() < -distance)
            create_drive_direct(-speed, -speed);
    }

    create_stop();
}

void Roomba::rotate(int angle, int speed)
{
    angle = (int)(angle * ANGLE_TO_TICKS);
    set_create_total_angle(0);

    if (angle > 0)
        while (-get_create_total_angle() < angle)
            create_drive_direct(speed, -speed);
    else
        while (get_create_total_angle() < -angle)
            create_drive_direct(-speed, speed);
}

void Roomba::setSlidePos(float percentageTop, bool startingAtTop, int speed)
{
    /*
    Notes :
    - If you go down, ticks from motor DECREASES
    - If you go up, ticks from motor INCREASES
    */

    // plan : go from top -> targetPosition / percentageTop

    cmpc(SLIDE_PIN);
    // rewrite
    if (startingAtTop)
    {
        int deltaTicks = (int)scale(percentageTop - 1.0, 0.0, 1.0, SLIDE_BOTTOM, SLIDE_TOP); // moving down (aka. deltaTicks < 0)

        while (-gmpc(SLIDE_PIN) > deltaTicks)
            move_at_velocity(SLIDE_PIN, -speed);
    }
    else
    {
        int deltaTicks = (int)scale(percentageTop, 0.0, 1.0, SLIDE_BOTTOM, SLIDE_TOP); // moving up (aka. deltaTick > 0)
        while (gmpc(SLIDE_PIN) < deltaTicks)
            move_at_velocity(SLIDE_PIN, speed);
    }

    freeze(SLIDE_PIN);
}

void Roomba::setSlidePitch(float percentageVertical)
{
    enable_servo(SLIDE_PITCH_PIN);
    set_servo_position(SLIDE_PITCH_PIN, lerp(percentageVertical, 0.0f, 1.0f, SLIDE_PITCH_HORIZONTAL, SLIDE_PITCH_VERTICAL));
    msleep(SLIDE_PITCH_SLEEP);
}

void Roomba::setClawPos(float percentageOpen)
{
    enable_servo(CLAW_PIN);
    set_servo_position(CLAW_PIN, lerp(percentageOpen, 0.0f, 1.0f, CLAW_CLOSED, CLAW_OPEN));
    msleep(CLAW_SLEEP);
}
void Roomba::closeClaw()
{
    setClawPos(0.0f);
}
void Roomba::openClaw()
{
    setClawPos(1.0f);
}

void Roomba::getNoodle(float percentageUp, int speed)
{
    if (percentageUp < 0.5)
    { // use bottom switch for reference
        while (!bottomPressed())
            move_at_velocity(SLIDE_PIN, -speed);
        msleep(SLIDE_SLEEP);
        setSlidePos(percentageUp, false, speed);
    }
    else
    { // use top switch for reference
        while (!topPressed())
            move_at_velocity(SLIDE_PIN, speed);
        msleep(SLIDE_SLEEP);
        setSlidePos(percentageUp, true, speed);
    }
    closeClaw();

    // once you got the noodle, go to the top
    while (!topPressed())
        move_at_velocity(SLIDE_PIN, speed);
}

void Roomba::dropOffNoodle(float percentageUp, int speed)
{
    setSlidePos(percentageUp, true, speed);
    msleep(SLIDE_SLEEP);
    openClaw();
    msleep(CLAW_SLEEP);
}
