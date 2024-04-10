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
        this->robot = Roomba();
        create_connect();
    }

    void runOpMode() override
    {
        //ROOMBA ROUTING ONLY. NOODLE INTERACTION NOT YET IMPLEMENTED. DISTANCES/ROTATIONS/SPEED SUBJECT TO CHANGE.

        //BEGIN. HEAD TO PHASE 1 LOCATION
        robot.rotate(-45, 50);
        robot.move(2, 50);
        robot.rotate(-90, 50);
        robot.move(4, 50);
        robot.rotate(-90, 50);
        //BEGIN PHASE 1
        robot.move(0.5, 50);
        robot.rotate(-90. 50); //and pick up
        robot.rotate(90, 50);
        robot.move(0.5, 50); //whereever the first pole is
        robot.rotate(90, 50); //and drop
        robot.rotate(90, 50);
        robot.move(0.5, 50);//whereever the next noodle is
        robot.rotate(90, 50);//and pick up
        robot.rotate(90, 50);
        robot.move(0.5, 50);//go to pole 1
        robot.rotate(90, 50);//and drop
        robot.rotate(90, 50);
        robot.move(0.5, 50);//whereever the next noodle is
        robot.rotate(90, 50);//and pick up
        robot.rotate(90, 50);
        robot.move(0.5, 50);//go to pole 2
        robot.rotate(90, 50);//and drop
        robot.rotate(90, 50);
        robot.move(0.5, 50);//whereever the next noodle is
        robot.rotate(90, 50);//and pick up
        robot.rotate(90, 50);
        robot.move(0.5, 50);//go to pole 2
        robot.rotate(90, 50);//and drop
        for(int i = 0; i < 2; i++){
            robot.rotate(90, 50);
            robot.move(0.5, 50);//whereever the next noodle is
            robot.rotate(90, 50);//and pick up
            robot.rotate(90, 50);
            robot.move(0.5, 50);//go to pole 2
            robot.rotate(90, 50);//and drop
        }
        for(int j = 0; j < 3; j++){
            robot.rotate(90, 50);
            robot.move(0.5, 50);//whereever the next noodle is
            robot.rotate(90, 50);//and pick up
            robot.rotate(90, 50);
            robot.move(0.5, 50);//go to pole 4
            robot.rotate(90, 50);//and drop
        }
        //END OF PHASE 1, NAVIGATE TO PHASE 2 LOCATION
        robot.rotate(90, 50);
        robot.move(4, 50);//to moon base
        //BEGIN PHASE 2
        robot.rotate(-45, 50); //face directly at panel with noodle
        for(int k = 0; k < 2; k++){
            //place code to pick noodle up
            robot.rotate(-45, 50);//face pole 5.
            robot.move(0.1, 50); //just a hair enough to get to pole 5.
            //place code to drop noodle on pole 5.
            robot.rotate(135, 50);//head back to panel.
            robot.move(0.1, 50); //just a hair
            robot.rotate(90, 50); //face the robot DIRECTLY at panel!
        }
        //END OF PHASE 2. NAVIGATE TO PHASE 3.
        robot.rotate(90, 50);
        robot.move(0.5, 50);
        robot.rotate(-90, 50);
        robot.move(0.5, 50);
        robot.rotate(-90, 50);
        //BEGIN PHASE 3
        for(int l = 0; l < 2; l++){
            //place code to pick noodle up
            robot.rotate(-45, 50); //subject to change. Rotate to face pole 6.
            robot.move(0.1, 50); //just a hair enough to get to pole 6.
            //place code to drop noodle on pole 5.
            robot.rotate(135, 50); //subject to change. Back to panel.
            robot.move(0.1, 50); //just a hair
            robot.rotate(90, 50); //face the robot DIRECTLY at panel!
        }
        //END OF PHASE 3. NAVIGATE TO PHASE 4.
        robot.rotate(180, 50);
        robot.rotate(45, 50);
        robot.move(2, 50); //move out a little
        robot.rotate(90, 50);
        robot.move(5.5, 50); //go to last noodle sector.
        robot.rotate(90, 50);
        robot.move(1, 50); //get close to noodle.
        //BEGIN PHASE 4
        for(int l = 0; l < 4; l++){
            //code to pick up noodle.
            robot.rotate(90, 50);
            robot.move(0.5, 50);
            robot.rotate(-90, 50);
            robot.move(3, 50);
            robot.rotate(-90, 50);
            robot.move(0.45, 50);
            robot.rotate(90, 50); //aligned with pole 3.
            robot.move(0.25, 50); //to get closer to pole 3.
            //code to drop noodle at pole 3.
            robot.rotate(90, 50);
            robot.move(0.45, 50);
            robot.rotate(90, 50);
            robot.move(3, 50);
            robot.rotate(90, 50);
            robot.move(0.5, 50);
            robot.rotate(90, 50); //back at noodles. repeat.
        }
        //END OF PHASE 4. BEGIN OPERATION REMOVE TOP NOODLE. HEAD TO POLE STATION.
        robot.rotate(90, 50);
        robot.move(0.5, 50);
        robot.rotate(-90, 50);
        robot.move(3, 50);
        robot.rotate(-90, 50);
        robot.move(2, 50); //align with pole 1.
        robot.rotate(90, 50);
        //BEGIN REMOVAL.
        for(int m = 0; m < 5; m++){
            //remove top noodle. eject (i dunno where it should go)
            //potential code to move removed noodle somewhere.
            if(m==4){
                break;
            }
            robot.rotate(90, 50);
            robot.move(0.1, 50);//to next pole
            robot.rotate(-90, 50);
        }
        robot.rotate(180, 50);
        robot.move(1, 50);
        robot.rotate(-90, 50);
        robot.move(2, 50);
        robot.rotate(-90, 50);
        robot.move(1, 50);
        //remove top noodle. eject (i dunno where it should go)
        //potential code to move removed noodle somewhere.
        //END OF OPERATION.  END OF ROUTE SEGMENT.
    }
        

    }
};

int main()
{
    Roomba_OpMode opmode = Roomba_OpMode();
    opmode.runOpMode();

    return 1;
}