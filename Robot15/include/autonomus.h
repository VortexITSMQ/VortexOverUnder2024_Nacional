#include <iostream>
#include "robot-config.h"
#include "constants.h"
#include "vex_global.h"

using namespace vex;
extern brain Brain;

//--------- Main auton functions ---------//
void auton()
{
  DrivetrainInertial.calibrate();
  Drivetrain.setDriveVelocity(25, pct);

  //Primera ida
  Drivetrain.driveFor(fwd, 70, distanceUnits::cm);
  
  /*-----------------------------
  * Vuelta para empujar el trible
  * -----------------------------*/
  Drivetrain.turnToHeading(-30, rotationUnits::deg, 50, rpm, true);
  IndexerRight.set(true);
  Drivetrain.turnToHeading(180, rotationUnits::deg, 80, rpm, true);
  IndexerRight.set(false);

  /*----------------------------------
  * Se acomoda para recoger el trible
  * ----------------------------------*/
  Drivetrain.driveFor(reverse, 10, distanceUnits::cm);
  Drivetrain.turnToHeading(135, rotationUnits::deg, 30, rpm, true);
  Drivetrain.driveFor(reverse, 25, distanceUnits::cm);
  Drivetrain.turnToHeading(225, rotationUnits::deg, 30, rpm, true);
  Drivetrain.driveFor(reverse, 20, distanceUnits::cm);

  /*----------------
  * Recoge el trible
  * ----------------*/
  Climber.spin(reverse, 45, percent);
  wait(5.7, seconds);
  Climber.stop();

  /*---------------
  * Saca el trible
  * ---------------*/
  Drivetrain.driveFor(fwd, 85, distanceUnits::cm);
  
  /*---------------------------------
  * Se acomoda para soltar el trible
  * ---------------------------------*/
  Drivetrain.turnToHeading(180, rotationUnits::deg, 30, rpm, true);

  /*-----------------
  * Suelta el trible
  * -----------------*/
  Climber.spin(fwd, 45, percent);
  wait(2.3, seconds);
  Climber.stop();

  /*-----------------
  * Empuja el trible
  * -----------------*/
  Drivetrain.setDriveVelocity(70, pct);
  Drivetrain.driveFor(reverse, 50, distanceUnits::cm);
  Drivetrain.driveFor(fwd, 10, distanceUnits::cm);
  Drivetrain.driveFor(reverse, 15, distanceUnits::cm);

  /*-----------------------------------
  * Se acomoda para tocar el tubo rojo
  * -----------------------------------*/
  Drivetrain.setDriveVelocity(45, pct);
  Drivetrain.driveFor(fwd, 10, distanceUnits::cm);
  Drivetrain.turnToHeading(305, rotationUnits::deg, 30, rpm, true);
  Drivetrain.driveFor(reverse, 55, distanceUnits::cm);
}