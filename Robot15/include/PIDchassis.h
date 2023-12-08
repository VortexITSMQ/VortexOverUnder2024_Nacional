#include "vex.h"
#include "robot-config.h"
#include "constants.h"
using namespace vex;


double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

int error; //SensorValue - DesireValue : Position
int prevError; //Position 20 miliseconds ago
int derivative;
int totalError;

//Varaible modified for use
bool enableDrivePID = true;

int drivePID(){

  while(enableDrivePID){

    int RightDriveAPosition = RightDriveA.position(degrees);
    int RightDriveBPosition = RightDriveB.position(degrees);
    int LeftDriveAPosition = LeftDriveA.position(degrees);
    int LeftDriveBPosition = LeftDriveB.position(degrees);

    int averagePosition = ();
    
    //code
    prevError = error;
    task::sleep(20);

  }

}