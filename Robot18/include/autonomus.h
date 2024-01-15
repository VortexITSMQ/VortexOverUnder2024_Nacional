#include <iostream>
#include "constants.h"
#include "robot-config.h"
#include "vex_global.h"
#include "vex.h"


using namespace vex;
extern brain Brain;

//--------- Main auton functions ---------//
/*void auton()
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
//

}*/

void auton(){
  // Collect triball
  CollectorButtonBack.released(CollectorBack);
  CollectorButtonFront.pressed(CollectorFront);
  Drivetrain.setDriveVelocity(30, rpm);

  CollectorFront();
  CollectorIsOn = false;
  AutonCollector = true;

  /*Drivetrain.driveFor(fwd, 40, distanceUnits::cm);
  wait(10, msec);
  Drivetrain.turnToHeading(-45, deg, 30, rpm);
  wait(10, msec);
  Drivetrain.driveFor(reverse, 40, distanceUnits::cm); //Now in triball position
  wait(10, msec);
  CollectorIsOn = true;
  CollectorBack();

  if(CollectorCont > 1){
      std::cout<<CollectorCont<<std::endl;
      Collector.stop(hold);
      wait(0.1, sec);
      Collector.spinFor(reverse, 10, deg); 
      Collector.stop(hold);
    }*/
  //Collector.spinTo(20, deg);
  /*Drivetrain.driveFor(fwd, 60, distanceUnits::cm);
  wait(10, msec);
  Drivetrain.turnToHeading(-65, deg, 30, rpm);
  wait(10, msec);
  Thrower.spin(fwd, 20, percent);
  wait(1, sec);
  CollectorFront();
  CollectorIsOn = false;
  wait(2, sec);
  Thrower.spin(fwd, 0, percent);*/

  // Complete autonomous, no win point
  // Start to triball position
  /*Drivetrain.driveFor(fwd, 40, distanceUnits::cm);
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

  Drivetrain.driveFor(fwd, 60, distanceUnits::cm); //Now in triball position
  wait(10, msec);
  Drivetrain.turnToHeading(-90, deg, 30, rpm);
  wait(10, msec);
  Drivetrain.setDriveVelocity(80, rpm);
  Drivetrain.driveFor(fwd, 30, distanceUnits::cm); //Now in triball position
  wait(10, msec);
  Drivetrain.setDriveVelocity(30, rpm);
  Drivetrain.driveFor(reverse, 10, distanceUnits::cm); //Now in triball position
  wait(10, msec);
  Drivetrain.turnToHeading(45, deg, 30, rpm);
  wait(10, msec);
  Drivetrain.driveFor(reverse, 7, distanceUnits::cm); //Now in triball position
  wait(10, msec);
  Collector.spinTo(-100, deg);
  Collector.stop(coast);*/


  





  //std:: cout << DrivetrainInertial.heading() << std::endl;
  /*DrivetrainInertial.resetHeading();
  wait(20, msec);
  Drivetrain.turnToHeading(90, deg, 30, rpm);
  std:: cout << DrivetrainInertial.heading() << std::endl;
  DrivetrainInertial.resetHeading();
  wait(20, msec);
  Drivetrain.turnToHeading(90, deg, 30, rpm);
  std:: cout << DrivetrainInertial.heading() << std::endl;
  wait(20, msec);*/
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