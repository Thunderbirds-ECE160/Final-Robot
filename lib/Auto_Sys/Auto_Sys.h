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
  int colBlack = 850;
  int colWhite = 650;

  // pointer vars for Weapon_Sys, Drive, and a Sonar
  Weapon_Sys* irSys;
  Drive* robot;


 public:
  Auto_Sys(Weapon_Sys* _irSys, Drive* _robot) {
    irSys = _irSys;
    robot = _robot;
  }

  ~Auto_Sys() {}

  void init();
  int doAvg(int[]);
  void lineFollowing();
  void checkSonar();
  void doAutonomous();
};

#endif