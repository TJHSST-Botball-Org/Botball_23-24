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
        // wait_for_light(Roomba::LIGHT_PIN);
        // shut_down_in(119);
        init();
        // robot->openClaw();
        // robot->getNoodle(0.85f);
        // robot->rotate(-135);
        // robot->move(-45); // getting out of the starting position
        // robot->rotate(-90);
        // robot->moveTillBump();      // move to first pool noodle pole
        // robot->rotate(180);         // face first pool noodle pole
        // robot->dropOffNoodle(0.6f); // place the first noodle
        // robot->rotate(90);          // face towards noodles
        // robot->moveTillBump();      // drive to noodles
        // robot->rotate(135);         // face towards pool noodles    2nd
        // robot->openClaw();
        // robot->getNoodle(1.0f);
        robot->setSlidePos(0.5f);
    }
    void reset()
    {
        robot->setSlidePitch(0.0f);
        robot->closeClaw();
    }
};

int main()
{
    Roomba_OpMode opmode = Roomba_OpMode();
    opmode.runOpMode();
    // opmode.reset();

    return 1;
}