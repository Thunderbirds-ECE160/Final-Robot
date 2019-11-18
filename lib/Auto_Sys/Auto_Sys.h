/*************************************************************************************************************************************************
 * File: Auto_Sys.h
 * Author: Alex Westerman, David Purdy, Joshua Roehm
 * Port Author: Alex Westerman
 * Date Created: 10/31/2019
 * Description
 * ======================
 * This class defines an autonomous mode for the robot
 * 
 * Class Variables
 * ======================
 * Weapon_Sys* irSys - Pointer to the IR Subsystem Object
 * Drive* robot - Pointer to the drivetrain object
 *
 * Class Functions
 * ======================
 * void init() - Initialization for the Auto_Sys object. Currently an empty function as of the most recent implementation
 * int doAvg(int[]) - Simple Average function that returns the average of an array of ints
 * void lineFollowing() - Simple line following function 
 * int checkSonar() - Function that uses the sonar to find the distance (in inches) of the nearest obstacle
 * void doAutonomous() - Main autonomous mode function that is used  
 * void preventCrash();
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
  int checkSonar();
  void doAutonomous();
  void preventCrash();
};

#endif