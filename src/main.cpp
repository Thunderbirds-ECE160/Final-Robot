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
#include <Arduino.h>  //The Standard Arduino Library
#include <Auto_Sys.h>
#include <Drive.h>     //Robot Driving Library (Written by Alex Westerman)
#include <PS2X_lib.h>  //PS2 Controller Interface Library (Written by Bill Porter - http://http://www.billporter.info/2010/06/05/playstation-2-controller-arduino-library-v1-0/)

#include "cpu_map.h"  //Contains pin definitions for the robot

//#include <IR_Control.h>   //IR Controlled Driving Library (Written by David
// Purdy, Ported by Alex Westerman) #include <IRremote.h>
#include <Controls.h>
#include <Weapon_Sys.h>
/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/
IRrecv reciever(IR_REMOTE_RECV);

IRsend transmitter;

// PS2 Controller Object
PS2X ps2Boi;

// Drive object with servo pinouts
Drive robot(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

Weapon_Sys weapons(&reciever, &transmitter);
Auto_Sys autonomous(&weapons, &robot);

Controls driveTrain(&robot, &ps2Boi, &weapons);

// IR Reciever Object
// IRrecv ir_reciever(IR_REMOTE_RECV);

// IRsend transmitter;

// IR_Control object with proper reference params
// IR_Control ir_Drive(&ir_reciever, &robot, &transmitter);

/*============================================================*
 *                         MAIN FUNCTIONS                     *
 *============================================================*/
void setup() {
  Serial.begin(9600);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  robot.attachServos();
  weapons.init();
  // Shell function for initializing autonomous
  // autonomous.init();
  autonomous.doAutonomous();
  delay(10);
  // Move to manual
  driveTrain.init();
}

void loop() {
  // Read and operate on IR input
  // ir_Drive.getCMD();

  driveTrain.entry();
  // Short delay to prevent wack execution
  delay(50);
}
