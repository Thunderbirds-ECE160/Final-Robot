/*************************************************************************************************************************************************
 * File: main.cpp
 * Author: Alex Westerman
 * Contains code by Alex Westerman, David Purdy, and Joshua Roehm
 * Date Created: 10/14/2019
 * Description
 * ======================
 * This file serves as the entry point of execution for the robot's function.
 * The only functions are the default Arduino Functions to allow for proper building of the project
 * 
 * Important Functions
 * ======================
 * void setup() - The default Arduino function that runs only once
 * void loop() - The default Arduino function that runs forever until the machine is reset
 **************************************************************************************************************************************************/

/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include "cpu_map.h"      //Contains pin definitions for the robot
#include <Arduino.h>      //The Standard Arduino Library
#include <Drive.h>        //Robot Driving Library (Written by Alex Westerman)
#include <PS2X_lib.h>     //PS2 Controller Interface Library (Written by Bill Porter - http://http://www.billporter.info/2010/06/05/playstation-2-controller-arduino-library-v1-0/)
#include <PS2_Control.h>  //PS2 Controlled Driving Library (Written by Alex Westerman)

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/
//PS2 Controller Object
PS2X ps2Boi;

//Drive object with servo pinouts
Drive robot(LEFT_SERVO_PIN, RIGHT_SERVO_PIN, GRIPPER_SERVO_PIN);

//PS2_Control object with proper reference params
PS2_Control ps2_Drive(&ps2Boi, &robot);

/*============================================================*
 *                         MAIN FUNCTIONS                     *
 *============================================================*/
void setup() {
  //Initalize the PS2_Control object
  ps2_Drive.init();
  
}

void loop() {
//Read and operate on controller input
 ps2_Drive.read_controller();
 
 //Short delay to prevent wack execution
 delay(10);
}
