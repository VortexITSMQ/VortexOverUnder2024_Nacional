#include "vex.h"
#include "constants.h"
using namespace vex;

// Cerebelo
brain Brain;

// Control (mando)
controller Controller1 = controller(primary);

// Chassis
//Motor rojo  18:1
//Motor verde 36:1
//Motor azul   6:1
inertial DrivetrainInertial = inertial(PORT13);
motor RightDriveA = motor(PORT1, ratio6_1, true);
motor RightDriveB = motor(PORT2, ratio6_1, false);
motor LeftDriveA = motor(PORT1, ratio6_1, true);
motor LeftDriveB = motor(PORT2, ratio6_1, false);
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 
  WHEEL_TRAVEL, TRACK_WIDTH, TRACK_BASE, mm, EXT_GEAR_RATIO);


bool RemoteControlCodeEnabled = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;


/*--------------------------------------------------------------------------*/
/*                   rc_auto_loop_function_Controller1()                    */
/*                                                                          */
/*               Aquí se junta todas las funciones de control               */
/*               se repetiran una vez el control se inicialice              */
/*--------------------------------------------------------------------------*/
int rc_auto_loop_function_Controller1() {
  //Funciones de botones y sistemas
  //..............................
  //..............................
  while(true) {
    chassis_control();
  }
    
  wait(20, msec);
  return 0;
}

/*--------------------------------------------------------------------------*/
/*                               vexcodeInit()                              */
/*                                                                          */
/*               Aquí solamente se calibra el sensor inercial               */
/*--------------------------------------------------------------------------*/
void vexcodeInit( void ) {
  wait(200, msec);
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  wait(50, msec);
}


/*--------------------------------------------------------------------------*/
/*                             chassis_control()                            */
/*                                                                          */
/*       Aquí se especifica la configuración de como controlar el robot     */
/*                 SI SE QUIERE CAMBIAR LA VELOCIDAD DEL ROBOT              */
/*                     se tiene que cambiar el cálculo de:                  */
/*           drivetrainLeftSideSpeed y de drivetrainRightSideSpeed          */
/*--------------------------------------------------------------------------*/
void chassis_control(){
  //int drivetrainLeftSideSpeed = (Controller1.Axis3.position() - (0.7*Controller1.Axis1.position()))/2.0;
  //int drivetrainRightSideSpeed = (Controller1.Axis3.position() + (0.7*Controller1.Axis1.position()))/2.0;

  int suma1 = (Controller1.Axis3.position() - (Controller1.Axis1.position())) * 0.8;
  int suma2 = (Controller1.Axis3.position() + (Controller1.Axis1.position())) * 0.8;
  
  int drivetrainLeftSideSpeed = (Controller1.Axis3.position() - (Controller1.Axis1.position())) * suma1;
  int drivetrainRightSideSpeed = (Controller1.Axis3.position() + (Controller1.Axis1.position())) * suma2;


  
  if (drivetrainLeftSideSpeed < JOYSTICK_DEADBAND && drivetrainLeftSideSpeed > -JOYSTICK_DEADBAND) {
    if (DrivetrainLNeedsToBeStopped_Controller1) {
      LeftDriveSmart.stop();
      DrivetrainLNeedsToBeStopped_Controller1 = false;
    }
  } else {
    DrivetrainLNeedsToBeStopped_Controller1 = true;
  }
  if (drivetrainRightSideSpeed < JOYSTICK_DEADBAND && drivetrainRightSideSpeed > -JOYSTICK_DEADBAND) {
    if (DrivetrainRNeedsToBeStopped_Controller1) {
      RightDriveSmart.stop();
      DrivetrainRNeedsToBeStopped_Controller1 = false;
    }
  } else {
    DrivetrainRNeedsToBeStopped_Controller1 = true;
  }
  
  if (DrivetrainLNeedsToBeStopped_Controller1) {
    LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
    LeftDriveSmart.spin(forward);
  }
  if (DrivetrainRNeedsToBeStopped_Controller1) {
    RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
    RightDriveSmart.spin(forward);
  }
}