#pragma once

class Roomba
{
public:
    Roomba() = default;

    void move(int distance, int speed = 250);
    void rotate(float distance);
    void rotate(float distance, int speed = 250);
};