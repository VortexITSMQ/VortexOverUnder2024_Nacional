#include <iostream>
#include "constants.h"
#include "robot-config.h"
#include "vex_global.h"
#include "vex.h"


using namespace vex;
extern brain Brain;

//--------- Main auton functions ---------//

void auton_WP_P(){//Empieza ya posicionado WP

    CollectorButtonBack.pressed(CollectorBack);
    CollectorButtonFront.pressed(CollectorFront);
    Drivetrain.setDriveVelocity(30, rpm);

//agarra el triball
    CollectorIsOn = true;
    CollectorBack();
    while (CollectorCont < 2){
        wait(10, msec); 
    }
    
    CollectorFront();
    CollectorIsOn = false;

//abanza y se posiciona 
    Drivetrain.driveFor(fwd, 75, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(-43, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(fwd, 23, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(-135, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(fwd, 10, distanceUnits::cm);
    wait(10, msec);

//acciona lanzador
    Thrower.spin(fwd, 100, percent);
    wait(3, sec);

//mete triball
    Drivetrain.setDriveVelocity(60, rpm);
    Drivetrain.driveFor(fwd, 15, distanceUnits::cm);
    wait(10, msec);
    Thrower.stop(hold); 
    Drivetrain.driveFor(reverse, 15, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.driveFor(fwd, 12, distanceUnits::cm);
    wait(10, msec);

//se posiciona para tocar el tubo
    Drivetrain.setDriveVelocity(30, rpm);
    //Drivetrain.driveFor(reverse, 50, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(-93, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(reverse, 55, distanceUnits::cm);
    wait(10, msec);
    //Drivetrain.turnToHeading(-45, deg, 30, rpm);
   //wait(10, msec);
    Collector.spinTo(-100, deg);
    Collector.stop(coast);

}

void auton_10_P(){//Empieza ya posicionado lanza 10 Triballs
     // Collect triball
    CollectorButtonBack.pressed(CollectorBack);
    CollectorButtonFront.pressed(CollectorFront);
    Drivetrain.setDriveVelocity(30, rpm);

    Thrower.spin(fwd, 500, percent);
    wait(0.5,sec);

    CollectorIsOn = true;
    wait(10, msec);
    CollectorBack();
    while(CollectorCont <= 11){
        wait(10, msec);}
    CollectorIsOn = false;
    wait(1, sec);
    Thrower.spin(fwd, 0, percent);

    Drivetrain.driveFor(fwd, 70, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    Drivetrain.turnToHeading(-90, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.setDriveVelocity(80, rpm);
    Drivetrain.driveFor(reverse, 30, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    Drivetrain.setDriveVelocity(30, rpm);
    //Drivetrain.driveFor(reverse, 10, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    //Drivetrain.turnToHeading(135, deg, 30, rpm);
    //wait(10, msec);
    //Drivetrain.driveFor(reverse, 7, distanceUnits::cm); //Now in triball position
    //wait(10, msec);
    Collector.spinTo(-100, deg);
    Collector.stop(coast);

}

void skill_P(){//Empieza ya posicionado
    //CollectorFront();
    wait(5, sec);
    CollectorButtonBack.pressed(CollectorBack);
    CollectorButtonFront.pressed(CollectorFront);
    Drivetrain.setDriveVelocity(30, rpm);
    
    Thrower.spin(fwd, 100, percent);
    CollectorIsOn = true;
    CollectorBack();

}
void skill(){//Se posiciona solo
    CollectorButtonBack.released(CollectorBack);
    CollectorButtonFront.pressed(CollectorFront);
    Drivetrain.setDriveVelocity(30, rpm);

    CollectorFront();
    CollectorIsOn = false;

    Drivetrain.driveFor(fwd, 40, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(45, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(reverse, 40, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    Thrower.spin(fwd, 100, percent);
    CollectorIsOn = true;
    CollectorBack();
    }

void auton_WP(){ //se posiciona solo, Win point

    CollectorButtonBack.pressed(CollectorBack);
    CollectorButtonFront.pressed(CollectorFront);
    Drivetrain.setDriveVelocity(30, rpm);

    CollectorFront();
    CollectorIsOn = false;

//se posiciona en la esquina
    Drivetrain.driveFor(fwd, 40, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(45, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(reverse, 40, distanceUnits::cm); //Now in triball position
    wait(10, msec);

//agarra el triball
    CollectorIsOn = true;
    CollectorBack();
    while (CollectorCont < 2){
        wait(10, msec); 
    }
    
    CollectorFront();
    CollectorIsOn = false;

//abanza y se posiciona 
    Drivetrain.driveFor(fwd, 75, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(-43, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(fwd, 23, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(-135, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(fwd, 10, distanceUnits::cm);
    wait(10, msec);

//acciona lanzador
    Thrower.spin(fwd, 100, percent);
    wait(3, sec);

//mete triball
    Drivetrain.setDriveVelocity(60, rpm);
    Drivetrain.driveFor(fwd, 15, distanceUnits::cm);
    wait(10, msec);
    Thrower.stop(hold); 
    Drivetrain.driveFor(reverse, 15, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.driveFor(fwd, 12, distanceUnits::cm);
    wait(10, msec);

//se posiciona para tocar el tubo
    Drivetrain.setDriveVelocity(30, rpm);
    //Drivetrain.driveFor(reverse, 50, distanceUnits::cm);
    //wait(10, msec);
   // Drivetrain.turnToHeading(0, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(reverse, -93, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(55, deg, 30, rpm);
    wait(10, msec);
    Collector.spinTo(-100, deg);
    Collector.stop(coast);

}

void auton_10(){ //Se posiciona solo, lanza 10 triballs
    
  // Collect triball
    CollectorButtonBack.released(CollectorBack);
    CollectorButtonFront.pressed(CollectorFront);
    Drivetrain.setDriveVelocity(30, rpm);

    CollectorFront();
    CollectorIsOn = false;

    // Complete autonomous, no win point
    // Start to triball position
    Drivetrain.driveFor(fwd, 40, distanceUnits::cm);
    wait(10, msec);
    Drivetrain.turnToHeading(-45, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.driveFor(reverse, 40, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    Thrower.spin(fwd, 500, percent);
    
    CollectorIsOn = true;
    wait(10, msec);
    CollectorBack();
    while(CollectorCont <= 10){
        std::cout << CollectorCont << std::endl;
        wait(10, msec);}
    CollectorIsOn = false;
    wait(1, sec);
    Thrower.spin(fwd, 0, percent);

    Drivetrain.driveFor(fwd, 70, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    Drivetrain.turnToHeading(-90, deg, 30, rpm);
    wait(10, msec);
    Drivetrain.setDriveVelocity(80, rpm);
    Drivetrain.driveFor(reverse, 30, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    Drivetrain.setDriveVelocity(30, rpm);
    //Drivetrain.driveFor(reverse, 10, distanceUnits::cm); //Now in triball position
    wait(10, msec);
    //Drivetrain.turnToHeading(-45, deg, 30, rpm);
    //wait(10, msec);
    //Drivetrain.driveFor(reverse, 7, distanceUnits::cm); //Now in triball position
    //wait(10, msec);
    Collector.spinTo(-100, deg);
    Collector.stop(coast);
}

void move_to_coordinate(double target_x, double target_y, double target_heading)
{

    if (target_x == 0 && target_y != 0)
    {
        Drivetrain.driveFor(fwd, target_y, distanceUnits::cm);
    }
    if (target_y == 0 && target_x != 0)
    {
        double ang = 90;
        if (target_x > 0)
        {
        Drivetrain.turnToHeading(ang, rotationUnits::deg);
        }
        if (target_x < 0)
        {
        Drivetrain.turnToHeading(-ang, rotationUnits::deg);
        }
        Drivetrain.driveFor(fwd, target_x, distanceUnits::cm);
    }
    if (target_x != 0 && target_y != 0)
    {
        double ang = atan(target_y / target_x) * 180 / M_PI;
        double hyp = sqrt(target_x * target_x + target_y * target_y);
        // 1st quadrant
        if (target_x > 0 && target_y > 0)
        {
        Drivetrain.turnToHeading(ang, rotationUnits::deg);
        }
    // 2nd quadrant
    if (target_x < 0 && target_y > 0)
        {
        Drivetrain.turnToHeading(-ang, rotationUnits::deg);
        }
        // 3rd quadrant
        if (target_x < 0 && target_y < 0)
        {
        Drivetrain.turnToHeading(180 - ang, rotationUnits::deg);
        }
        // 4th quadrant
        if (target_x > 0 && target_y < 0)
        {
        Drivetrain.turnToHeading(180 + ang, rotationUnits::deg);
        }
        Drivetrain.driveFor(hyp, distanceUnits::cm);
    }
    DrivetrainInertial.resetHeading();
    if (target_heading != 0)
    {
        Drivetrain.turnToHeading(target_heading, rotationUnits::deg);
    }
    Drivetrain.stop(brakeType::hold);
}