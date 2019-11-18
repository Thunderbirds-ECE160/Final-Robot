/*************************************************************************************************************************************************
 * File: main.cpp
 * Author: Alex Westerman
 * Contains code by Alex Westerman, David Purdy, and Joshua Roehm
 * Date Created: 10/14/2019
 * Description
 * ======================
 * This file serves as the entry point of execution for the robot's function.
 * The only functions are the default Arduino Functions to allow for proper
 *building of the project
 *
 * Important Functions
 * ======================
 * void setup() - The default Arduino function that runs only once
 * void loop() - The default Arduino function that runs forever until the
 *machine is reset
 **************************************************************************************************************************************************/

/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include <Arduino.h>   //The Standard Arduino Library
#include <Auto_Sys.h>  //Autonomous Mode Library (Written by Alex Westerman, David Purdy, and Joshua Roehm)
#include <Controls.h>  //Teleoperation Library (Written by Alex Westerman)
#include <Drive.h>     //Robot Driving Library (Written by Alex Westerman)
#include <PS2X_lib.h>  //PS2 Controller Interface Library (Written by Bill Porter - http://http://www.billporter.info/2010/06/05/playstation-2-controller-arduino-library-v1-0/)
#include <Weapon_Sys.h>  //IR Subsystem Library (Written by Alex Westerman and David Purdy)

#include "cpu_map.h"  //Contains pin definitions for the robot

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/
// IR Receiver Object
IRrecv reciever(IR_REMOTE_RECV);

// IR Transmitter object
IRsend transmitter;

// PS2 Controller Object
PS2X ps2Boi;

// Drivetrain object with servo pinouts
Drive robot(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

// IR Subsystem
Weapon_Sys weapons(&reciever, &transmitter);

// Autonomous Subsystem
Auto_Sys autonomous(&weapons, &robot);

// Teleoperation Subsystem
Controls driveTrain(&robot, &ps2Boi, &weapons);

/*============================================================*
 *                         MAIN FUNCTIONS                     *
 *============================================================*/
void setup() {
  // Debug clause
#ifdef DEBUG_ME
  Serial.begin(9600);
#endif

  // set LED pins to OUTPUT
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // Initialize Drivetrain
  robot.attachServos();

  // Initialize IR subsystem
  weapons.init();

  // Shell function for initializing autonomous
  // autonomous.init();

  // Start with Autonomous mode
  autonomous.doAutonomous();
  delay(10);
  // Move to manual
  driveTrain.init();
}

void loop() {
  // This code just executes the driving protocol, which runs in a loop until
  // exit
  driveTrain.entry();
  // Short delay to prevent wack execution
  delay(50);
}
