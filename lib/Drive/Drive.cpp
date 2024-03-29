/*************************************************************************************************************************************************
 * File: Drive.c
 * Author: Alex Westerman
 * Date Created: 10/17/2019
 * Description
 * ======================
 * This file contains common functionality regarding basic movement of a robot
 *using two continuous motion servos (left and right). There is optional
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

/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/

#include "Drive.h"

//Servo Attachment Method
void Drive::attachServos(){
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
}

// Driving (no limit)
void Drive::drive(int dir) {
  switch (dir) {
    case FORWARD:
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CW_ROT);
      break;
    case BACKWARD:
      leftServo.writeMicroseconds(CW_ROT);
      rightServo.writeMicroseconds(CCW_ROT);
      break;
    default:
      // Do nothing, this should not happed tbh
      break;
  }
}

// Turning
void Drive::turn(int dir) {
  switch (dir) {
    case LEFT:
      leftServo.writeMicroseconds(CCW_LOW_ROT);
      rightServo.writeMicroseconds(CW_ROT);
      break;
    case RIGHT:
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CW_LOW_ROT);
      break;
    default:
      break;
  }
}

//Spinning
void Drive::spin(int dir) {
  switch (dir) {
    case LEFT:
      leftServo.writeMicroseconds(CW_ROT);
      rightServo.writeMicroseconds(CW_ROT);
      break;
    case RIGHT:
      leftServo.writeMicroseconds(CCW_ROT);
      rightServo.writeMicroseconds(CCW_ROT);
      break;
    default:
      break;
  }
}

//Pivoting
void Drive::pivot(int dir) {
  switch (dir) {
    case LEFT:
      rightServo.writeMicroseconds(CW_ROT);
      break;
    case RIGHT:
      leftServo.writeMicroseconds(CCW_ROT);
      break;
    default:
      break;
  }
}

//Stop
void Drive::stop() {
  leftServo.writeMicroseconds(STOP_ROT);
  rightServo.writeMicroseconds(STOP_ROT);
}
