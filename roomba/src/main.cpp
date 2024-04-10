#include <kipr/wombat.h>
#include <iostream>
#include <OpMode.h>
#include <Roomba.h>

class Roomba_OpMode : public OpMode
{
private:
    Roomba robot;

public:
    Roomba_OpMode() : OpMode()
    {
        // initilization
        this->robot = Roomba();
    }

    void runOpMode() override
    {
        robot.move(50);
    }
};

int main()
{
    Roomba_OpMode opmode = Roomba_OpMode();
    opmode.runOpMode();

    return 1;
}