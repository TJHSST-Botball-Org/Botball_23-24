#include <kipr/wombat.h>
// #include "../kipr/wombat.h"
#include <Roomba.h>

Roomba::Roomba()
{
    create_connect();
    cmpc(SLIDE_PIN);
}

float Roomba::lerp(float value, float a1, float b1, float a2, float b2)
{
    // First, find the normalized position of 'value' within the range [a1, b1]
    float t = (value - a1) / (b1 - a1);

    // Then, map this normalized position (t) to the new range [a2, b2]
    return a2 + t * (b2 - a2);
}

void Roomba::move(int distance, MOVEMENT_SPEED speed_enum)
{
    distance = distance * Roomba::DISTANCE_TO_INCHES; // scales the ticks to inches
    int factor = distance > 0 ? -1 : 1;
    int speed = static_cast<int>(speed_enum);
    set_create_distance(0);

    while (factor * get_create_distance() < distance)          // if forward, get_create_distance() returns negative
        create_drive_direct(-factor * speed, -factor * speed); // if forward, factor will be negative meaning we need to minus

    create_stop();
}

void Roomba::rotate(int angle, ROTATION_SPEED speed_enum)
{
    int factor = angle > 0 ? -1 : 1;
    set_create_total_angle(0);
    int speed = static_cast<int>(speed_enum);
    while (factor * get_create_total_angle() < angle)         // if turn right, get_create_total_angle() returns negative
        create_drive_direct(-factor * speed, factor * speed); // if turn right, factor will be negative
}

void Roomba::setSlidePos(float percentageTop, SLIDE_SPEED speed_enum)
{
    // I don't plan on clearing motor position to let gmpc give accurate value
    int currentPos = gmpc(SLIDE_PIN);
    float targetPos = (int)lerp(percentageTop, 0.0, 1.0, SLIDE_BOTTOM, SLIDE_TOP);
    int speed = static_cast<int>(speed_enum);
    int currentSpeed = speed;

    while (currentPos != targetPos)
    {
        /* code */
        currentPos = gmpc(SLIDE_BOTTOM);

        if (currentPos == targetPos)
        {
            currentSpeed = 0;
            continue;
        }
        else if (currentPos < targetPos) // slide is below target
        {
            if (targetPos - SLOW_DOWN_BUFFER <= currentPos)
            {
                currentSpeed = (int)lerp(currentPos, targetPos - SLOW_DOWN_BUFFER, targetPos, speed, 1.0);
            }
            else
            {
                currentSpeed = speed;
            }
        }
        else
        { // slide is above target
            if (currentPos <= targetPos + SLOW_DOWN_BUFFER)
            {
                currentSpeed = (int)lerp(currentPos, targetPos, targetPos + SLOW_DOWN_BUFFER, -1, -speed);
            }
            else
            {
                currentSpeed = -speed;
            }
        }
        move_at_velocity(SLIDE_PIN, currentSpeed);
    }

    freeze(SLIDE_PIN);
}

void Roomba::setSlidePitch(float percentageUp)
{
    enable_servo(SLIDE_PITCH_PIN);
    set_servo_position(SLIDE_PITCH_PIN, lerp(percentageUp, 0.0, 1.0, SLIDE_PITCH_DOWN, SLIDE_PITCH_UP));
    msleep(SLIDE_PITCH_SLEEP);
}

void Roomba::setClawPos(float percentageOpen)
{
    enable_servo(CLAW_PIN);
    set_servo_position(CLAW_PIN, lerp(percentageOpen, 0.0, 1.0, CLAW_CLOSED, CLAW_OPEN));
    msleep(CLAW_SLEEP);
}

bool Roomba::switchPressed()
{
    return get_digital_value(SWITCH_PIN) == 1;
}