/*************************************************************************************************************************************************
 * File:
 * Author: Alex Westerman
 * Date Created:
 * Description
 * ======================
 *
 * This file implements the class prototype(s) defined in
 **************************************************************************************************************************************************/
/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include <cpu_map.h>

#include "Auto_Sys.h"


void Auto_Sys::init() {
  // Assume drive train is already inited
  // Assume that weaponssystem is already inited
  // This will be a "shell" function
}

void Auto_Sys::lineFollowing() {
  if (analogRead(LINE_SEN_L) > (colBlack - COL_TOLERANCE) &&
      analogRead(LINE_SEN_M) < (colWhite + COL_TOLERANCE) &&
      analogRead(LINE_SEN_R) > (colBlack - COL_TOLERANCE)) {
    robot->drive(FORWARD);
  } else if (analogRead(LINE_SEN_L) < (colWhite + COL_TOLERANCE) &&
             analogRead(LINE_SEN_M) > (colBlack - COL_TOLERANCE) &&
             analogRead(LINE_SEN_R) > (colBlack - COL_TOLERANCE)) {
    robot->spin(LEFT);
  } else if (analogRead(LINE_SEN_L) > (colBlack - COL_TOLERANCE) &&
             analogRead(LINE_SEN_M) > (colBlack - COL_TOLERANCE) &&
             analogRead(LINE_SEN_R) < (colWhite + COL_TOLERANCE)) {
    robot->spin(RIGHT);
  }
  // Add a "fallback" assuming that if all the sensors read black, spin 180
  // degees
  else if (analogRead(LINE_SEN_L) > (colBlack - COL_TOLERANCE) &&
           analogRead(LINE_SEN_M) > (colBlack - COL_TOLERANCE) &&
           analogRead(LINE_SEN_R) < (colWhite + COL_TOLERANCE)) {
    // Honestly, it does not matter which direction we rotate, just that we do
    // an approximate rotation
    robot->spin(RIGHT);
    // Fixed delay
    delay(500);
    // stop rotation
  }
  delay(10);
}

void Auto_Sys::checkSonar() {
  int val = 0;
  // Sending the trigger pulse
  pinMode(SONAR_TRIG, OUTPUT);
  digitalWrite(SONAR_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIG, LOW);

  // Reads echo and converting
  pinMode(SONAR_ECHO, INPUT);
  val = pulseIn(SONAR_ECHO, HIGH) / 74 / 2;

  // debugging
  Serial.print(val);
  Serial.println("in");

  // prevent crash oh no
  if (val < 6) {
    while (val < 6) {
      robot->stop();
    }
  }
  delay(10);
}

void Auto_Sys::doAutonomous() {
  // 45 second timer
  unsigned long stoptime = millis() + 45000;
  while (millis() < stoptime) {
    lineFollowing();
    checkSonar();
    if (irSys->getRecv()->decode(irSys->getResults())) {
      irSys->processHit();
      irSys->getRecv()->resume();
    }
  }
}