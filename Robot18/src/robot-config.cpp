#include "vex.h"
#include "constants.h"

using namespace vex;

bool ThrowerIsOn = false;
bool WingAreOpen = false;
bool CollectorIsOn = true;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller Controller1 = controller(primary);

//chassis
inertial DrivetrainInertial = inertial(PORT15);
motor RightDriveA = motor(PORT10, ratio18_1, false);
motor RightDriveB = motor(PORT20, ratio18_1, false);
motor LeftDriveA = motor(PORT1, ratio18_1, true);
motor LeftDriveB = motor(PORT12, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 
  WHEEL_TRAVEL, TRACK_WIDTH, TRACK_BASE, mm, EXT_GEAR_RATIO);

//Recolector
motor Collector = motor(PORT14, ratio18_1, true);
//Recolector buttons
limit CollectorButtonBack = limit(Brain.ThreeWirePort.H);
limit CollectorButtonFront = limit(Brain.ThreeWirePort.G);

//Wings
pneumatics IndexerRight = pneumatics(Brain.ThreeWirePort.A);
pneumatics IndexerLeft = pneumatics(Brain.ThreeWirePort.B);

//Thrower
motor ThrowerUp = motor(PORT8, ratio6_1, false);
motor ThrowerDown = motor(PORT9, ratio6_1, true);

motor_group Thrower = motor_group(ThrowerUp, ThrowerDown);

bool RemoteControlCodeEnabled = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

void Thrower_cb(){
  if (!ThrowerIsOn){
    Thrower.spin(fwd, 500, percent);
    ThrowerIsOn = true;
  }else{
    Thrower.spin(fwd, 0, percent);
    ThrowerIsOn = false;
  }
} 

void CollectorBack(){
  if (!CollectorIsOn){
    Collector.stop(hold);
  }
  else{
    Collector.spin(reverse, 20, percent);//el que baja
    printf("CollectorBack\n");
  }
}

void CollectorFront(){
  Collector.spin(forward, 70, percent);//El que sube
  printf("CollectorFront\n");
}

void Collector_cb(){
  if (CollectorIsOn){
    CollectorFront();
    CollectorIsOn = false;
    printf("Collector is up\n");
  }
  else{
    CollectorIsOn = true;
    CollectorBack();
    printf("Collector goes down\n");
  }
}

void Wings(){
//If the wings are open then we close them
  if (!WingAreOpen) {
    //Wing.spinToPosition(100, degrees, true);
    IndexerRight.set(true);
    IndexerLeft.set(true);
    WingAreOpen = true;
  }
  //If the wings are close then we open them
  else {
    //Wing.spinToPosition(-100, degrees, true);
    IndexerRight.set(false);
    IndexerLeft.set(false);
    WingAreOpen = false;
  }
} 

int rc_auto_loop_function_Controller1() {
  //Funciones de botones y sistemas
  Controller1.ButtonR2.pressed(Thrower_cb);
  
  CollectorButtonBack.pressed(CollectorBack);
  CollectorButtonFront.pressed(CollectorFront);

  Controller1.ButtonB.pressed(Wings);
  Controller1.ButtonX.pressed(Wings);

  Controller1.ButtonL2.pressed(Collector_cb);

  while(true) {
    chassis_control();
  }
    
  wait(20, msec);
  return 0;
}

void vexcodeInit(void) {
  wait(200, msec);
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  wait(50, msec);
}

void chassis_control(){
  //int drivetrainLeftSideSpeed = (Controller1.Axis3.position() - (0.7*Controller1.Axis1.position()))/2.0;
  //int drivetrainRightSideSpeed = (Controller1.Axis3.position() + (0.7*Controller1.Axis1.position()))/2.0;

  int drivetrainLeftSideSpeed = (Controller1.Axis3.position() - (Controller1.Axis1.position()));
  int drivetrainRightSideSpeed = (Controller1.Axis3.position() + (Controller1.Axis1.position()));
  
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
