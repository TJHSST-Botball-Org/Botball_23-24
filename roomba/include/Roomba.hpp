#pragma once

class Roomba
{
public:
    Roomba() = default;

    void move(float distance);
    void rotate(float distance);
};