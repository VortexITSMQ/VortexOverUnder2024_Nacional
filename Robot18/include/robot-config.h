using namespace vex;

extern brain Brain;
extern inertial DrivetrainInertial;
extern controller Controller1;
extern smartdrive Drivetrain;
extern bool CollectorIsOn;

//chassis
extern motor RightDriveA;
extern motor RightDriveB;
extern motor LeftDriveA;
extern motor LeftDriveB;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

//Recolector
extern motor Collector;
extern limit CollectorButtonBack;
extern limit CollectorButtonFront;

//Wings
extern pneumatics IndexerRight;
extern pneumatics IndexerLeft;

//Thrower
extern motor ThrowerUp;
extern motor ThrowerDown;
extern motor_group Thrower;

//Collector functions
extern int rc_auto_loop_function_Controller1();

void Collector_cb();
void CollectorFront();
void CollectorBack();


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
// Driver Control Function
extern int rc_auto_loop_function_Controller1();
void chassis_control();