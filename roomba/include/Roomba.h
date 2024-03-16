#pragma once

class Roomba
{
public:
    Roomba() = default;

    void move(int distance, int speed = 300); // forward and backwards
    void rotate(int angle, int speed = 250);  // right and left
};