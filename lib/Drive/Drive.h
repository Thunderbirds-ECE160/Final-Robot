/*************************************************************************************************************************************************
 * File Name: Drive.h
 * Author: Alex Westerman
 * Date Created: 10/17/2019
 * Description
 * ======================
 *
 *
 * This is the header that corresponds to Drive.c
 *
 * Important Functions
 * ======================
 *
 *
 * Misc Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#ifndef DRIVE_H_
#define DRIVE_H_

/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include <Servo.h>
#include "Arduino.h"

// Defines for continuous servo writeMicrosecond commands
#define CW_ROT 1300
#define CCW_ROT 1700
#define STOP_ROT 1500
#define CW_LOW_ROT 1450
#define CCW_LOW_ROT 1550

// Direction defines
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4

class Drive {
 private:
  // Servo Objects
  Servo leftServo;
  Servo rightServo;


  int leftServoPin;
  int rightServoPin;

 public:
  Drive(int left, int right) {
    leftServoPin = left;
    rightServoPin = right;
  }

  ~Drive() {}

  //Servo Activation Method
  void attachServos();

  // Standard Driving Methods
  void drive(int);       // Driving (no limit)
  void turn(int);        // Turning (based on direciton)
  void spin(int);        // Spinning (no limit)
  void pivot(int);       // Pivoting (no limit)
  void stop();           // Stop moving

};

#endif