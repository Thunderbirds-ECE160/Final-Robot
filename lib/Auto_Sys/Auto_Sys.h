/*************************************************************************************************************************************************
 * File:
 * Author: Alex Westerman
 * Date Created:
 * Description
 * ======================
 *
 * Class Variables
 * ======================
 *
 *
 * Class Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#ifndef AUTO_SYS_H_
#define AUTO_SYS_H_

/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include <Drive.h>
#include <IRremote.h>
#include <SR04.h>
#include <Weapon_Sys.h>

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/
// IMPORTANT : Comment if we do not want to calculate colors for the line
// follower
//#define USE_DEF_COL_VALS

// A tolerance value that is used with the line follower
#define COL_TOLERANCE 75

class Auto_Sys {
 private:
  // Calibration variables for line following
  int colBlack = 0;
  int colWhite = 0;

  // pointer vars for Weapon_Sys, Drive, and a Sonar
  Weapon_Sys* irSys;
  Drive* robot;
  SR04* sonar;

 public:
  Auto_Sys(Weapon_Sys* _irSys, Drive* _robot, SR04* _sonar) {
    irSys = _irSys;
    robot = _robot;
    sonar = _sonar;
  }

  ~Auto_Sys() {}

  void init();
  int doAvg(int[]);
  void lineFollowing();
  void checkSonar();
  void doAutonomous();
};

#endif