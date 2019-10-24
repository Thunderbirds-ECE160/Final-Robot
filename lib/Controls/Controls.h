/*************************************************************************************************************************************************
 * File: Controls.h
 * Author: Alex Westerman
 * Date Created: 10/24/2019
 * Description
 * ======================
 * This class will be the replacement for the previous IR_Control and
 *PS2_Control libraries Class Variables
 * ======================
 *
 *
 * Class Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#ifndef CONTROLS_H_
#define CONTROLS_H_
/*============================================================*
 *                      INCLUDE THINGS                        *
 *============================================================*/
#include <Arduino.h>
#include <Drive.h>
#include <IRremote.h>
#include <PS2X_lib.h>

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/

typedef enum { PS2_CONTROL, IR_CONTROL } Control_Sys;

#define DRIVE_FORWARD 1
#define DRIVE_BACKWARD 2
#define SPIN_LEFT 3
#define SPIN_RIGHT 4
#define PIVOT_LEFT 5
#define PIVOT_RIGHT 6
#define TURN_LEFT 7
#define TURN_RIGHT 8
#define FIRE 9

class Controls {
 private:
  Drive* robot;
  Control_Sys currentSys;
  PS2X* controller;
  IRrecv* remote;
  decode_results prev_cmd;
  decode_results recv_cmd;
  int currentCMD;

 public:
  Controls(Drive* _robot, PS2X* _controller) {
    robot = _robot;
    controller = _controller;
    currentSys = Control_Sys::PS2_CONTROL;
  }

  Controls(Drive* _robot, IRrecv* _remote) {
    robot = _robot;
    remote = _remote;
    currentSys = Control_Sys::IR_CONTROL;
  }

  ~Controls() {}
  void init();
  void entry();
  void readPS2();
  void readIR();
  void parseInput(int);
};

#endif