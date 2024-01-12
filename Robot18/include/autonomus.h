#include <iostream>
#include "constants.h"
#include "robot-config.h"
#include "vex_global.h"


using namespace vex;
extern brain Brain;

//--------- Main auton functions ---------//
void auton()
{
    //Complete route of ROBOT 18
    CollectorButtonBack.pressed(CollectorBack);
    CollectorButtonFront.pressed(CollectorFront);

    DrivetrainInertial.calibrate();
    Drivetrain.setDriveVelocity(25, pct);

//Levatar el recolector y detenerlo
    CollectorFront();
    CollectorIsOn = false;

//avanza, gira, retrocede
    Drivetrain.driveFor(fwd, 40, distanceUnits::cm);
    Drivetrain.turnToHeading(-48, rotationUnits::deg, 50, rpm, true);
    Drivetrain.driveFor(reverse, 45, distanceUnits::cm);

//baja el recolector y Levanta el triball
    CollectorIsOn = true;
    CollectorBack();
    wait(2.2, sec);
    Collector.stop(hold);

//avanza, retrocede, da vuelta
    Drivetrain.driveFor(fwd, 30, distanceUnits::cm);
    Drivetrain.turnToHeading(0, rotationUnits::deg, 50, rpm, true);

//Lanzador poquito, recolector arriba
    Thrower.spin(fwd, 20, percent);
    CollectorFront();
    CollectorIsOn = false;
    wait(3, sec);
    Thrower.stop(hold);
    /*
//Mete triball
    Drivetrain.driveFor(fwd, , distanceUnits::cm);
    Drivetrain.turnToHeading();
    //alita
    Drivetrain.driveFor(fwd, ,distanceUnits::cm);

//Se acomoda para lanzar
    Drivetrain.driveFor(reverse, , distanceUnits::cm);
    Drivetrain.turnToHeading();
    Drivetrain.driveFor(reverse, , distanceUnits::cm);

//lanza

*/
//

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