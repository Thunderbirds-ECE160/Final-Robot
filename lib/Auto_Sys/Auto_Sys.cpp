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

int Auto_Sys::checkSonar() {
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

  return val;
}

void Auto_Sys::preventCrash() {
  // prevent crash oh no
  if (checkSonar() < 6) {
    while (checkSonar() < 6) {
      robot->stop();
      delay(10);
    }
  }
  delay(10);
}

void Auto_Sys::doAutonomous() {
  // 45 second timer
  unsigned long stoptime = millis() + 45000;
  robot->drive(FORWARD);
  delay(3000);
  robot->pivot(LEFT);
  delay(1500);
  boolean stateSet = false;
  while (millis() < stoptime) {
    unsigned long timeToNextMvmt = millis() + (45 * 142.18);
    int mvntStage = 0;
    if (timeToNextMvmt >= millis() && stateSet) {
      mvntStage++;
      // loopback
      if (mvntStage % 4 == 0) {
        mvntStage = 0;
      }
      stateSet = false;
    }

    switch (mvntStage) {
      case 0:
        robot->drive(FORWARD);
        if (!stateSet) {
          timeToNextMvmt = millis() + (45 * 142.18);
          stateSet = true;
        }
        break;
      case 1:
        robot->stop();
        if (!stateSet) {
          timeToNextMvmt = millis() + 500;
          stateSet = true;
        }
      case 2:
        robot->pivot(LEFT);
        if (!stateSet) {
          timeToNextMvmt = millis() + 1000;
          stateSet = true;
        }
        break;
      case 3:
        robot->stop();
        if (!stateSet) {
          timeToNextMvmt = millis() + 500;
          stateSet = true;
        }
        break;
    }

     preventCrash();
    if (irSys->getRecv()->decode(irSys->getResults())) {
      robot->stop();
      irSys->processHit();
      irSys->getRecv()->resume();
      
    }
  }
}