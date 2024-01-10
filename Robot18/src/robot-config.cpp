#include "vex.h"
#include "constants.h"

using namespace vex;

bool ThrowerIsOn = false;
bool WingAreOpen = false;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller Controller1 = controller(primary);

//chassis
inertial DrivetrainInertial = inertial(PORT10);
motor RightDriveA = motor(PORT2, ratio18_1, true);
motor RightDriveB = motor(PORT19, ratio18_1, true);
motor LeftDriveA = motor(PORT1, ratio18_1, false);
motor LeftDriveB = motor(PORT10, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 
  WHEEL_TRAVEL, TRACK_WIDTH, TRACK_BASE, mm, EXT_GEAR_RATIO);

//Recolector
motor Collector = motor(PORT11, ratio18_1, true);
//Recolector buttons
limit CollectorButtonFront = limit(Brain.ThreeWirePort.H);
limit CollectorButtonBack = limit(Brain.ThreeWirePort.G);

//Wings
pneumatics IndexerRight = pneumatics(Brain.ThreeWirePort.A);
pneumatics IndexerLeft = pneumatics(Brain.ThreeWirePort.B);

//Lanzador
motor ThrowerUp = motor(PORT1, ratio6_1, false);
motor ThrowerDown = motor(PORT12, ratio6_1, true);

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

void CollectorFront(){
  Collector.spin(reverse);
  printf("catapultswitch\n");
}

void CollectorBack(){
  Collector.spin(forward);
  printf("catapultswitch\n");
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
  CollectorButtonFront.pressed(CollectorFront);
  CollectorButtonBack.pressed(CollectorBack);

  Controller1.ButtonB.pressed(Wings);
  Controller1.ButtonX.pressed(Wings);

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

