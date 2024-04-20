#include <kipr/wombat.h>
#include <iostream>
#include <OpMode.h>
#include <Roomba.h>

class Roomba_OpMode : public OpMode
{
private:
    Roomba *robot;

public:
    Roomba_OpMode() : OpMode()
    {
        // initilization
        robot = new Roomba();
    }
    ~Roomba_OpMode()
    {
        delete robot;
    }

    void init()
    {
        robot->setSlidePitch(1.0f);
        robot->closeClaw();
        msleep(1000);
    }
    void runOpMode() override
    {
        init();
        robot->openClaw();
        robot->getNoodle(0.85);
        // robot->rotate(30); // turn straight after first noodle
        // robot->move(5); // move out of starting area (with noodle)
        // robot->rotate(-90); // turn left (towards poles)
        // robot->move(15); //move towards poles
        // robot->rotate(-90); //turn toward small pole
        // robot->move(5); // move toward edge
        // robot->rotate(90); //face up towards smallest pole
    }
};

int main()
{
    Roomba_OpMode opmode = Roomba_OpMode();
    opmode.runOpMode();
    return 1;
}