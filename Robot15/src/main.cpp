/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]         [Port(s)]
// Drivetrain           drivetrain      1, 10           
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"
#include "bits/stdc++.h" //Librerias esenciales de C++
using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                                  pre_auton                                */
/*                                                                           */
/*              ESTA ES LA CONFIGURACIÓN INICIAL DEL AUTONOMO                */
/*             Nosotros no creamos esta función, se crea solita              */
/*                            NO SE DEBE BORRAR!!                            */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

/*---------------------------------------------------------------------------*/
/*                               display_info                                */
/*                                                                           */
/*             Aquí solo imprimimos algo, ya sea en la consola               */
/*                                  o en cerebro                             */
/*   Es buena para imprimir valores, como grados, medidas, posiciones, etc   */
/*---------------------------------------------------------------------------*/

void display_info(){
  std::cout << "Hola desde la consola" << std::endl;
  Brain.Screen.print("Hola desde el cerebro");
}

/*---------------------------------------------------------------------------*/
/*                                autonomous                                 */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*                            a VEX Competition.                             */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                usercontrol                                */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*                            a VEX Competition.                             */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    display_info(); //Es bueno imprimir para que se muestren varios valores mientras corre el robot
    wait(100, msec);
  }
}
